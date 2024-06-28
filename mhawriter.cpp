#include "mhawriter.h"
#include <opencv2/imgcodecs.hpp>
#include <QThread>


MHAWriter::MHAWriter(QObject *parent,  const std::string& filepath, const std::string& prefixname)
    : QObject{parent}, isRecording(false)
{
    // open a file to write the .mha
    filename_ = filepath + prefixname + "_" + getCurrentDateTime() + ".mha";
    mhaFile_.open(filename_, std::ios::binary);
    if (!mhaFile_.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename_);
    }

    // start the timestamp
    timestamp.start();
}

/*
MHAWriter::MHAWriter(QObject *parent, BmodeConnection *bmodeConnection, QualisysConnection *qualisysConnection, const std::string& prefixname)
    : QObject{parent}, isRecording(false), bmodeConnection_(bmodeConnection), qualisysConnection_(qualisysConnection)
{
    // open a file to write the .mha
    filename_ = "D:/" + prefixname + "_" + getCurrentDateTime() + ".mha";
    mhaFile_.open(filename_, std::ios::binary);
    if (!mhaFile_.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename_);
    }

    // start the timestamp
    timestamp.start();
}
*/

void MHAWriter::onImageReceived(const cv::Mat &image) {
    if (latestTransform) {
        storeDataPair(image, *latestTransform);
        resetData();
    } else {
        latestImage = image;
    }
}

void MHAWriter::onRigidBodyReceived(const QualisysTransformationManager &tmanager) {
    if (latestImage) {
        storeDataPair(*latestImage, tmanager.getTransformationById("TB-M"));
        resetData();
    } else {
        latestTransform = tmanager.getTransformationById("TB-M");
    }
}

void MHAWriter::storeDataPair(const cv::Mat& image, const Eigen::Isometry3d& transform) {
    // make a complete copy of cv::Mat using copyTo() function, it is super necessary so that i am not referencing the streaming image
    cv::Mat imageCopy;
    image.copyTo(imageCopy);
    // make a copy of Eigen::Isometry3d, not like cv::Mat, assigning new object like this will not affect the original object
    Eigen::Isometry3d transformCopy = transform;

    allImages.push_back(imageCopy);
    allTransforms.push_back(transformCopy);
    allTimestamps.push_back(timestamp.elapsed()/1000.0);
}

void MHAWriter::resetData() {
    latestImage.reset();
    latestTransform.reset();
}

void MHAWriter::startRecord()
{
    isRecording = true;
    // connect(bmodeConnection_, &BmodeConnection::imageProcessed, this, &MHAWriter::onImageReceived);
    // connect(qualisysConnection_, &QualisysConnection::dataReceived, this, &MHAWriter::onRigidBodyReceived);
}

bool MHAWriter::stopRecord()
{
    isRecording = false;
    // disconnect(bmodeConnection_, &BmodeConnection::imageProcessed, this, &MHAWriter::onImageReceived);
    // disconnect(qualisysConnection_, &QualisysConnection::dataReceived, this, &MHAWriter::onRigidBodyReceived);
    resetData();

    if (!mhaFile_.is_open()) {
        std::cerr << "Error opening MHA file for writing." << std::endl;
        return false;
    }

    // Header initalization
    // read this    : http://perk-software.cs.queensu.ca/plus/doc/nightly/user/FileSequenceFile.html
    // example file : https://github.com/PlusToolkit/PlusLibData/blob/master/TestImages/SpinePhantomFreehandReconstructed.mha
    header_.ObjectType                 = "Image";                               // Type of the MetaIO object (must be Image)
    header_.NDims                      = 3;                                     // Number of dimensions for a 3D image (must be 3)
    header_.BinaryData                 = true;                                  // Data is in binary format (must be true)
    header_.BinaryDataByteOrderMSB     = false;                                 // Little-endian byte order (must be false)
    header_.CompressedData             = false;                                 // Data is not compressed
    header_.TransformMatrix            = {1, 0, 0, 0, 1, 0, 0, 0, 1};           // Initialize with an identity matrix (not used by Plus Toolkit, typical value is identity matrix)
    header_.DimSize                    = { allImages.at(1).cols, allImages.at(1).rows, static_cast<int>(allImages.size())}; // Assuming a 2D image with one slice
    header_.Offset                     = {0, 0, 0};                             // Origin of the image (not used by Plus Toolkit, typical value is 0 0 0)
    header_.CenterOfRotation           = {0, 0, 0};                             // Center of rotation (not used by Plus Toolkit, typical value is 0 0 0)
    header_.AnatomicalOrientation      = "RAI";                                 // Anatomical orientation (not used by Plus Toolkit, typical value is RAI)
    header_.ElementSpacing             = {1, 1, 1};                             // Spacing between elements (not used by Plus Toolkit, typical value is 1 1 1)
    header_.ElementType                = "MET_UCHAR";                           // Data type of the image elements
    header_.UltrasoundImageOrientation = "MFA";                                 // Default value is MFA
    header_.UltrasoundImageType        = "BRIGHTNESS";                          // Default value is BRIGHTNESS (for B-mode)
    header_.ElementDataFile            = "LOCAL";                               // Location of the image data. For *.mha files (must be LOCAL)

    writeHeader();
    writeTransformations();
    writeImages();

    // close the file to save
    mhaFile_.close();

    return true;
}

bool MHAWriter::writeHeader()
{
    // Write header
    mhaFile_ << "ObjectType = "                 << header_.ObjectType << std::endl;
    mhaFile_ << "NDims = "                      << header_.NDims << std::endl;
    mhaFile_ << "BinaryData = "                 << (header_.BinaryData ? "True" : "False") << std::endl;
    mhaFile_ << "BinaryDataByteOrderMSB = "     << (header_.BinaryDataByteOrderMSB ? "True" : "False") << std::endl;
    mhaFile_ << "CompressedData = "             << (header_.CompressedData ? "True" : "False") << std::endl;
    mhaFile_ << "TransformMatrix = "            << header_.TransformMatrix.at(0) << " " << header_.TransformMatrix.at(1) << " " << header_.TransformMatrix.at(2) << " "
                                                << header_.TransformMatrix.at(3) << " " << header_.TransformMatrix.at(4) << " " << header_.TransformMatrix.at(5) << " "
                                                << header_.TransformMatrix.at(6) << " " << header_.TransformMatrix.at(7) << " " << header_.TransformMatrix.at(8) << std::endl;
    mhaFile_ << "DimSize = "                    << header_.DimSize.at(0) << " "
                                                << header_.DimSize.at(1) << " "
                                                << header_.DimSize.at(2) << std::endl;
    mhaFile_ << "Offset = "                     << header_.Offset.at(0) << " "
                                                << header_.Offset.at(1) << " "
                                                << header_.Offset.at(2) << std::endl;
    mhaFile_ << "CenterOfRotation = "           << header_.CenterOfRotation.at(0) << " "
                                                << header_.CenterOfRotation.at(1) << " "
                                                << header_.CenterOfRotation.at(2) << std::endl;
    mhaFile_ << "AnatomicalOrientation = "      << header_.AnatomicalOrientation << std::endl;
    mhaFile_ << "ElementSpacing = "             << header_.ElementSpacing.at(0) << " "
                                                << header_.ElementSpacing.at(1) << " "
                                                << header_.ElementSpacing.at(2) << std::endl;
    mhaFile_ << "ElementType = "                << header_.ElementType << std::endl;
    mhaFile_ << "UltrasoundImageOrientation = " << header_.UltrasoundImageOrientation << std::endl;
    mhaFile_ << "UltrasoundImageType = "        << header_.UltrasoundImageType << std::endl;

    return true;
}

// Function to write transformation data
bool MHAWriter::writeTransformations()
{
    // Write the transformations
    for (size_t i = 0; i < allTransforms.size(); ++i) {
        bool isNaN = false;
        const Eigen::Isometry3d& transform = allTransforms[i];
        mhaFile_ << "Seq_Frame" << std::setfill('0') << std::setw(4) << i << "_ProbeToTrackerTransform = ";
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                mhaFile_ << transform.matrix()(row, col) << " ";
                if(transform.matrix()(row, col)!=transform.matrix()(row, col)) isNaN=true;
            }
        }
        mhaFile_ << std::endl;

        // if the transformation contains NaN, set TransformStatus to invalid
        if (isNaN) mhaFile_ << "Seq_Frame" << std::setfill('0') << std::setw(4) << i << "_ProbeToTrackerTransformStatus = " << "INVALID" << std::endl;
        else mhaFile_ << "Seq_Frame" << std::setfill('0') << std::setw(4) << i << "_ProbeToTrackerTransformStatus = " << "OK" << std::endl;
        // print the timestamps
        mhaFile_ << "Seq_Frame" << std::setfill('0') << std::setw(4) << i << "_Timestamp = " << allTimestamps[i] << std::endl;
        // i am assuming that the image always ok
        mhaFile_ << "Seq_Frame" << std::setfill('0') << std::setw(4) << i << "_ImageStatus = " << "OK" << std::endl;
    }

    // Write this before the image
    mhaFile_ << "ElementDataFile = " << header_.ElementDataFile << std::endl;

    return true;
}

// Function to write raw image data
bool MHAWriter::writeImages()
{
    // // For debugging only, to see the resulting images in a window
    // cv::namedWindow("Image Sequence", cv::WINDOW_NORMAL);
    // // for (const auto& image : allImages) {
    // //     cv::imshow("Image Sequence", image);
    // //     cv::waitKey(500);  // Display each image for 1 second
    // // }
    // for (size_t i = 0; i < allImages.size(); ++i) {
    //     const auto& image = allImages[i];
    //     cv::imshow("Image Sequence", image);
    //     cv::waitKey(10);  // Display each image for 1 second
    // }

    // for (size_t i = 0; i < allImages.size(); ++i) {
    //     const auto& myimage = allImages[i];
    //     mhaFile_.write(reinterpret_cast<const char*>(myimage.data), myimage.total() * myimage.elemSize());
    //     std::cout << myimage.total() << "*"<< myimage.elemSize() << std::endl;
    //     mhaFile_.flush();
    // }

    for (size_t i = 0; i < allImages.size(); ++i) {
        mhaFile_.write(reinterpret_cast<const char*>(allImages[i].data), allImages[i].total() * allImages[i].elemSize());
        mhaFile_.flush();
    }

    // mhaFile_.flush();
    // std::vector<uchar> rawData(allImages[0].data, allImages[0].data + allImages[0].total() * allImages[0].elemSize());
    // mhaFile_.write(reinterpret_cast<const char*>(rawData.data()), rawData.size());
    // mhaFile_.flush();

    return true;
}

// Function to get the current date and time as a formatted string
std::string MHAWriter::getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&time_t);

    // Format the date and time as a string (e.g., "2024-04-22_16-18-42")
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &local_tm);
    return std::string(buffer);
}

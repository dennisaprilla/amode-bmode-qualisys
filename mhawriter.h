#ifndef MHAWRITER_H
#define MHAWRITER_H

#include <QObject>
// #include <QRunnable>
#include <QDateTime>
#include <QElapsedTimer>

#include <string>
#include <vector>
#include <fstream>

#include <Eigen/Geometry>
#include <opencv2/opencv.hpp>

#include "bmodeconnection.h"
#include "qualisysconnection.h"
#include "qualisystransformationmanager.h"

struct MHAHeader {
    std::string      ObjectType;
    int              NDims;
    bool             BinaryData;
    bool             BinaryDataByteOrderMSB;
    bool             CompressedData;
    std::vector<int> TransformMatrix;
    std::vector<int> DimSize;
    std::vector<int> Offset;
    std::vector<int> CenterOfRotation;
    std::string      AnatomicalOrientation;
    std::vector<int> ElementSpacing;
    std::string      ElementType;
    std::string      UltrasoundImageOrientation;
    std::string      UltrasoundImageType;
    std::string      ElementDataFile;

};

/**
 * @class MHAWriter
 * @brief For writing Sequence Image (.mha) files.
 *
 * For the context. The user should be able to record b-mode images and its transfromation in order to
 * perform volume reconstruction. This two data usually is encapsulated in a file called Sequence Image
 * with an extension (.mha). You can learn how Sequence Image file is defined here:
 * http://perk-software.cs.queensu.ca/plus/doc/nightly/user/FileSequenceFile.html
 *
 * This class has two slots, onImageReceived and onRigidBodyReceived, which needs to be connected to a
 * signal from BmodeConnection::imageProcessed and QualisysConnection::dataReceived. This class will do
 * the soft-synchronization by making sure there will be pair of data.
 *
 */

class MHAWriter : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Constructor function, it loads the csv file directly by calling loadData() function
     */
    explicit MHAWriter(QObject *parent = nullptr, const std::string& filepath="D:\\", const std::string& prefixname="output");

    /**
     * @brief Start recording the data (image, transformations, and timestamps), stored in local
     */
    void startRecord();

    /**
     * @brief Stop recording the data (image, transformations, and timestamps) and start writing the file
     */
    int stopRecord();

    /**
     * @brief SET the transformation ID for bmode probe and bmode reference (marker on the phantom)
     */
    void setTransformationID(std::string bmodeprobe_transformationID, std::string bmoderef_transformationID);

public slots:

    /**
     * @brief slot function, will be called when an image is received, needs to be connected to signal from bmodeconnection class
     */
    void onImageReceived(const cv::Mat &image);

    /**
     * @brief slot function, will be called when transformations in a timestamp are received, needs to be connected to signal from qualisysconnection class
     */
    void onRigidBodyReceived(const QualisysTransformationManager &tmanager);

private:

    /**
     * @brief writes header for sequence image (.mha) file
     */
    bool writeHeader();

    /**
     * @brief writes transformations, status, timestamps, for sequence image (.mha) file
     */
    bool writeTransformations();

    /**
     * @brief writes binary image (not compressed), for sequence image (.mha) file
     */
    bool writeImages();

    /**
     * @brief generates current time, for file naming purposes
     */
    std::string getCurrentDateTime();

    /**
     * @brief handles pair of data (soft-synchronization)
     */
    void storeDataPair(const cv::Mat& image, const Eigen::Isometry3d& transform_probe, const Eigen::Isometry3d& transform_ref);

    /**
     * @brief reset the pair of data (soft-synchronization)
     */
    void resetData();

    // variables for naming file
    std::string filename_;
    MHAHeader header_;
    std::ofstream mhaFile_;

    // variables for storing data
    bool isRecording;
    std::optional<cv::Mat> latestImage;
    std::optional<Eigen::Isometry3d> latestTransform_probe;
    std::optional<Eigen::Isometry3d> latestTransform_ref;

    std::vector<cv::Mat>           allImages;
    std::vector<Eigen::Isometry3d> allTransforms_probe;
    std::vector<Eigen::Isometry3d> allTransforms_ref;
    std::vector<double>            allTimestamps;
    QElapsedTimer timestamp;

    // variables that is used to grab the necessary rigid bodies
    std::string bmodeprobe_transformationID_ = "B_PROBE";
    std::string bmoderef_transformationID_   = "B_REF";

signals:
};

#endif // MHAWRITER_H

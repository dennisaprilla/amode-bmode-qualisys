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

class MHAWriter : public QObject
{
    Q_OBJECT

public:

    explicit MHAWriter(QObject *parent = nullptr, const std::string& filepath="D:\\", const std::string& prefixname="output");
    // explicit MHAWriter(QObject *parent = nullptr, const std::string& prefixname="output");
    // explicit MHAWriter(QObject *parent = nullptr, BmodeConnection *bmodeConnection = nullptr, QualisysConnection *qualisysConnection = nullptr, const std::string& prefixname="output");
    void startRecord();
    bool stopRecord();

public slots:
    void onImageReceived(const cv::Mat &image);
    void onRigidBodyReceived(const QualisysTransformationManager &tmanager);

private:
    // functions for writing MHA file
    bool writeHeader();
    bool writeTransformations();
    bool writeImages();
    std::string getCurrentDateTime();

    // functions to handle pair of data soft-synchronization
    void storeDataPair(const cv::Mat& image, const Eigen::Isometry3d& isometry);
    void resetData();

    // variables for naming file
    std::string filename_;
    MHAHeader header_;
    std::ofstream mhaFile_;

    // variables for storing data
    bool isRecording;
    std::optional<cv::Mat> latestImage;
    std::optional<Eigen::Isometry3d> latestTransform;
    std::vector<cv::Mat> allImages;
    std::vector<Eigen::Isometry3d> allTransforms;
    std::vector<double> allTimestamps;
    QElapsedTimer timestamp;

    // BmodeConnection *bmodeConnection_;
    // QualisysConnection *qualisysConnection_;

signals:
};

#endif // MHAWRITER_H

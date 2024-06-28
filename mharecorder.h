// MhaRecorder.h

#ifndef MHA_RECORDER_H
#define MHA_RECORDER_H

#include <QObject>
#include <QPushButton>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Eigen/Geometry>

class MhaRecorder : public QObject
{
    Q_OBJECT

public:
    explicit MhaRecorder(QObject* parent = nullptr);

public slots:

private:
    // Function to convert cv::Mat image to a string in RAW format
    std::string matToRawString(const cv::Mat& image);

    // Function to write the .mha file
    bool writeMHASequence(const std::vector<cv::Mat>& images, const std::vector<Eigen::Isometry3d>& transformations, const std::string& filename);
};

#endif // MHA_RECORDER_H

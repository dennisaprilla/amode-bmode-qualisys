#ifndef BMODECONNECTION_H
#define BMODECONNECTION_H

#include <QObject>
#include <QTimer>
#include <opencv2/opencv.hpp>

class BmodeConnection : public QObject {
    Q_OBJECT

public:
    explicit BmodeConnection(QObject *parent = nullptr);
    ~BmodeConnection();

    bool openCamera(int cameraIndex = 0);
    void closeCamera();
    void startImageStream();
    void stopImageStream();

signals:
    void imageProcessed(const cv::Mat &image);

private slots:
    void processFrame();

private:
    cv::VideoCapture camera;
    cv::Mat processedImage;
    cv::Rect roi;

    QTimer *frameTimer;
};

#endif // BMODECONNECTION_H

#include "BmodeConnection.h"

//roi(662, 0, 840, 900)
//roi(0, 0, 320, 480)
BmodeConnection::BmodeConnection(QObject *parent) : QObject(parent), roi(662, 0, 840, 900), frameTimer(new QTimer(this)) {
    // Constructor
    connect(frameTimer, &QTimer::timeout, this, &BmodeConnection::processFrame);
}

BmodeConnection::~BmodeConnection() {
    // Destructor
    stopImageStream();
    closeCamera();
}

bool BmodeConnection::openCamera(int cameraIndex) {
    if(camera.open(cameraIndex)) {
        return true;
    }
    return false;
}

void BmodeConnection::closeCamera() {
    if(camera.isOpened()) {
        camera.release();
    }
}

void BmodeConnection::startImageStream() {
    if(camera.isOpened()) {
        frameTimer->start(30); // Set the interval in milliseconds (e.g., 30ms for ~33 fps)
    }
}

void BmodeConnection::stopImageStream() {
    if(frameTimer->isActive()) {
        frameTimer->stop();
    }
}

void BmodeConnection::processFrame() {
    cv::Mat frame;
    if(camera.read(frame)) {
        // Perform cropping and simple image processing here
        frame = frame(roi);

        // For example, convert to grayscale:
        cv::cvtColor(frame, processedImage, cv::COLOR_BGR2GRAY);

        // Emit the signal with the processed image
        emit imageProcessed(processedImage);
    }
}

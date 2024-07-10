#ifndef BMODE3DVISUALIZER_H
#define BMODE3DVISUALIZER_H

#include <QWidget>

#include <Qt3DCore/QTransform>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPlaneMesh>

#include <Qt3DRender/QMesh>
#include <Qt3DRender/QPaintedTextureImage>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QCullFace>
#include <QPainter>

#include <opencv2/opencv.hpp>
#include <Eigen/Geometry>

#include "bmodeconnection.h"
#include "qualisysconnection.h"
#include "qualisystransformationmanager.h"

class PaintedTextureImage : public Qt3DRender::QPaintedTextureImage {
public:
    PaintedTextureImage() : image(QImage()) {}

    void setImage(const QImage &img) {
        image = img;
        setSize(image.size());
        update(); // Trigger a repaint
    }

protected:
    void paint(QPainter *painter) override {
        QRect rect(QPoint(0, 0), size());
        painter->drawImage(rect, image);
    }

private:
    QImage image;
};

/**
 * @class Bmode3DVisualizer
 * @brief A class which handle the visualization of the 2D B-mode image in 3D environment.
 *
 * Context: The user will perform B-mode freehand scanning using this software. To make the software more intuitive,
 * it is better to visualize the real time position and orientation of the B-mode ultrasound and its image. This class
 * will visualize exactly just that.
 *
 */

class Bmode3DVisualizer : public QWidget {
    Q_OBJECT

public:
    Bmode3DVisualizer(QWidget *parent = nullptr);
    // Bmode3DVisualizer(QWidget *parent = nullptr, BmodeConnection *bmodeConnection = nullptr, QualisysConnection *qualisysConnection = nullptr);
    void show();

public slots:
    void onImageReceived(const cv::Mat &image);
    void onRigidBodyReceived(const QualisysTransformationManager &tmanager);

private:

    // Variables for storing current image and current transformation
    cv::Mat             currentImage;
    Eigen::Isometry3d   currentTransform;
    Qt3DCore::QTransform *currentQTransform;

    // Variables to controling the class if both of the data are ready
    bool imageReady     = false;
    bool rigidbodyReady = false;

    // Variables for 3D visualization
    bool firstData      = true;
    Qt3DExtras::Qt3DWindow       *view;
    Qt3DCore::QEntity            *rootEntity;

    // Mesh for origin axis
    Qt3DCore::QEntity            *axisOriginEntity;
    Qt3DCore::QEntity            *axisProbeEntity;
    Qt3DCore::QEntity            *axisImageEntity;

    // Mesh for Ultrasound image
    Qt3DCore::QEntity            *imageEntity;
    Qt3DExtras::QPlaneMesh       *planeMesh;
    Qt3DCore::QTransform         *planeTransform;
    Qt3DCore::QTransform         *planeBaseTransform;

    PaintedTextureImage          *paintedTextureImage;
    Qt3DRender::QTexture2D       *planeTexture2D;
    Qt3DExtras::QTextureMaterial *planeTextureMaterial;

    // Mesh for Probe image
    Qt3DCore::QEntity            *probeEntity;
    Qt3DRender::QMesh            *probeMesh;
    Qt3DCore::QTransform         *probeTransform;
    Qt3DCore::QTransform         *probeBaseTransform;
    Qt3DExtras::QPhongMaterial   *probeMaterial;

    // Functions for converting images and transformation to Qt Compatible
    QImage cvMatToQImage(const cv::Mat &mat);
    QMatrix4x4 eigenToQMatrix(const Eigen::Isometry3d &eigen_mat);

    Qt3DCore::QEntity* createAxis(Qt3DCore::QEntity* parent, const QVector3D& start, const QVector3D& end, const QColor& color);
    void createArrow(Qt3DCore::QEntity* rootEntity, const QColor& color, const QVector3D& rotation);
    void createAxisVector(Qt3DCore::QEntity* rootEntity);

    // This function is called in the constructor
    void initializeScene();
    // This function is called when both of the slots are ready
    void visualizeImage();
};

#endif // BMODE3DVISUALIZER_H

// Bmode3DVisualizer.cpp
// NOTE: 25/04/2024 I make the scale all in cm in the 3D visualization

#include "Bmode3DVisualizer.h"

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QForwardRenderer.h>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QConeMesh>

#include <Qt3DRender/QPaintedTextureImage>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QCamera>

#include <Qt3DRender/QpointLight.h>
#include <Qt3DRender/QDirectionalLight.h>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DExtras/QPhongMaterial>

#include <QImage>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>


Bmode3DVisualizer::Bmode3DVisualizer(QWidget *parent)
    : QWidget(parent)
{
    initializeScene();
}

/*
Bmode3DVisualizer::Bmode3DVisualizer(QWidget *parent, BmodeConnection *bmodeConnection, QualisysConnection *qualisysConnection)
    : QWidget(parent) {

    // Signal and Slot Connection --------------
    // Connect the BmodeConnection imageProcessed signal to the Bmode3DVisualizer onImageReceived slot
    connect(bmodeConnection, &BmodeConnection::imageProcessed,
            this, &Bmode3DVisualizer::onImageReceived);

    // Connect the QualisysConnection dataReceived signal to the Bmode3DVisualizer onRigidBodyReceived slot
    connect(qualisysConnection, &QualisysConnection::dataReceived,
            this, &Bmode3DVisualizer::onRigidBodyReceived);

    initializeScene();
}
*/

void Bmode3DVisualizer::initializeScene()
{
    // QtWidget container for Qt3D --------------
    // Create View from Qt3DWindow
    qputenv("QSG_RHI_BACKEND", QByteArray("opengl"));
    view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    // I don't want them to be separate window, so i will make a container
    QWidget *container = QWidget::createWindowContainer(view);
    // Make a vertical layout and add the container to this layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(container);
    // Set the layout
    setLayout(layout);

    // Qt3D setup and cameras --------------
    // Initialize the root entity for Qt3DWindow
    rootEntity = new Qt3DCore::QEntity();

    // Camera Entity
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->setPosition(QVector3D(10.0f, 10.0f, 10.0f));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setNearPlane(0.1f);
    cameraEntity->setFarPlane(1000.0f);
    cameraEntity->setFieldOfView(60.0f);
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed(30.0);
    camController->setCamera(cameraEntity);

    // Light Entity
    // Qt3DRender::QPointLight *lightPoint = new Qt3DRender::QPointLight();
    // lightPoint->setColor("white");
    // lightPoint->setIntensity(1);
    Qt3DRender::QDirectionalLight *directionalLight1 = new Qt3DRender::QDirectionalLight();
    directionalLight1->setColor("white");
    directionalLight1->setIntensity(1.0f);
    directionalLight1->setWorldDirection(QVector3D(-1, -1, -1)); // Set the direction of the light
    Qt3DRender::QDirectionalLight *directionalLight2 = new Qt3DRender::QDirectionalLight();
    directionalLight2->setColor("white");
    directionalLight2->setIntensity(1.0f);
    directionalLight2->setWorldDirection(QVector3D(-1, -1, 1)); // Set the direction of the light
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform();
    lightTransform->setTranslation(cameraEntity->position());
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    lightEntity->addComponent(directionalLight1);
    lightEntity->addComponent(directionalLight2);
    lightEntity->addComponent(lightTransform);

    // Origin axis entity (X,Y,Z), (red, green, blue)
    // createAxis(rootEntity, QVector3D(0, 0, 0), QVector3D(1, 0, 0), Qt::red);
    // createAxis(rootEntity, QVector3D(0, 0, 0), QVector3D(0, 1, 0), Qt::green);
    // createAxis(rootEntity, QVector3D(0, 0, 0), QVector3D(0, 0, 1), Qt::blue);
    Qt3DCore::QEntity *axisOriginEntity = new Qt3DCore::QEntity(rootEntity);
    createAxisVector(axisOriginEntity);

    // Ground Mesh Entity
    Qt3DExtras::QPlaneMesh *groundMesh = new Qt3DExtras::QPlaneMesh();
    groundMesh->setWidth(10);
    groundMesh->setHeight(10);
    Qt3DCore::QTransform *groundTransform = new Qt3DCore::QTransform();
    // groundTransform->setRotation(QQuaternion::fromEulerAngles(90.0f, 0.0f, 0.0f));
    // groundTransform->setTranslation(QVector3D(0.1f, 0.0f, 0.0f));
    Qt3DExtras::QPhongMaterial *groundMaterial  = new Qt3DExtras::QPhongMaterial();
    groundMaterial->setDiffuse(QColor(QRgb(0x3498db)));
    Qt3DCore::QEntity *groundEntity = new Qt3DCore::QEntity(rootEntity);
    groundEntity->addComponent(groundMesh);
    groundEntity->addComponent(groundTransform);
    groundEntity->addComponent(groundMaterial);

    // Set root entity
    view->setRootEntity(rootEntity);
}

void Bmode3DVisualizer::onImageReceived(const cv::Mat &image) {
    currentImage = image;
    imageReady = true;
    if (rigidbodyReady) {
        visualizeImage();
    }
}

void Bmode3DVisualizer::onRigidBodyReceived(const QualisysTransformationManager &tmanager) {
    // here i just take one of the transformation instead of all
    // in real case, you should take every transformation, and do something with them
    currentTransform = tmanager.getTransformationById("B_PROBE");
    rigidbodyReady = true;
    if (imageReady) {
        visualizeImage();
    }
}

void Bmode3DVisualizer::visualizeImage() {
    // Reset flags
    imageReady = false;
    rigidbodyReady = false;

    if (firstData)
    {
        // Convert the OpenCV image to a QImage
        QImage qtImage = cvMatToQImage(currentImage);
        // Convert Eigen Matrix to QMatrix and store it in QTransform
        currentQTransform = new Qt3DCore::QTransform();
        currentQTransform->setMatrix(eigenToQMatrix(currentTransform));

        // Creating Axis entity (to understand the transformation better in visualization)sss
        axisImageEntity = new Qt3DCore::QEntity(rootEntity);
        createAxisVector(axisImageEntity);
        axisImageEntity->addComponent(currentQTransform);

        // Creating Mesh Entity for B-mode probe model in 3D space
        // 1) Probe Mesh
        probeMesh = new Qt3DRender::QMesh();
        probeMesh->setSource(QUrl::fromLocalFile("C:/UsProbe_Telemed_L12.stl"));
        // 2) Probe Entity
        probeMaterial = new Qt3DExtras::QPhongMaterial();
        probeMaterial->setDiffuse(QColor(Qt::white));
        // 3) Probe Transformation
        // 3.a) Probe initial Transformation
        probeBaseTransform = new Qt3DCore::QTransform();
        probeBaseTransform->setScale(0.1f); // i put scale 0.1 because the mesh dimension is in mm, i want it to be visualized in cm
        probeBaseTransform->setRotation(QQuaternion::fromEulerAngles(90.0f, 0.0f, 0.0f));
        // 3.b) Probe current Transformation
        probeTransform = new Qt3DCore::QTransform();
        probeTransform->setMatrix(eigenToQMatrix(currentTransform)*probeBaseTransform->matrix());
        // 4) Probe Entity
        probeEntity = new Qt3DCore::QEntity(rootEntity);
        probeEntity->addComponent(probeMesh);
        probeEntity->addComponent(probeMaterial);
        probeEntity->addComponent(probeTransform);

        // Creating Plane Entity for B-mode image in 3D space
        // 1) Plane Mesh
        planeMesh = new Qt3DExtras::QPlaneMesh();
        // planeMesh->setWidth(0.004444*currentImage.cols);
        // planeMesh->setHeight(0.004444*currentImage.rows);
        planeMesh->setWidth(0.1*(4.0/90.0)*currentImage.cols);  // i put scale 0.1 because pix2mm (4.0/90.0) is in mm, i want it to be visualized in cm
        planeMesh->setHeight(0.1*(4.0/90.0)*currentImage.rows); // same here
        // 2) Plane Texture (it is a but workaround, i want texture from QImage instead of external image file)
        // 2.a) Create an instance of PaintedTextureImage and set the QImage
        paintedTextureImage = new PaintedTextureImage();
        paintedTextureImage->setImage(qtImage);
        // 2.b) Create a QTexture2D instance and add the PaintedTextureImage
        planeTexture2D = new Qt3DRender::QTexture2D();
        planeTexture2D->addTextureImage(paintedTextureImage);
        // 2.c) Create a texture material and set the QTexture2D as its texture
        planeTextureMaterial = new Qt3DExtras::QTextureMaterial();
        planeTextureMaterial->setTexture(planeTexture2D);
        // 3) Plane Transformation
        // 3.a) Plane base Transformation
        planeBaseTransform = new Qt3DCore::QTransform();
        planeBaseTransform->setRotation(QQuaternion::fromEulerAngles(0.0f, 0.0f, 0.0f));
        planeBaseTransform->setTranslation(QVector3D(0.0f, 0.0f, 2.0f));
        // 3.b) Plane current Transformation
        planeTransform = new Qt3DCore::QTransform();
        planeTransform->setMatrix(currentQTransform->matrix()*planeBaseTransform->matrix());
        // 4) Plane Entity
        // 4.a) The image plane itself
        imageEntity = new Qt3DCore::QEntity(rootEntity);
        imageEntity->addComponent(planeMesh);
        imageEntity->addComponent(planeTextureMaterial);
        imageEntity->addComponent(planeTransform);


        firstData = false;
    }

    else
    {
        // Convert the OpenCV image to a QImagete
        QImage qtImage = cvMatToQImage(currentImage);
        // Convert Eigen Matrix to QMatrix and store it in QTransform
        currentQTransform->setMatrix(eigenToQMatrix(currentTransform));

        // Probe Transform
        probeTransform->setMatrix(currentQTransform->matrix()*probeBaseTransform->matrix());

        // Plane texture, the pipeline following the above
        paintedTextureImage->setImage(qtImage);
        planeTexture2D->addTextureImage(paintedTextureImage);
        planeTextureMaterial->setTexture(planeTexture2D);
        // Plane Transform
        planeTransform->setMatrix(currentQTransform->matrix()*planeBaseTransform->matrix());

    }
}

// Function to convert cv::Mat to QImage
QImage Bmode3DVisualizer::cvMatToQImage(const cv::Mat &mat) {

    switch (mat.type()) {

    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        // Use copy to detach from original data, to ensure that the QImage is a deep copy
        // and does not depend on the original cv::Mat data
        return image.copy();
    }

    // 8-bit, 3 channel
    case CV_8UC3: {
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        // Swap RGB to BGR and detach because OpenCV uses BGR format by default, while QImage expects RGB.
        return image.rgbSwapped().copy();
    }

    // 8-bit, 1 channel
    case CV_8UC1: {
        QVector<QRgb> colorTable;
        for (int i = 0; i < 256; i++)
            colorTable.push_back(qRgb(i, i, i));
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        image.setColorTable(colorTable);
        return image.copy(); // Use copy to detach from original data
    }

    default:
        qWarning("cvMatToQImage() - cv::Mat image type not handled in switch:");
        return QImage();
    }

}

// Function to convert Eigen::Isometry3d to QMatrix4x4
QMatrix4x4 Bmode3DVisualizer::eigenToQMatrix(const Eigen::Isometry3d &eigen_mat) {

    // Convert to Matrix4f
    Eigen::Matrix4f mat = eigen_mat.matrix().cast<float>();

    // I am using dummy data for now, so i need to adjust a little bit with the translation
    QMatrix4x4 currentQMat = QMatrix4x4(mat.data()).transposed();
    QVector3D translation  = currentQMat.column(3).toVector3D();
    currentQMat.setColumn(3, QVector4D(0.01*translation, 1.0f));
    return currentQMat;

    // Transpose to match row-major order because Eigen uses column-major order by default,
    // while Qt uses row-major order for its matrices.
    //return QMatrix4x4(mat.data()).transposed();
}

// Function to create a line entity representing an axis
Qt3DCore::QEntity* Bmode3DVisualizer::createAxis(Qt3DCore::QEntity* parent, const QVector3D& start, const QVector3D& end, const QColor& color) {
    auto *geometry = new Qt3DCore::QGeometry(parent);

    // Position vertices
    QByteArray bufferBytes;
    bufferBytes.resize(3 * 2 * sizeof(float)); // 2 vertices, 3 floats each
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    *positions++ = start.x();
    *positions++ = start.y();
    *positions++ = start.z();
    *positions++ = end.x();
    *positions++ = end.y();
    *positions++ = end.z();

    // Create buffer and fill it with vertex data
    auto *buf = new Qt3DCore::QBuffer(geometry);
    buf->setData(bufferBytes);

    // Create position attribute
    auto *positionAttribute = new Qt3DCore::QAttribute(geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(buf);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(2);
    geometry->addAttribute(positionAttribute);

    // Create a line mesh
    auto *line = new Qt3DRender::QGeometryRenderer(parent);
    line->setGeometry(geometry);
    line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

    // Create material
    auto *material = new Qt3DExtras::QPhongMaterial(parent);
    material->setAmbient(color);

    // Create entity for the axis
    auto *axisEntity = new Qt3DCore::QEntity(parent);
    axisEntity->addComponent(line);
    axisEntity->addComponent(material);

    return axisEntity;
}

void Bmode3DVisualizer::createArrow(Qt3DCore::QEntity* rootEntity, const QColor& color, const QVector3D& rotation) {
    auto *cylinder = new Qt3DExtras::QCylinderMesh();
    cylinder->setRadius(0.05f);
    cylinder->setLength(1.0f);
    cylinder->setRings(100);
    cylinder->setSlices(20);

    auto *cone = new Qt3DExtras::QConeMesh();
    cone->setTopRadius(0.0f);
    cone->setBottomRadius(0.1f);
    cone->setLength(0.2f);
    cone->setRings(50);
    cone->setSlices(20);

    auto *cylinderEntity = new Qt3DCore::QEntity(rootEntity);
    cylinderEntity->addComponent(cylinder);

    auto *coneEntity = new Qt3DCore::QEntity(rootEntity);
    coneEntity->addComponent(cone);

    auto *material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(color);

    cylinderEntity->addComponent(material);
    coneEntity->addComponent(material);

    auto *cylinderTransform = new Qt3DCore::QTransform();
    cylinderTransform->setTranslation(QVector3D(0, 0.5f, 0));
    cylinderEntity->addComponent(cylinderTransform);

    auto *coneTransform = new Qt3DCore::QTransform();
    coneTransform->setTranslation(QVector3D(0, 1.0f, 0));
    coneEntity->addComponent(coneTransform);

    auto *arrowTransform = new Qt3DCore::QTransform();
    arrowTransform->setRotation(QQuaternion::fromEulerAngles(rotation.x(), rotation.y(), rotation.z()));
    rootEntity->addComponent(arrowTransform);
}

void Bmode3DVisualizer::createAxisVector(Qt3DCore::QEntity* parentEntity) {
    Qt3DCore::QEntity *arrowX = new Qt3DCore::QEntity(parentEntity);
    createArrow(arrowX, Qt::red, QVector3D(0, 0, -90));
    Qt3DCore::QEntity *arrowY = new Qt3DCore::QEntity(parentEntity);
    createArrow(arrowY, Qt::green, QVector3D(0, 0, 0));
    Qt3DCore::QEntity *arrowZ = new Qt3DCore::QEntity(parentEntity);
    createArrow(arrowZ, Qt::blue, QVector3D(90, 0, 0));
}

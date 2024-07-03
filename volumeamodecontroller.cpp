#include <filesystem>
#include <cmath>
#include "volumeamodecontroller.h"
#include "amodedatamanipulator.h"

bool readCsvIntoEigenVectorXd(const QString &filePath, Eigen::VectorXd &vector1, Eigen::VectorXd &vector2) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading";
        return false;
    }

    QTextStream in(&file);
    int lineNumber = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(';');

        // Resize the Eigen::VectorXd to fit the number of values in the CSV row
        if (lineNumber == 0) {
            vector1.resize(values.size());
        } else if (lineNumber == 1) {
            vector2.resize(values.size());
        }

        int colIndex = 0;
        for (const QString &val : values) {
            bool ok;
            double num = val.toDouble(&ok);
            if (ok) {
                if (lineNumber == 0) {
                    vector1(colIndex) = num;
                } else if (lineNumber == 1) {
                    vector2(colIndex) = num;
                }
                ++colIndex;
            }
        }
        ++lineNumber;
        if (lineNumber > 1) break; // We only need two rows
    }
    file.close();
    return true;
}

VolumeAmodeController::VolumeAmodeController(QObject *parent, Q3DScatter *scatter, std::vector<AmodeConfig::Data> amodegroupdata)
    : QObject{parent}, scatter_(scatter), amodegroupdata_(amodegroupdata)
{
    // // The code below is for [prototying]
    Eigen::VectorXd vector1, vector2;
    if (!readCsvIntoEigenVectorXd("D:/testamodesignal_26_3500.csv", vector1, vector2)) {
        qDebug() << "Failed to read the CSV file into Eigen vectors.";
    }
    amode3dsignal_.row(0) = vector2 * 0.001; // x-coordinate
    amode3dsignal_.row(1) = vector1; // y-coordinate
    amode3dsignal_.row(2).setZero(); // z-coordinate
    amode3dsignal_.row(3).setOnes(); // 1 (homogeneous)

    // initialize transformations
    currentT_holder_camera = Eigen::Isometry3d::Identity();
    for(std::size_t i = 0; i < amodegroupdata_.size(); ++i)
    {
        currentT_ustip_camera.push_back(Eigen::Isometry3d::Identity());
        currentT_ustip_camera_Qt.push_back(Eigen::Isometry3d::Identity());
    }
    // initialize points
    for(std::size_t i = 0; i < amodegroupdata_.size(); ++i)
    {
        all_amode3dsignal_.push_back(amode3dsignal_);
    }

    // initialize the 3ditem and its setting
    // initMeshItem();

    // initialize the object (for temp, later, i need to change the model based on the group name)
    // newObject("D:/model/holder_new8.obj", amodegroupdata_.at(0).groupname);

    // initialize scatter data array and series
    // initSeries();

    // initialize mode
    setSignalDisplayMode(0);
}

VolumeAmodeController::~VolumeAmodeController()
{
    // delete all the series inside the scatter
    for (QScatter3DSeries *series : scatter_->seriesList()) {
        if (series->name() == "amode3dsignal" || series->name() == "amode3dorigin") {
            scatter_->removeSeries(series);
        }
    }
}

void VolumeAmodeController::initMeshItem()
{
    // initialize QCustom3DItem
    meshItem_ = new QCustom3DItem();
    // Set the texture, simple red does the job
    QImage color = QImage(2, 2, QImage::Format_RGB32);
    color.fill(Qt::red);
    meshItem_->setTextureImage(color);
    // Set other settings, just to make sure uneccessary additional process
    meshItem_->setShadowCasting(false);
}

void VolumeAmodeController::initSeries()
{

}

void VolumeAmodeController::setSignalDisplayMode(int mode)
{
    /* We display our 3D signal with the envelope of our signal.
     *
     * However, because the signal basically a 2D representation in 3D space,
     * in certain angle, you can't see the differences in amplitude in the envelope signal.
     * It becomes a line in certain angle.
     *
     * So, we decided to provide several modes to show our envelope signal: Mode 1, 2, and 4.
     * Mode 1 is just normal 1 envelope signal.
     * Mode 2 is 2 envelope signal. The original, and the original that is rotated 180 degrees along directional axis.
     *        so it is like and envelope in up and down direction.
     * Mode 4 is 4 envelope signal. The original, and the original that is rotated 90, 180, 270 degrees along directional axis.
     *        you can imagine how it will be, come on.
     *
     */

    // delete all the rotation matrix inside this variable
    rotation_signaldisplay.clear();

    // initialize angle degrees
    std::vector<int> angle_degrees;
    // angle_degrees will depend on user choice
    if (mode==0)
    {
        n_signaldisplay = 1;
        angle_degrees.insert(angle_degrees.end(), {0});
    }
    else if (mode==1)
    {
        n_signaldisplay = 2;
        angle_degrees.insert(angle_degrees.end(), {0, 180});
    }
    else if (mode == 2)
    {
        n_signaldisplay = 4;
        angle_degrees.insert(angle_degrees.end(), {0, 90, 180, 270});
    }

    for (size_t i = 0; i < angle_degrees.size(); ++i)
    {
        // specify the rotation in radian
        double angle_radians = angle_degrees.at(i) * M_PI / 180.0;
        // create the rotation matrix
        Eigen::Matrix4d current_R;
        current_R << cos(angle_radians),  0, sin(angle_radians), 0,
                     0,                   1,                  0, 0,
                     -sin(angle_radians), 0, cos(angle_radians), 0,
                     0,                   0,                  0, 1;
        // store the rotation matrix
        rotation_signaldisplay.push_back(current_R);
    }
}

// void VolumeAmodeController::setAmodeGroupData(std::vector<AmodeConfig::Data> amodegroupdata)
// {
//     amodegroupdata_ = amodegroupdata;
// }

void VolumeAmodeController::newObject(std::string path, std::string name)
{
    std::string objpath = path;
    if (!std::filesystem::exists(path))
    {
        qDebug() << "Object file to represent the ultrasound holder can not be found. Use the default instead";
        objpath = "D:/model/cube2c.obj";
    }
    // You should change this to identity. Here is not because when debugging i used dummy obj
    meshItem_->setScalingAbsolute(false);
    meshItem_->setScaling(QVector3D(5.0f, 5.0f, 5.0f));

    // for QCustom3DItem you can only use .obj file (check https://doc.qt.io/qt-6/qml-qtdatavisualization-custom3ditem.html for other specification)
    // If you only have stl file. Better use Blender, import the .stl -> add material -> smart uv project -> export .obj -> check all geometry, uncheck materal.
    meshItem_->setObjectName(QString::fromStdString(name));
    meshItem_->setMeshFile(QString::fromStdString(objpath));

    // Add the item to the scatter plot
    scatter_->addCustomItem(meshItem_);
}

void VolumeAmodeController::updateTransformations(Eigen::Isometry3d currentT_holder_camera)
{
    // get the current transformation matrix from qualisys
    Eigen::Matrix3d tmp_R = currentT_holder_camera.rotation();
    Eigen::Vector3d tmp_t = currentT_holder_camera.translation();

    // initialize transformation matrix for Qt. In Qt, the representation of rotation matrix
    // is different. You need to transpose it so that it will be the same as representation in Eigen.
    Eigen::Isometry3d currentT_holder_camera_Qt = Eigen::Isometry3d::Identity();
    currentT_holder_camera_Qt.linear()          = tmp_R.transpose();
    currentT_holder_camera_Qt.translation()     = tmp_t;

    // update the T_ustip_holder. Loop for each ustip inside the holder
    for(std::size_t i = 0; i < amodegroupdata_.size(); ++i)
    {
        // get the local_R data from amodeconfig
        Eigen::Vector3d local_R_euler(amodegroupdata_.at(i).local_R.at(0), amodegroupdata_.at(i).local_R.at(1), amodegroupdata_.at(i).local_R.at(2));
        // convert it to radians
        Eigen::Vector3d local_R_radians = local_R_euler * (M_PI / 180.0);
        // convert it to rotation matrix
        Eigen::Matrix3d local_R_matrix;
        local_R_matrix = Eigen::AngleAxisd(local_R_radians.x(), Eigen::Vector3d::UnitX()) *
                         Eigen::AngleAxisd(local_R_radians.y(), Eigen::Vector3d::UnitY()) *
                         Eigen::AngleAxisd(local_R_radians.z(), Eigen::Vector3d::UnitZ());

        // convert local_t from amode config data in with Eigen
        Eigen::Vector3d local_t(amodegroupdata_.at(i).local_t.at(0), amodegroupdata_.at(i).local_t.at(1), amodegroupdata_.at(i).local_t.at(2));

        // pack local_R and local_t into transformation matrix with Eigen
        Eigen::Isometry3d currentT_ustip_holder = Eigen::Isometry3d::Identity();
        currentT_ustip_holder.linear() = local_R_matrix;
        currentT_ustip_holder.translation() = local_t;

        // now, do the same thing also but for Qt matrix representation
        Eigen::Isometry3d currentT_ustip_holder_Qt = Eigen::Isometry3d::Identity();
        currentT_ustip_holder_Qt.linear() = local_R_matrix.transpose();
        currentT_ustip_holder_Qt.translation() = local_t;

        // store everything to our vectors. Transformation is now updated
        currentT_ustip_camera.at(i) = currentT_holder_camera * currentT_ustip_holder;
        currentT_ustip_camera_Qt.at(i) = currentT_holder_camera_Qt * currentT_ustip_holder_Qt;
    }
}


void VolumeAmodeController::onAmodeSignalReceived(const std::vector<uint16_t> &usdata_uint16_)
{
    // get the amode data
    QVector<int16_t> tmp(usdata_uint16_.begin(), usdata_uint16_.end());
    amodesignal_ = tmp;

    // set the flag to be true...
    amodesignalReady = true;
    // ...and only continue to visualize data if rigidbody data already arrive
    if (rigidbodyReady) {
        visualize3DSignal();
    }
}

void VolumeAmodeController::onRigidBodyReceived(const QualisysTransformationManager &tmanager)
{
    // temporary code, i should get the transformation based on the group amodegroupdata_->at(0).groupname
    currentT_holder_camera = tmanager.getTransformationById("TB-M");

    // set the flag to be true...
    rigidbodyReady = true;
    // ...and only continue to visualize data if the amode signal data already arrive
    if (amodesignalReady) {
        visualize3DSignal();
    }

}

void VolumeAmodeController::visualize3DSignal()
{
    // if this function is executed, it means both of rigid body data and amode data already arrived.
    // first, reset the flag back to false
    amodesignalReady = false;
    rigidbodyReady = false;

    // Then, starting from here, let's do visualization...

    // update all necessary transformations
    updateTransformations(currentT_holder_camera);

    // [prototyping]
    int offset_x = -450;
    int offset_y = -125;
    int offset_z = -115;

    // delete all the series inside the scatter. So everytime there is a new rigidbody data coming
    // from qualisys, we should remove all the scatter data in our scatter series
    for (QScatter3DSeries *series : scatter_->seriesList()) {
        if (series->name() == "amode3dsignal" || series->name() == "amode3dorigin") {
            scatter_->removeSeries(series);
        }
    }

    // Create a QScatterDataArray to store the origins of the signals.
    // I wrote this outside the loop (below), because i want the scatter for origin point to be one scatter object,
    // so that i could set the configuration of the visualization as a group
    QScatterDataArray *originArray = new QScatterDataArray;
    originArray->resize(amodegroupdata_.size());

    // For the case of scatter for the signal data themshelves, i will make them separately,
    // each signal has its own scatter object, so that i could make differentiation in color for each signal.
    // So i will need a loop for how much signal i have
    for(std::size_t i = 0; i < amodegroupdata_.size(); ++i)
    {
        // select the row from the whole amode data
        QVector<int16_t> amodesignal_rowsel = AmodeDataManipulator::getRow(amodesignal_, amodegroupdata_.at(i).number-1, 3500);
        // convert to Eigen::VectorXd
        Eigen::VectorXd amodesignal_rowsel_eigenVector = Eigen::Map<const Eigen::Matrix<int16_t, Eigen::Dynamic, 1>>(
                                                                    amodesignal_rowsel.constData(), amodesignal_rowsel.size()).cast<double>();
        // remove the near field disturbance
        amodesignal_rowsel_eigenVector.head(200).setZero();
        // store it to our amode3dsignal_
        amode3dsignal_.row(0) = amodesignal_rowsel_eigenVector * 0.0015; // x-coordinate

        // Get the size of the data (that is the samples in the signal)
        int arraysize = amode3dsignal_.cols();

        // Since we provided several display mode for visualizing amode 3d signal, we need to provide
        // a variable to place all of those display modes
        Eigen::Matrix<double, 4, Eigen::Dynamic> current_amode3dsignal_display(4, arraysize * n_signaldisplay);

        // Let's populate the all the rotated signal data to it
        for (std::size_t j = 0; j < rotation_signaldisplay.size(); ++j)
        {
            int start_column = j*arraysize;
            current_amode3dsignal_display.block(0, start_column, 4, arraysize) = currentT_ustip_camera_Qt.at(i).matrix() * rotation_signaldisplay.at(j) * amode3dsignal_;
        }

        // This is the QScatterDataArray object for the signal data, each loop will be new object
        QScatterDataArray *dataArray = new QScatterDataArray;
        // resize the data array
        dataArray->resize(arraysize * n_signaldisplay);

        // We need to copy copy the points from the Eigen matrix to the QScatterDataArray one by one
        // There is no other way, this is bullshit from QtDataVisualization, i hate it so much
        for (int j = 0; j < arraysize * n_signaldisplay; ++j) {

            (*dataArray)[j].setPosition( QVector3D(current_amode3dsignal_display(0, j) +offset_x,
                                                  current_amode3dsignal_display(1, j) +offset_y,
                                                  current_amode3dsignal_display(2, j) +offset_z));
        }

        // Using this loop, i will add data to my originArray, that is the first data in the signal.
        // To be honest, it is not exactly the origin of the signal, but hey, who the fuck can see 0.01 mm differences in the visualization?
        (*originArray)[i].setPosition( QVector3D(current_amode3dsignal_display(0, 0) +offset_x,
                                                current_amode3dsignal_display(1, 0) +offset_y,
                                                current_amode3dsignal_display(2, 0) +offset_z));

        // Create new series where the QScatterDataArray object will be added
        QScatter3DSeries *series = new QScatter3DSeries();
        series->setName("amode3dsignal");
        series->setItemSize(0.04f);
        series->setMesh(QAbstract3DSeries::MeshPoint);
        series->dataProxy()->resetArray(dataArray);

        // add the current amode data (series) to our scatter object
        scatter_->addSeries(series);
    }

    // Now, i want to create new series for my originData
    QScatter3DSeries *series = new QScatter3DSeries();
    series->setName("amode3dorigin");
    series->setItemSize(0.2f);
    series->setMesh(QAbstract3DSeries::MeshPoint);
    series->setBaseColor(Qt::red);
    series->dataProxy()->resetArray(originArray);

    // add the current origin point data (series) to our scatter object
    scatter_->addSeries(series);
}

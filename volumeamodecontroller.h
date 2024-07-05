#ifndef VOLUMEAMODECONTROLLER_H
#define VOLUMEAMODECONTROLLER_H

#include <Eigen/Dense>

#include <QObject>
#include <QtDataVisualization>

#include "amodeconfig.h"
#include "qualisysconnection.h"
#include "qualisystransformationmanager.h"

class VolumeAmodeController : public QObject
{
    Q_OBJECT

public:
    VolumeAmodeController(QObject *parent = nullptr, Q3DScatter *scatter = nullptr, std::vector<AmodeConfig::Data> amodegroupdata = std::vector<AmodeConfig::Data>());
    ~VolumeAmodeController();

    void setSignalDisplayMode(int mode);
    // void setAmodeGroupData(std::vector<AmodeConfig::Data> amodegroupdata);
    void newObject(std::string path, std::string name);
    void updateTransformations(Eigen::Isometry3d T);

public slots:
    void onAmodeSignalReceived(const std::vector<uint16_t> &usdata_uint16_);
    void onRigidBodyReceived(const QualisysTransformationManager &tmanager);

private:
    void initMeshItem();
    void initSeries();
    void visualize3DSignal();

    // all variables related to visualization with QCustomPlot
    QCustom3DItem *meshItem_ = nullptr;
    Q3DScatter *scatter_;
    std::vector<QScatterDataArray> all_dataArray_;
    std::vector<QScatter3DSeries> all_series_;

    // all variables related to amode signal
    int downsample_nsample_;
    double downsample_ratio = 2.0;
    bool isDownsample       = true;

    std::vector<AmodeConfig::Data> amodegroupdata_;
    QVector<int16_t> amodesignal_;
    Eigen::Matrix<double, 4, Eigen::Dynamic> amode3dsignal_;
    std::vector<Eigen::Matrix<double, 4, Eigen::Dynamic>> all_amode3dsignal_;

    // all variables related to ultrasound specification
    Eigen::VectorXd us_dvector_;
    Eigen::VectorXd us_tvector_;

    // all variables related to transformations
    Eigen::Isometry3d currentT_holder_camera;
    std::vector<Eigen::Isometry3d> currentT_ustip_camera;
    std::vector<Eigen::Isometry3d> currentT_ustip_camera_Qt;

    // variable that controls "soft synchronization" data from qualisys and A-mode machine.
    bool amodesignalReady = false;
    bool rigidbodyReady = false;

    // variable that handle the display of 3d signal
    int n_signaldisplay = 1;
    std::vector<Eigen::Matrix4d> rotation_signaldisplay;

signals:
};

#endif // VOLUMEAMODECONTROLLER_H

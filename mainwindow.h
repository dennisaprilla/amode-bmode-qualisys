#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

#include "amodeconnection.h"
#include "amodeconfig.h"
#include "bmodeconnection.h"
#include "bmode3dvisualizer.h"
#include "qcustomplot.h"
#include "qualisysconnection.h"
#include "mhawriter.h"
#include "mhareader.h"
#include "volume3dcontroller.h"
#include "volumeamodecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void displayImage(const cv::Mat &image);
    void displayUSsignal(const std::vector<uint16_t> &usdata_uint16_);
    void disconnectUSsignal();
    void updateQualisysText(const QualisysTransformationManager &tmanager);

    void volumeReconstructorCmdFinished();
    void volumeReconstructorCmdStandardOutput();
    void volumeReconstructorCmdStandardError();

private slots:
    // void on_pushButton_startCamera_clicked();
    // void on_pushButton_qualisysConnect_clicked();
    void on_pushButton_bmode2d3d_clicked();
    void on_pushButton_mhaRecord_clicked();

    void on_pushButton_amodeConnect_clicked();
    void on_pushButton_amodeConfig_clicked();
    void on_comboBox_amodeNumber_textActivated(const QString &arg1);

    void on_pushButton_volumeLoad_clicked();
    void on_pushButton_volumeReconstruct_clicked();
    void on_pushButton_volumeBrowseConfig_clicked();
    void on_pushButton_volumeBrowseRecording_clicked();
    void on_checkBox_volumeShow3DSignal_stateChanged(int arg1);

    void on_pushButton_mhaPath_clicked();
    void on_pushButton_volumeBrowseOutput_clicked();
    void on_checkBox_autoReconstruct_stateChanged(int arg1);
    void on_comboBox_volume3DSignalMode_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    AmodeConnection *myAmodeConnection;
    AmodeConfig *myAmodeConfig = nullptr;
    BmodeConnection *myBmodeConnection;
    QualisysConnection *myQualisysConnection;
    Bmode3DVisualizer *myBmode3Dvisualizer;
    MHAWriter *myMHAWriter;
    MHAReader *myMHAReader = nullptr;
    Volume3DController *myVolume3DController = nullptr;
    VolumeAmodeController *myVolumeAmodeController = nullptr;

    std::vector<QCustomPlot*> amodePlots;
    Q3DScatter *scatter;

    QProcess* process;

    bool isMHArecord = true;
    int currentCameraIndex;

    bool isBmode2d3dStream = true;
    bool isBmode2d3dFirstStream = true;

    bool isAmodeStream = true;

};
#endif // MAINWINDOW_H

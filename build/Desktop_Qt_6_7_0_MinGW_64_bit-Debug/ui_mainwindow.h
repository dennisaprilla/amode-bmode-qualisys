/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_volume;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *layout_volume;
    QGridLayout *horizontalLayout_volumeMenu;
    QLineEdit *lineEdit_volumeConfig;
    QLabel *label_volumeConfig;
    QLineEdit *lineEdit_volumeSource;
    QPushButton *pushButton_volumeBrowseRecording;
    QPushButton *pushButton_volumeReconstruct;
    QPushButton *pushButton_volumeLoad;
    QLineEdit *lineEdit_volumeOutput;
    QPushButton *pushButton_volumeBrowseOutput;
    QLabel *label_volumeExisting;
    QLineEdit *lineEdit_volumeRecording;
    QLabel *label_volumeOutput;
    QPushButton *pushButton_volumeBrowseConfig;
    QLabel *label_volumeRecording;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_volumePixelValMin;
    QSlider *horizontalSlider_volumeThreshold;
    QLabel *label_volumePixelValMax;
    QLabel *label_volumeThreshold;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_volumeShow3DSignal;
    QComboBox *comboBox_volume3DSignalMode;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_volume;
    QGroupBox *groupBox_Bmode2D;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *layout_Bmode2D;
    QHBoxLayout *layout_Bmode2D3D_menu;
    QLabel *label_4;
    QComboBox *comboBox_camera;
    QLabel *label_qualisysIP;
    QLineEdit *lineEdit_qualisysIP;
    QLabel *label_qualisysPort;
    QLineEdit *lineEdit_qualisysPort;
    QPushButton *pushButton_bmode2d3d;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_mhaPath;
    QPushButton *pushButton_mhaPath;
    QPushButton *pushButton_mhaRecord;
    QCheckBox *checkBox_autoReconstruct;
    QHBoxLayout *layout_Bmode2D3D_content;
    QLabel *label_imageDisplay;
    QTextEdit *textEdit_qualisysLog;
    QGroupBox *groupBox_Amode;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *layout_Amode;
    QHBoxLayout *layout_Amode_menu;
    QLabel *label;
    QLineEdit *lineEdit_amodeIP;
    QLabel *label_2;
    QLineEdit *lineEdit_amodePort;
    QPushButton *pushButton_amodeConnect;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_amodeConfig;
    QPushButton *pushButton_amodeConfig;
    QComboBox *comboBox_amodeNumber;
    QGridLayout *gridLayout_amodeSignals;
    QCustomPlot *customPlot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        groupBox_volume = new QGroupBox(centralwidget);
        groupBox_volume->setObjectName("groupBox_volume");
        verticalLayout_2 = new QVBoxLayout(groupBox_volume);
        verticalLayout_2->setObjectName("verticalLayout_2");
        layout_volume = new QVBoxLayout();
        layout_volume->setObjectName("layout_volume");
        horizontalLayout_volumeMenu = new QGridLayout();
        horizontalLayout_volumeMenu->setObjectName("horizontalLayout_volumeMenu");
        lineEdit_volumeConfig = new QLineEdit(groupBox_volume);
        lineEdit_volumeConfig->setObjectName("lineEdit_volumeConfig");
        lineEdit_volumeConfig->setEnabled(false);

        horizontalLayout_volumeMenu->addWidget(lineEdit_volumeConfig, 0, 1, 1, 1);

        label_volumeConfig = new QLabel(groupBox_volume);
        label_volumeConfig->setObjectName("label_volumeConfig");

        horizontalLayout_volumeMenu->addWidget(label_volumeConfig, 0, 0, 1, 1);

        lineEdit_volumeSource = new QLineEdit(groupBox_volume);
        lineEdit_volumeSource->setObjectName("lineEdit_volumeSource");
        lineEdit_volumeSource->setEnabled(false);

        horizontalLayout_volumeMenu->addWidget(lineEdit_volumeSource, 0, 4, 1, 1);

        pushButton_volumeBrowseRecording = new QPushButton(groupBox_volume);
        pushButton_volumeBrowseRecording->setObjectName("pushButton_volumeBrowseRecording");
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("document-open")));
        pushButton_volumeBrowseRecording->setIcon(icon);

        horizontalLayout_volumeMenu->addWidget(pushButton_volumeBrowseRecording, 1, 2, 1, 1);

        pushButton_volumeReconstruct = new QPushButton(groupBox_volume);
        pushButton_volumeReconstruct->setObjectName("pushButton_volumeReconstruct");

        horizontalLayout_volumeMenu->addWidget(pushButton_volumeReconstruct, 3, 0, 1, 3);

        pushButton_volumeLoad = new QPushButton(groupBox_volume);
        pushButton_volumeLoad->setObjectName("pushButton_volumeLoad");
        pushButton_volumeLoad->setIcon(icon);

        horizontalLayout_volumeMenu->addWidget(pushButton_volumeLoad, 0, 5, 1, 1);

        lineEdit_volumeOutput = new QLineEdit(groupBox_volume);
        lineEdit_volumeOutput->setObjectName("lineEdit_volumeOutput");
        lineEdit_volumeOutput->setEnabled(false);

        horizontalLayout_volumeMenu->addWidget(lineEdit_volumeOutput, 2, 1, 1, 1);

        pushButton_volumeBrowseOutput = new QPushButton(groupBox_volume);
        pushButton_volumeBrowseOutput->setObjectName("pushButton_volumeBrowseOutput");
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("folder-open")));
        pushButton_volumeBrowseOutput->setIcon(icon1);

        horizontalLayout_volumeMenu->addWidget(pushButton_volumeBrowseOutput, 2, 2, 1, 1);

        label_volumeExisting = new QLabel(groupBox_volume);
        label_volumeExisting->setObjectName("label_volumeExisting");

        horizontalLayout_volumeMenu->addWidget(label_volumeExisting, 0, 3, 1, 1);

        lineEdit_volumeRecording = new QLineEdit(groupBox_volume);
        lineEdit_volumeRecording->setObjectName("lineEdit_volumeRecording");
        lineEdit_volumeRecording->setEnabled(false);

        horizontalLayout_volumeMenu->addWidget(lineEdit_volumeRecording, 1, 1, 1, 1);

        label_volumeOutput = new QLabel(groupBox_volume);
        label_volumeOutput->setObjectName("label_volumeOutput");

        horizontalLayout_volumeMenu->addWidget(label_volumeOutput, 2, 0, 1, 1);

        pushButton_volumeBrowseConfig = new QPushButton(groupBox_volume);
        pushButton_volumeBrowseConfig->setObjectName("pushButton_volumeBrowseConfig");
        pushButton_volumeBrowseConfig->setIcon(icon);

        horizontalLayout_volumeMenu->addWidget(pushButton_volumeBrowseConfig, 0, 2, 1, 1);

        label_volumeRecording = new QLabel(groupBox_volume);
        label_volumeRecording->setObjectName("label_volumeRecording");

        horizontalLayout_volumeMenu->addWidget(label_volumeRecording, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_volumePixelValMin = new QLabel(groupBox_volume);
        label_volumePixelValMin->setObjectName("label_volumePixelValMin");

        horizontalLayout_2->addWidget(label_volumePixelValMin);

        horizontalSlider_volumeThreshold = new QSlider(groupBox_volume);
        horizontalSlider_volumeThreshold->setObjectName("horizontalSlider_volumeThreshold");
        horizontalSlider_volumeThreshold->setMinimum(50);
        horizontalSlider_volumeThreshold->setMaximum(200);
        horizontalSlider_volumeThreshold->setOrientation(Qt::Horizontal);
        horizontalSlider_volumeThreshold->setTickPosition(QSlider::TicksBothSides);

        horizontalLayout_2->addWidget(horizontalSlider_volumeThreshold);

        label_volumePixelValMax = new QLabel(groupBox_volume);
        label_volumePixelValMax->setObjectName("label_volumePixelValMax");
        label_volumePixelValMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_volumePixelValMax);


        horizontalLayout_volumeMenu->addLayout(horizontalLayout_2, 1, 4, 2, 2);

        label_volumeThreshold = new QLabel(groupBox_volume);
        label_volumeThreshold->setObjectName("label_volumeThreshold");

        horizontalLayout_volumeMenu->addWidget(label_volumeThreshold, 1, 3, 2, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        checkBox_volumeShow3DSignal = new QCheckBox(groupBox_volume);
        checkBox_volumeShow3DSignal->setObjectName("checkBox_volumeShow3DSignal");

        horizontalLayout->addWidget(checkBox_volumeShow3DSignal);

        comboBox_volume3DSignalMode = new QComboBox(groupBox_volume);
        comboBox_volume3DSignalMode->addItem(QString());
        comboBox_volume3DSignalMode->addItem(QString());
        comboBox_volume3DSignalMode->addItem(QString());
        comboBox_volume3DSignalMode->setObjectName("comboBox_volume3DSignalMode");
        comboBox_volume3DSignalMode->setEnabled(false);

        horizontalLayout->addWidget(comboBox_volume3DSignalMode);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(groupBox_volume);
        pushButton->setObjectName("pushButton");
        QIcon icon2(QIcon::fromTheme(QString::fromUtf8("dialog-information")));
        pushButton->setIcon(icon2);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox_volume);
        pushButton_2->setObjectName("pushButton_2");
        QIcon icon3(QIcon::fromTheme(QString::fromUtf8("zoom-in")));
        pushButton_2->setIcon(icon3);

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(groupBox_volume);
        pushButton_3->setObjectName("pushButton_3");
        QIcon icon4(QIcon::fromTheme(QString::fromUtf8("zoom-out")));
        pushButton_3->setIcon(icon4);

        horizontalLayout->addWidget(pushButton_3);


        horizontalLayout_volumeMenu->addLayout(horizontalLayout, 3, 4, 1, 2);


        layout_volume->addLayout(horizontalLayout_volumeMenu);

        verticalSpacer_volume = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layout_volume->addItem(verticalSpacer_volume);

        layout_volume->setStretch(1, 1);

        verticalLayout_2->addLayout(layout_volume);


        gridLayout->addWidget(groupBox_volume, 0, 1, 2, 1);

        groupBox_Bmode2D = new QGroupBox(centralwidget);
        groupBox_Bmode2D->setObjectName("groupBox_Bmode2D");
        verticalLayout_3 = new QVBoxLayout(groupBox_Bmode2D);
        verticalLayout_3->setObjectName("verticalLayout_3");
        layout_Bmode2D = new QVBoxLayout();
        layout_Bmode2D->setObjectName("layout_Bmode2D");
        layout_Bmode2D->setSizeConstraint(QLayout::SetMaximumSize);
        layout_Bmode2D3D_menu = new QHBoxLayout();
        layout_Bmode2D3D_menu->setObjectName("layout_Bmode2D3D_menu");
        layout_Bmode2D3D_menu->setSizeConstraint(QLayout::SetFixedSize);
        label_4 = new QLabel(groupBox_Bmode2D);
        label_4->setObjectName("label_4");

        layout_Bmode2D3D_menu->addWidget(label_4);

        comboBox_camera = new QComboBox(groupBox_Bmode2D);
        comboBox_camera->addItem(QString());
        comboBox_camera->addItem(QString());
        comboBox_camera->addItem(QString());
        comboBox_camera->addItem(QString());
        comboBox_camera->addItem(QString());
        comboBox_camera->setObjectName("comboBox_camera");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_camera->sizePolicy().hasHeightForWidth());
        comboBox_camera->setSizePolicy(sizePolicy);

        layout_Bmode2D3D_menu->addWidget(comboBox_camera);

        label_qualisysIP = new QLabel(groupBox_Bmode2D);
        label_qualisysIP->setObjectName("label_qualisysIP");

        layout_Bmode2D3D_menu->addWidget(label_qualisysIP);

        lineEdit_qualisysIP = new QLineEdit(groupBox_Bmode2D);
        lineEdit_qualisysIP->setObjectName("lineEdit_qualisysIP");

        layout_Bmode2D3D_menu->addWidget(lineEdit_qualisysIP);

        label_qualisysPort = new QLabel(groupBox_Bmode2D);
        label_qualisysPort->setObjectName("label_qualisysPort");

        layout_Bmode2D3D_menu->addWidget(label_qualisysPort);

        lineEdit_qualisysPort = new QLineEdit(groupBox_Bmode2D);
        lineEdit_qualisysPort->setObjectName("lineEdit_qualisysPort");

        layout_Bmode2D3D_menu->addWidget(lineEdit_qualisysPort);

        pushButton_bmode2d3d = new QPushButton(groupBox_Bmode2D);
        pushButton_bmode2d3d->setObjectName("pushButton_bmode2d3d");
        QIcon icon5(QIcon::fromTheme(QString::fromUtf8("network-wired")));
        pushButton_bmode2d3d->setIcon(icon5);

        layout_Bmode2D3D_menu->addWidget(pushButton_bmode2d3d);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layout_Bmode2D3D_menu->addItem(horizontalSpacer_2);

        lineEdit_mhaPath = new QLineEdit(groupBox_Bmode2D);
        lineEdit_mhaPath->setObjectName("lineEdit_mhaPath");
        lineEdit_mhaPath->setEnabled(false);

        layout_Bmode2D3D_menu->addWidget(lineEdit_mhaPath);

        pushButton_mhaPath = new QPushButton(groupBox_Bmode2D);
        pushButton_mhaPath->setObjectName("pushButton_mhaPath");
        pushButton_mhaPath->setIcon(icon1);

        layout_Bmode2D3D_menu->addWidget(pushButton_mhaPath);

        pushButton_mhaRecord = new QPushButton(groupBox_Bmode2D);
        pushButton_mhaRecord->setObjectName("pushButton_mhaRecord");
        QIcon icon6(QIcon::fromTheme(QString::fromUtf8("media-record")));
        pushButton_mhaRecord->setIcon(icon6);

        layout_Bmode2D3D_menu->addWidget(pushButton_mhaRecord);

        checkBox_autoReconstruct = new QCheckBox(groupBox_Bmode2D);
        checkBox_autoReconstruct->setObjectName("checkBox_autoReconstruct");

        layout_Bmode2D3D_menu->addWidget(checkBox_autoReconstruct);

        layout_Bmode2D3D_menu->setStretch(7, 1);

        layout_Bmode2D->addLayout(layout_Bmode2D3D_menu);

        layout_Bmode2D3D_content = new QHBoxLayout();
        layout_Bmode2D3D_content->setObjectName("layout_Bmode2D3D_content");
        label_imageDisplay = new QLabel(groupBox_Bmode2D);
        label_imageDisplay->setObjectName("label_imageDisplay");
        label_imageDisplay->setAutoFillBackground(false);
        label_imageDisplay->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border: 1px solid black;\n"
"}\n"
""));
        label_imageDisplay->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        layout_Bmode2D3D_content->addWidget(label_imageDisplay);

        textEdit_qualisysLog = new QTextEdit(groupBox_Bmode2D);
        textEdit_qualisysLog->setObjectName("textEdit_qualisysLog");
        QFont font;
        font.setPointSize(6);
        textEdit_qualisysLog->setFont(font);
        textEdit_qualisysLog->setReadOnly(true);

        layout_Bmode2D3D_content->addWidget(textEdit_qualisysLog);

        layout_Bmode2D3D_content->setStretch(0, 3);
        layout_Bmode2D3D_content->setStretch(1, 7);

        layout_Bmode2D->addLayout(layout_Bmode2D3D_content);


        verticalLayout_3->addLayout(layout_Bmode2D);


        gridLayout->addWidget(groupBox_Bmode2D, 0, 0, 1, 1);

        groupBox_Amode = new QGroupBox(centralwidget);
        groupBox_Amode->setObjectName("groupBox_Amode");
        verticalLayout_6 = new QVBoxLayout(groupBox_Amode);
        verticalLayout_6->setObjectName("verticalLayout_6");
        layout_Amode = new QVBoxLayout();
        layout_Amode->setObjectName("layout_Amode");
        layout_Amode_menu = new QHBoxLayout();
        layout_Amode_menu->setObjectName("layout_Amode_menu");
        label = new QLabel(groupBox_Amode);
        label->setObjectName("label");

        layout_Amode_menu->addWidget(label);

        lineEdit_amodeIP = new QLineEdit(groupBox_Amode);
        lineEdit_amodeIP->setObjectName("lineEdit_amodeIP");

        layout_Amode_menu->addWidget(lineEdit_amodeIP);

        label_2 = new QLabel(groupBox_Amode);
        label_2->setObjectName("label_2");

        layout_Amode_menu->addWidget(label_2);

        lineEdit_amodePort = new QLineEdit(groupBox_Amode);
        lineEdit_amodePort->setObjectName("lineEdit_amodePort");

        layout_Amode_menu->addWidget(lineEdit_amodePort);

        pushButton_amodeConnect = new QPushButton(groupBox_Amode);
        pushButton_amodeConnect->setObjectName("pushButton_amodeConnect");
        pushButton_amodeConnect->setEnabled(true);
        pushButton_amodeConnect->setIcon(icon5);

        layout_Amode_menu->addWidget(pushButton_amodeConnect);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layout_Amode_menu->addItem(horizontalSpacer);

        lineEdit_amodeConfig = new QLineEdit(groupBox_Amode);
        lineEdit_amodeConfig->setObjectName("lineEdit_amodeConfig");
        lineEdit_amodeConfig->setEnabled(false);
        lineEdit_amodeConfig->setReadOnly(true);

        layout_Amode_menu->addWidget(lineEdit_amodeConfig);

        pushButton_amodeConfig = new QPushButton(groupBox_Amode);
        pushButton_amodeConfig->setObjectName("pushButton_amodeConfig");
        pushButton_amodeConfig->setIcon(icon);

        layout_Amode_menu->addWidget(pushButton_amodeConfig);

        comboBox_amodeNumber = new QComboBox(groupBox_Amode);
        comboBox_amodeNumber->addItem(QString());
        comboBox_amodeNumber->setObjectName("comboBox_amodeNumber");

        layout_Amode_menu->addWidget(comboBox_amodeNumber);

        layout_Amode_menu->setStretch(5, 3);
        layout_Amode_menu->setStretch(8, 1);

        layout_Amode->addLayout(layout_Amode_menu);

        gridLayout_amodeSignals = new QGridLayout();
        gridLayout_amodeSignals->setObjectName("gridLayout_amodeSignals");
        customPlot = new QCustomPlot(groupBox_Amode);
        customPlot->setObjectName("customPlot");

        gridLayout_amodeSignals->addWidget(customPlot, 0, 0, 1, 1);


        layout_Amode->addLayout(gridLayout_amodeSignals);

        layout_Amode->setStretch(1, 1);

        verticalLayout_6->addLayout(layout_Amode);


        gridLayout->addWidget(groupBox_Amode, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        comboBox_camera->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "A-mode Navigation", nullptr));
        groupBox_volume->setTitle(QCoreApplication::translate("MainWindow", "Volume", nullptr));
        lineEdit_volumeConfig->setPlaceholderText(QCoreApplication::translate("MainWindow", "config.xml", nullptr));
        label_volumeConfig->setText(QCoreApplication::translate("MainWindow", "Config", nullptr));
        lineEdit_volumeSource->setPlaceholderText(QCoreApplication::translate("MainWindow", "volume.mha", nullptr));
        pushButton_volumeBrowseRecording->setText(QString());
        pushButton_volumeReconstruct->setText(QCoreApplication::translate("MainWindow", "Reconstruct Volume", nullptr));
        pushButton_volumeLoad->setText(QCoreApplication::translate("MainWindow", "Load Volume", nullptr));
        lineEdit_volumeOutput->setText(QCoreApplication::translate("MainWindow", "D:/", nullptr));
        pushButton_volumeBrowseOutput->setText(QString());
        label_volumeExisting->setText(QCoreApplication::translate("MainWindow", "Existing Volume", nullptr));
        lineEdit_volumeRecording->setPlaceholderText(QCoreApplication::translate("MainWindow", "recording.mha", nullptr));
        label_volumeOutput->setText(QCoreApplication::translate("MainWindow", "Output", nullptr));
        pushButton_volumeBrowseConfig->setText(QString());
        label_volumeRecording->setText(QCoreApplication::translate("MainWindow", "Recording", nullptr));
        label_volumePixelValMin->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        label_volumePixelValMax->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
        label_volumeThreshold->setText(QCoreApplication::translate("MainWindow", "Threshold", nullptr));
        checkBox_volumeShow3DSignal->setText(QCoreApplication::translate("MainWindow", "Show 3D Signal", nullptr));
        comboBox_volume3DSignalMode->setItemText(0, QCoreApplication::translate("MainWindow", "Mode 1", nullptr));
        comboBox_volume3DSignalMode->setItemText(1, QCoreApplication::translate("MainWindow", "Mode 2", nullptr));
        comboBox_volume3DSignalMode->setItemText(2, QCoreApplication::translate("MainWindow", "Mode 4", nullptr));

        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        groupBox_Bmode2D->setTitle(QCoreApplication::translate("MainWindow", "B-mode", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        comboBox_camera->setItemText(0, QCoreApplication::translate("MainWindow", "Camera 1", nullptr));
        comboBox_camera->setItemText(1, QCoreApplication::translate("MainWindow", "Camera 2", nullptr));
        comboBox_camera->setItemText(2, QCoreApplication::translate("MainWindow", "Camera 3", nullptr));
        comboBox_camera->setItemText(3, QCoreApplication::translate("MainWindow", "Camera 4", nullptr));
        comboBox_camera->setItemText(4, QCoreApplication::translate("MainWindow", "Camera 5", nullptr));

        label_qualisysIP->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        lineEdit_qualisysIP->setPlaceholderText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_qualisysPort->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        lineEdit_qualisysPort->setPlaceholderText(QCoreApplication::translate("MainWindow", "22222", nullptr));
        pushButton_bmode2d3d->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        lineEdit_mhaPath->setText(QCoreApplication::translate("MainWindow", "D:/", nullptr));
        lineEdit_mhaPath->setPlaceholderText(QString());
        pushButton_mhaPath->setText(QCoreApplication::translate("MainWindow", "Select Path", nullptr));
        pushButton_mhaRecord->setText(QCoreApplication::translate("MainWindow", "Record", nullptr));
        checkBox_autoReconstruct->setText(QCoreApplication::translate("MainWindow", "Auto Reconstruct", nullptr));
        label_imageDisplay->setText(QString());
        groupBox_Amode->setTitle(QCoreApplication::translate("MainWindow", "A-mode", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        lineEdit_amodeIP->setPlaceholderText(QCoreApplication::translate("MainWindow", "192.168.1.2", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        lineEdit_amodePort->setPlaceholderText(QCoreApplication::translate("MainWindow", "6340", nullptr));
        pushButton_amodeConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        lineEdit_amodeConfig->setPlaceholderText(QCoreApplication::translate("MainWindow", "amodeconfig.csv", nullptr));
        pushButton_amodeConfig->setText(QCoreApplication::translate("MainWindow", "Load Config", nullptr));
        comboBox_amodeNumber->setItemText(0, QCoreApplication::translate("MainWindow", "Probe #", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

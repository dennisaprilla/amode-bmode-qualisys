/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/qbar3dseries.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtDataVisualization/qsurface3dseries.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "displayImage",
    "",
    "cv::Mat",
    "image",
    "displayUSsignal",
    "std::vector<uint16_t>",
    "usdata_uint16_",
    "disconnectUSsignal",
    "updateQualisysText",
    "QualisysTransformationManager",
    "tmanager",
    "volumeReconstructorCmdFinished",
    "volumeReconstructorCmdStandardOutput",
    "volumeReconstructorCmdStandardError",
    "on_pushButton_bmode2d3d_clicked",
    "on_pushButton_mhaRecord_clicked",
    "on_pushButton_amodeConnect_clicked",
    "on_pushButton_amodeConfig_clicked",
    "on_comboBox_amodeNumber_textActivated",
    "arg1",
    "on_pushButton_volumeLoad_clicked",
    "on_pushButton_volumeReconstruct_clicked",
    "on_pushButton_volumeBrowseConfig_clicked",
    "on_pushButton_volumeBrowseRecording_clicked",
    "on_checkBox_volumeShow3DSignal_stateChanged",
    "on_pushButton_mhaPath_clicked",
    "on_pushButton_volumeBrowseOutput_clicked",
    "on_checkBox_autoReconstruct_stateChanged",
    "on_comboBox_volume3DSignalMode_currentIndexChanged",
    "index"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  140,    2, 0x0a,    1 /* Public */,
       5,    1,  143,    2, 0x0a,    3 /* Public */,
       8,    0,  146,    2, 0x0a,    5 /* Public */,
       9,    1,  147,    2, 0x0a,    6 /* Public */,
      12,    0,  150,    2, 0x0a,    8 /* Public */,
      13,    0,  151,    2, 0x0a,    9 /* Public */,
      14,    0,  152,    2, 0x0a,   10 /* Public */,
      15,    0,  153,    2, 0x08,   11 /* Private */,
      16,    0,  154,    2, 0x08,   12 /* Private */,
      17,    0,  155,    2, 0x08,   13 /* Private */,
      18,    0,  156,    2, 0x08,   14 /* Private */,
      19,    1,  157,    2, 0x08,   15 /* Private */,
      21,    0,  160,    2, 0x08,   17 /* Private */,
      22,    0,  161,    2, 0x08,   18 /* Private */,
      23,    0,  162,    2, 0x08,   19 /* Private */,
      24,    0,  163,    2, 0x08,   20 /* Private */,
      25,    1,  164,    2, 0x08,   21 /* Private */,
      26,    0,  167,    2, 0x08,   23 /* Private */,
      27,    0,  168,    2, 0x08,   24 /* Private */,
      28,    1,  169,    2, 0x08,   25 /* Private */,
      29,    1,  172,    2, 0x08,   27 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   30,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'displayImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const cv::Mat &, std::false_type>,
        // method 'displayUSsignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<uint16_t> &, std::false_type>,
        // method 'disconnectUSsignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateQualisysText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QualisysTransformationManager &, std::false_type>,
        // method 'volumeReconstructorCmdFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'volumeReconstructorCmdStandardOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'volumeReconstructorCmdStandardError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_bmode2d3d_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_mhaRecord_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_amodeConnect_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_amodeConfig_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_comboBox_amodeNumber_textActivated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_pushButton_volumeLoad_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_volumeReconstruct_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_volumeBrowseConfig_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_volumeBrowseRecording_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_checkBox_volumeShow3DSignal_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_pushButton_mhaPath_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_volumeBrowseOutput_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_checkBox_autoReconstruct_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_comboBox_volume3DSignalMode_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->displayImage((*reinterpret_cast< std::add_pointer_t<cv::Mat>>(_a[1]))); break;
        case 1: _t->displayUSsignal((*reinterpret_cast< std::add_pointer_t<std::vector<uint16_t>>>(_a[1]))); break;
        case 2: _t->disconnectUSsignal(); break;
        case 3: _t->updateQualisysText((*reinterpret_cast< std::add_pointer_t<QualisysTransformationManager>>(_a[1]))); break;
        case 4: _t->volumeReconstructorCmdFinished(); break;
        case 5: _t->volumeReconstructorCmdStandardOutput(); break;
        case 6: _t->volumeReconstructorCmdStandardError(); break;
        case 7: _t->on_pushButton_bmode2d3d_clicked(); break;
        case 8: _t->on_pushButton_mhaRecord_clicked(); break;
        case 9: _t->on_pushButton_amodeConnect_clicked(); break;
        case 10: _t->on_pushButton_amodeConfig_clicked(); break;
        case 11: _t->on_comboBox_amodeNumber_textActivated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->on_pushButton_volumeLoad_clicked(); break;
        case 13: _t->on_pushButton_volumeReconstruct_clicked(); break;
        case 14: _t->on_pushButton_volumeBrowseConfig_clicked(); break;
        case 15: _t->on_pushButton_volumeBrowseRecording_clicked(); break;
        case 16: _t->on_checkBox_volumeShow3DSignal_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->on_pushButton_mhaPath_clicked(); break;
        case 18: _t->on_pushButton_volumeBrowseOutput_clicked(); break;
        case 19: _t->on_checkBox_autoReconstruct_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->on_comboBox_volume3DSignalMode_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 21;
    }
    return _id;
}
QT_WARNING_POP

QT += core gui 3dcore 3drender 3dinput 3dextras datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    amodeconfig.cpp \
    amodeconnection.cpp \
    amodedatamanipulator.cpp \
    bmode3dvisualizer.cpp \
    bmodeconnection.cpp \
    main.cpp \
    mainwindow.cpp \
    mhareader.cpp \
    mhawriter.cpp \
    qcustomplot.cpp \
    qualisysconnection.cpp \
    qualisystransformationmanager.cpp \
    volume3dcontroller.cpp \
    volumeamodecontroller.cpp

HEADERS += \
    amodeconfig.h \
    amodeconnection.h \
    amodedatamanipulator.h \
    bmode3dvisualizer.h \
    bmodeconnection.h \
    mainwindow.h \
    mhareader.h \
    mhawriter.h \
    qcustomplot.h \
    qualisysconnection.h \
    qualisystransformationmanager.h \
    ultrasoundconfig.h \
    volume3dcontroller.h \
    volumeamodecontroller.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    "C:/qualisys_cpp_sdk" \
    "C:/eigen-3.4.0"

SOURCES += \
    "C:/qualisys_cpp_sdk/Markup.cpp" \
    "C:/qualisys_cpp_sdk/Network.cpp" \
    "C:/qualisys_cpp_sdk/RTPacket.cpp" \
    "C:/qualisys_cpp_sdk/RTProtocol.cpp"

LIBS += -lws2_32 # Link against the Winsock library
LIBS += -liphlpapi # Link against the IP Helper API library

INCLUDEPATH += C:\opencv-4.9.0\opencv\build\include
LIBS += C:\opencv-4.9.0\opencv\build\install\x64\mingw\bin\libopencv_core490.dll
LIBS += C:\opencv-4.9.0\opencv\build\install\x64\mingw\bin\libopencv_highgui490.dll
LIBS += C:\opencv-4.9.0\opencv\build\install\x64\mingw\bin\libopencv_imgproc490.dll
LIBS += C:\opencv-4.9.0\opencv\build\install\x64\mingw\bin\libopencv_imgcodecs490.dll
LIBS += C:\opencv-4.9.0\opencv\build\install\x64\mingw\bin\libopencv_videoio490.dll

RESOURCES += \
    assets.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


QMAKE_CXXFLAGS += -Wa,-mbig-obj

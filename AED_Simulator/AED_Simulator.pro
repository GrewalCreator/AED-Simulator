QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aed.cpp \
    aedcontroller.cpp \
    main.cpp \
    aedwindow.cpp \
    mediaplayer.cpp \
    testcontroller.cpp \
    testwindow.cpp


HEADERS += \
    SignalType.h \
    aed.h \
    aedcontroller.h \
    aedwindow.h \
    defs.h \
    mediaplayer.h \
    testcontroller.h \
    testwindow.h \
    logs/YYY-MM-DD:AED_LOG.log

FORMS += \
    aedwindow.ui \
    testwindow.ui \




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

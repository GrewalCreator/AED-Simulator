QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    aed.cpp \
    aedcontroller.cpp \
    aedstate.cpp \
    battery.cpp \
    electrodepads.cpp \
    heartrategenerator.cpp \
    logger.cpp \
    main.cpp \
    aedwindow.cpp \
    mediaplayer.cpp \
    patient.cpp \
    processtracker.cpp \
    testcontroller.cpp \
    testwindow.cpp


HEADERS += \
    AudioTypes.h \
    PatientType.h \
    ProcessSteps.h \
    SignalType.h \
    aed.h \
    aedcontroller.h \
    aedstate.h \
    aedwindow.h \
    battery.h \
    defs.h \
    electrodepads.h \
    heartrategenerator.h \
    logger.h \
    mediaplayer.h \
    patient.h \
    processtracker.h \
    testcontroller.h \
    testwindow.h \

FORMS += \
    aedwindow.ui \
    testwindow.ui \




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    logs/YYYY:MM:DD-AED




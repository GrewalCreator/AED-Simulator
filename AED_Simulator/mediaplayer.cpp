#include "mediaplayer.h"

MediaPlayer::MediaPlayer(){

}


void MediaPlayer::play(const AudioTypes& audio){

    QString soundFilePath;
    QString fileName;

    switch(audio){
        case STAND_CLEAR:
            fileName = "stand_clear.wav";
            break;
        case POWER_ON_AUDIO:
            fileName = "Power_On.wav";
            break;
        case POWER_OFF_AUDIO:
            fileName = "Power_Off.wav";
            break;
        case BATTERY_AUDIO:
            fileName = "batterySound.wav";
            break;
        case CHARGING_AUDIO:
            fileName = "chargingSound.wav";
        break;
        case SHOCKING_AUDIO:
            fileName = "shockSound.wav";
            break;
        default:
            fileName = "error.wav";
            qInfo()  << "Audio File Not Found" << Qt::endl;
            break;
    }

    soundFilePath = QString(AUDIO_PATH) + fileName;


    qInfo() << soundFilePath << Qt::endl;

    if (!QFile::exists(soundFilePath)) {
        qInfo() << "Audio File Not found";
    } else {
        #ifdef Q_OS_WIN // Check for Windows platform
            QProcess::startDetached("cmd", QStringList() << "/c" << "start" << soundFilePath);
        #elif defined(Q_OS_LINUX) // Check for Linux platform
            QString command = "aplay";
            QStringList args;
            args << soundFilePath;

            QProcess* process = new QProcess();
            process->start(command, args);
            if (!process->waitForStarted() || !process->waitForFinished()) {
                qInfo() << "Failed to play audio. Please install 'alsa-utils' package.";
            }
            delete process;
        #elif defined(Q_OS_MAC) // Check for macOS platform
            QProcess::startDetached("afplay", QStringList() << soundFilePath);
        #else
            qInfo() << "OS Not Recognized. Cannot Play Audio" << Qt::endl;
        #endif
    }

}

MediaPlayer::~MediaPlayer(){

}

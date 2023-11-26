#include "mediaplayer.h"

MediaPlayer::MediaPlayer(){

}


void MediaPlayer::play(const AudioTypes& audio){

    QString soundFilePath;

    switch(audio){
        case STAND_CLEAR:
            soundFilePath = QString(AUDIO_PATH) + "stand_clear.wav";
            break;
        default:
            soundFilePath = QString(AUDIO_PATH) + "error.wav";
            qInfo()  << "Audio File Not Found" << Qt::endl;
    }


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

            QProcess process;
            process.start(command, args);
            if (!process.waitForStarted() || !process.waitForFinished()) {
                qInfo() << "Failed to play audio. Please install 'alsa-utils' package.";
            }
        #elif defined(Q_OS_MAC) // Check for macOS platform
            QProcess::startDetached("afplay", QStringList() << soundFilePath);
        #else
            qInfo() << "OS Not Recognized. Cannot Play Audio" << Qt::endl;
        #endif
    }
}

MediaPlayer::~MediaPlayer(){

}

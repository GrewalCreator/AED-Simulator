#include "mediaplayer.h"
MediaPlayer::MediaPlayer(){

}


void MediaPlayer::play(string audio){

    QString audioNotes = QString::fromStdString(audio);
    qInfo() << "Speaker: " << audioNotes << Qt::endl;
}

MediaPlayer::~MediaPlayer(){

}

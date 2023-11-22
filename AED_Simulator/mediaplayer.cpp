#include "mediaplayer.h"
MediaPlayer::MediaPlayer(){

}


void MediaPlayer::play(string audio){

    QString audioNotes = QString::fromStdString(audio);
    qInfo() << audioNotes << Qt::endl;
}

MediaPlayer::~MediaPlayer(){

}

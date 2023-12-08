#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "defs.h"
#include "QProcess"
#include "AudioTypes.h"
#include "QFile"

class MediaPlayer
{
public:
    MediaPlayer();
    void play(const AudioTypes& audio);
    virtual ~MediaPlayer();

private:

};

#endif // MEDIAPLAYER_H

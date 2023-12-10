#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "defs.h"
#include "QProcess"
#include "AudioTypes.h"
#include "QFile"

class MediaPlayer
{
public:
    explicit MediaPlayer();
    void play(const AudioTypes& audio) const;
    virtual ~MediaPlayer();

private:

};

#endif // MEDIAPLAYER_H

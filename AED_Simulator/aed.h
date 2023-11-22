#ifndef AED_H
#define AED_H

#include "mediaplayer.h"

class AEDController;

class AED
{
public:
    AED(AEDController& controller);
    void playAudio(string audio);

private:
    AEDController* controller;
    MediaPlayer* audioPlayer;
};

#endif // AED_H

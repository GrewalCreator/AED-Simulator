#ifndef AED_H
#define AED_H

#include "mediaplayer.h"
#include "SignalType.h"
#include "battery.h"


class AEDController;

class AED{
public:
    AED(AEDController& controller);
    void playAudio(string audio);
    bool checkShockSafety();
    bool shock(int amperage);

    virtual ~AED();

private:
    AEDController* controller;
    MediaPlayer* audioPlayer;
    Battery* battery;
};

#endif // AED_H

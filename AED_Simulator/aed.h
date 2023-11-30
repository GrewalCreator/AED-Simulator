#ifndef AED_H
#define AED_H

#include "mediaplayer.h"
#include "SignalType.h"
#include "battery.h"


class AEDController;

class AED{
public:
    AED(AEDController& controller);
    void playAudio(const AudioTypes& audio);
    bool checkShockSafety();
    bool shock(int amperage);
    bool powerOn();
    Battery* getBattery() const;

    virtual ~AED();

private:
    AEDController* controller;
    MediaPlayer* audioPlayer;
    Battery* battery;

    bool
    safetyChecks();
    };
#endif // AED_H

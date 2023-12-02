#ifndef AED_H
#define AED_H

#include "mediaplayer.h"
#include "SignalType.h"
#include "battery.h"
#include "PatientType.h"

class AEDController;

class AED{
public:
    AED(AEDController& controller);
    void playAudio(const AudioTypes& audio);
    bool checkShockSafety();
    bool shock(int amperage);
    bool powerOn();
    bool getShockDelivered();
    void resetShockDelivered();
    Battery* getBattery() const;

    virtual ~AED();

private:
    AEDController* controller;
    MediaPlayer* audioPlayer;
    Battery* battery;
    int numShocks;
    bool shockDelivered;
    bool safetyChecks();
    };
#endif // AED_H

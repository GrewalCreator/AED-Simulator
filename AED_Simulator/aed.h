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
    bool shock();
    bool powerOn();
    bool getShockDelivered();
    int getAmperage();
    void resetShockDelivered();
    Battery* getBattery() const;

    virtual ~AED();

private:
    AEDController* controller;
    MediaPlayer* audioPlayer;
    Battery* battery;
    int numShocks;
    int amperage;
    bool shockDelivered;
    bool safetyChecks();
    };
#endif // AED_H

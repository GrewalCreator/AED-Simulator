#ifndef AED_H
#define AED_H

#include "mediaplayer.h"
#include "SignalType.h"
#include "battery.h"
#include "PatientType.h"
#include "cmath"

class AEDController;

class AED{
public:
    AED(AEDController& controller);
    void playAudio(const AudioTypes& audio);
    bool checkShockSafety();
    bool shock();
    bool powerOn();
    bool getShockPressed();

    void setShockPressed();
    void resetShockPressed();
    Battery* getBattery() const;

    virtual ~AED();

private:
    AEDController* controller;
    MediaPlayer* audioPlayer;
    Battery* battery;
    int numShocks;
    bool shockPressed;
    bool safetyChecks();
    int getCurrentHR();
    int randomModifier(int diff);
    int random(int min, int max);
    };
#endif // AED_H

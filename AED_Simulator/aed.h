#ifndef AED_H
#define AED_H

#include "mediaplayer.h"
#include "SignalType.h"
#include "battery.h"
#include "PatientType.h"
#include "cmath"
#include "QRandomGenerator"

class AEDController;

class AED{
public:
    explicit AED(AEDController& controller);

    void playAudio(const AudioTypes& audio);
    bool checkShockSafety() const;
    bool shock() const;
    bool powerOn();
    bool getShockPressed() const;
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
    bool safetyChecks() const;
    int getCurrentHR() const;
    int randomModifier(int diff) const;
    int random(int min, int max) const;
    };
#endif // AED_H

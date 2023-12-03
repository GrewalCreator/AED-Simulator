#include "aed.h"
#include "aedcontroller.h"
#include "mediaplayer.h"

#define AMPERAGE 20

AED::AED(AEDController& controller): controller(&controller){
    audioPlayer = new MediaPlayer();
    battery = new Battery();
    numShocks = 0;
    amperage = AMPERAGE;
    shockDelivered = false;
}

void AED::playAudio(const AudioTypes& audio){
    audioPlayer->play(audio);
}

bool AED::powerOn(){
    // Run General Safety Checks
    if(!safetyChecks()){return false;}

    controller->getLogger()->log("AED Powering On");
    audioPlayer->play(INTRO_AUDIO);
    return true;


}


bool AED::safetyChecks(){
    // Implement Safety Checks
    return true;
}

bool AED::checkShockSafety(){
    return controller->getCurrentStep() == SHOCK ? true : false;
}

Battery* AED::getBattery() const{return this->battery;}

bool AED::getShockDelivered(){
    return shockDelivered;
}

int AED::getAmperage(){
    return amperage;
}

void AED::resetShockDelivered(){
    shockDelivered = false;
}

bool AED::shock(){

    if(!checkShockSafety()){
        return false;
    }

    if(battery->getBatteryLevels() < 30){
        controller->print("BATTERY LEVELS TOO LOW, PLEASE REPLACE");
        return false;
    }

    controller->getLogger()->log("Shocking!");

    battery->depleteBatteryLevel();

    shockDelivered = true;
    return true;
}


AED::~AED(){
    delete battery;
    delete audioPlayer;
}

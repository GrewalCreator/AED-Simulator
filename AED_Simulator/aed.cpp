#include "aed.h"
#include "aedcontroller.h"
#include "mediaplayer.h"
AED::AED(AEDController& controller): controller(&controller){
    audioPlayer = new MediaPlayer();
    battery = new Battery();
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


bool AED::shock(int amperage){

    //Check Safety
    if(!checkShockSafety()){return false;}

    if(battery->getBatteryLevels() < 30){return false;}

    controller->getLogger()->log("Shocking!");


    //Send Shock with specified ampage

    //Deplete Battery
    battery->depleteBatteryLevel();
    return true;
}


AED::~AED(){
    delete battery;
    delete audioPlayer;
}

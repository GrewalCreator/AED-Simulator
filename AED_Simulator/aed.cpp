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

bool AED::checkShockSafety(){
    return true;
}

bool AED::shock(int amperage){
    //Check Safety
    if(!checkShockSafety()){return false;}

    if(battery->getBatteryLevels() < 5){return false;}


    //Send Shock with specified ampage

    //Deplete Battery
    battery->depleteBatteryLevel();
    return true;
}




/*
 controller.sendStaticSignal(SIGNAL_TYPE);
 controller.sendDynamicSignal(SIGNAL_TYPE, string data);
*/






AED::~AED(){
    delete battery;
    delete audioPlayer;
    //delete controller;
}

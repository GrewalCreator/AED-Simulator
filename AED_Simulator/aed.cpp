#include "aed.h"
#include "aedcontroller.h"
#include "mediaplayer.h"
AED::AED(AEDController& controller): controller(&controller){
    audioPlayer = new MediaPlayer();
}

void AED::playAudio(string audio){
    audioPlayer->play(audio);
}

bool AED::shock(const int ampage){
    //Check Safety
    if(!checkShockSafety()){return false;}
    if(battery->getBatteryLevels() < 5){return false;}


    //Send Shock with specified ampage

    //Deplete Battery
    battery->depleteBatteryLevel();
    return true;


}

bool checkShockSafety(){
    // return true if safe
    //return false if not safe
}

/*
 controller.sendStaticSignal(SIGNAL_TYPE);
 controller.sendDynamicSignal(SIGNAL_TYPE, string data);
*/

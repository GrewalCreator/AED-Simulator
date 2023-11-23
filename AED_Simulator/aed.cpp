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

    if(battery->getBatteryLevels() >= 5){
        //Send Shock with specified ampage

        //Deplete Battery
        battery->depleteBatteryLevel();
    }else{
        // Not enough battery
    }


}

/*
 controller.sendStaticSignal(SIGNAL_TYPE);
 controller.sendDynamicSignal(SIGNAL_TYPE, string data);
*/

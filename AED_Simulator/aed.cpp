#include "aed.h"
#include "aedcontroller.h"
#include "mediaplayer.h"
AED::AED(AEDController& controller): controller(&controller){
    audioPlayer = new MediaPlayer();
}

void AED::playAudio(string audio){
    audioPlayer->play(audio);
}


/*
 controller.sendStaticSignal(SIGNAL_TYPE);
 controller.sendDynamicSignal(SIGNAL_TYPE, string data);
*/

#include "aed.h"
#include "aedcontroller.h"
#include "mediaplayer.h"
AED::AED(AEDController& controller): controller(&controller){

}

/*
 controller.sendStaticSignal(SIGNAL_TYPE);
 controller.sendDynamicSignal(SIGNAL_TYPE, string data);
*/

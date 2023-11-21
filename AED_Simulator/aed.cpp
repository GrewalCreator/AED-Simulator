#include "aed.h"
#include "controller.h"
#include "mediaplayer.h"
AED::AED(Controller& controller): controller(&controller){

}

/*
 controller.sendStaticSignal(SIGNAL_TYPE);
 controller.sendDynamicSignal(SIGNAL_TYPE, string data);
*/

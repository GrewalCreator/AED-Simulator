#include "controller.h"
#include "testcontroller.h"
#include "aed.h"

Controller::Controller(QObject* parent): QObject(parent){

    automatedED = new AED(*this);
}

/*
void sendStaticSignal(SignalType signalType){

    switch(signalType){
        case SET_STATUS_SUCCESS:
            emit statusLightSuccess();
            break;
        case SET_STATUS_FAIL:
            emit statusLightFail();
            break;
    }
}
*/

/*
void sendDynamicSignal(SignalType signalType, string data){

    switch(signalType){
        case PRINT:
            emit qprint(data);
            break;
    }
}
*/





Controller::~Controller(){
    delete automatedED;
}

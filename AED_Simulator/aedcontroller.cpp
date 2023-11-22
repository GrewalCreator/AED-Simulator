#include "aedcontroller.h"
#include "testcontroller.h"
#include "aed.h"

AEDController::AEDController(QObject* parent): QObject(parent){

    automatedED = new AED(*this);

}

void AEDController::setController(TestController* controller){
    this->testControlSystem = controller;
    //this->testControlSystem->setController(this);
}

AED* AEDController::getAED(){
    return automatedED;
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





AEDController::~AEDController(){
    delete automatedED;
}

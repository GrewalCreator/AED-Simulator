#include "aedcontroller.h"
#include "testcontroller.h"
#include "aed.h"

AEDController::AEDController(QObject* parent): QObject(parent){

    automatedED = new AED(*this);
    logger = new Logger();

}

void AEDController::setController(TestController* controller){
    this->testControlSystem = controller;
}

Logger* AEDController::getLogger(){
    return logger;
}

AED* AEDController::getAED(){
    return automatedED;
}


void AEDController::sendStaticSignal(SignalType& signalType){

    emit staticSignal(signalType);
}


void AEDController::sendDynamicSignal(SignalType& signalType, string& data){

    emit dynamicSignal(signalType, data);
}


AEDController::~AEDController(){
    delete automatedED;
}

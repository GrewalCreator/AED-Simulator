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


void AEDController::sendStaticSignal(const SignalType& signalType){

    emit staticSignal(signalType);
}


void AEDController::sendDynamicSignal(const SignalType& signalType, const string& data){

    emit dynamicSignal(signalType, data);
}


AEDController::~AEDController(){
    delete automatedED;
}

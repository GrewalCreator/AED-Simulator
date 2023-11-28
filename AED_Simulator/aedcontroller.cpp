#include "aedcontroller.h"
#include "testcontroller.h"
#include "aed.h"
#include "QThread"
AEDController::AEDController(QObject* parent){
    transmit = new AEDTransmitter(parent);
    automatedED = new AED(*this);
    logger = new Logger();

}

AEDTransmitter::AEDTransmitter(QObject* parent):QObject(parent){

};

void AEDTransmitter::sendDynamic(const SignalType& sig, const string& data){
    emit dynamicSignal(sig,data);
}

void AEDTransmitter::sendStatic(const SignalType& sig){
    emit staticSignal(sig);
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
    transmit->sendStatic(signalType);
}


void AEDController::sendDynamicSignal(const SignalType& signalType, const string& data){
    transmit->sendDynamic(signalType, data);
}

void AEDController::run(){

    while(true){
        QThread::msleep(1000);
        qDebug()<<"Looping.";

    }
}

void AEDController::cleanup(){
    qDebug()<<"doing cleanup...";
}
AEDController::~AEDController(){
    delete automatedED;
    delete transmit;

}

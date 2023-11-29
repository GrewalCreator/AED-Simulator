#include "aedcontroller.h"
#include "testcontroller.h"
#include "aed.h"
#include "QThread"
AEDController::AEDController(QSemaphore *sem , QObject* parent){
    transmit = new AEDTransmitter(parent);
    automatedED = new AED(*this);
    logger = new Logger();
    processTracker = new ProcessTracker();
    heartRateGenerator = new HeartRateGenerator();
    breakflag=false;
    semaphore = sem;
}

AEDTransmitter::AEDTransmitter(QObject* parent):QObject(parent){

};

void AEDTransmitter::sendDynamic(const SignalType& sig, const string& data){
    emit dynamicSignal(sig,data);
}

void AEDTransmitter::sendStatic(const SignalType& sig){
    emit staticSignal(sig);
}

void AEDController::setProcessTracker(const ProcessSteps& step){
    this->processTracker->setCurrentStep(step);
}

const ProcessSteps& AEDController::getProcessTracker(){
    return this->processTracker->getCurrentStep();
}

HeartRateGenerator* AEDController::getHeartRateGenerator(){
    return heartRateGenerator;
}

void AEDController::setController(TestController* controller){
    this->testControlSystem = controller;
}

bool AEDController::powerAEDOn(){
    return automatedED->powerOn();
}

bool AEDController::powerAEDOff(){
    qDebug()<<"in aedcontroller poweroff, calling cleanup now";
    this->cleanup();
    return true;//just true for now
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

    while(!breakflag){
        QThread::msleep(1000);
        qDebug()<<"Looping as thread id:"<<QThread::currentThreadId();

    }
    semaphore->release();
    qDebug()<<"sem released as thread id:"<<QThread::currentThreadId();
}

void AEDController::cleanup(){
    qDebug()<<"doing cleanup as thread id:"<<QThread::currentThreadId();
    breakflag = true;
}

AEDController::~AEDController(){
    qDebug()<<"Within AEDController deconstructor as thread id:"<<QThread::currentThreadId();
    //delete automatedED;
    //delete transmit;

}

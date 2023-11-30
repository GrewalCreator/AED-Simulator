#include "aedcontroller.h"
#include "testcontroller.h"
#include "aed.h"
#include "QThread"
#include "QCoreApplication"
#include <cstdlib>
#include <ctime>

AEDController::AEDController(QSemaphore *sem , QObject* parent){
    transmit = new AEDTransmitter(parent);
    automatedED = new AED(*this);
    logger = new Logger();
    processTracker = new ProcessTracker();
    heartRateGenerator = new HeartRateGenerator();
    breakflag=false;
    semaphore = sem;
    logger->log("Calling AEDController Constructor");
}

AEDTransmitter::AEDTransmitter(QObject* parent):QObject(parent){

}

void AEDTransmitter::sendDynamic(const SignalType& sig, const string& data){
    emit dynamicSignal(sig,data);
}

void AEDTransmitter::sendStatic(const SignalType& sig, bool state){
    emit staticSignal(sig, state);
}


void AEDController::setProcessTracker(const ProcessSteps& step){
    this->processTracker->setCurrentStep(step);
}

const ProcessSteps& AEDController::getProcessTracker() const{
    return this->processTracker->getCurrentStep();
}

HeartRateGenerator* AEDController::getHeartRateGenerator() const{
    return heartRateGenerator;
}

void AEDController::setController(TestController* controller){
    this->testControlSystem = controller;
}

bool AEDController::powerAEDOn(){
    return automatedED->powerOn();
}

bool AEDController::powerAEDOff(){

    logger->log("Calling AEDController PowerOff");
    this->cleanup();
    return true;//just true for now
}

Logger* AEDController::getLogger() const{
    return logger;
}

AED* AEDController::getAED() const{
    return automatedED;
}


void AEDController::sendStaticSignal(const SignalType& signalType, bool state){
    transmit->sendStatic(signalType,state);
}


void AEDController::sendDynamicSignal(const SignalType& signalType, const string& data){
    transmit->sendDynamic(signalType, data);
}

void AEDController::run(){
    breakflag = false; //allows for controller to start looping after being killed

    while(!breakflag){
        QThread::msleep(100);
        QString currentThreadId = "AEDController Looping As " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
        logger->log(currentThreadId);
        QCoreApplication::processEvents(); //allows for signals to propogate before looping another time
    }
    semaphore->release(); 
    QString currentThreadId = "Semaphore Released As Thread: " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    logger->log(currentThreadId);
    this->moveToThread(QCoreApplication::instance()->thread());
}


void AEDController::cleanup(){
    QString currentThreadId = "Cleanup Within AEDController As Thread: " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    logger->log(currentThreadId);
    breakflag = true;
}

void AEDController::placePads(const PatientType& type){

    //TODO: uncomment when previous step (preliminary checks) are implemented
    //if (processTracker->getCurrentStep() != ProcessSteps::ELECTRODE_PAD_PLACEMENT){
       // return;
    //}

    int placementIndicator;

    switch(type){

        case(ADULT):
            logger->log("Placing Adult Pads");

            break;
        case(CHILD):
            logger->log("Placing Pediatric Pads");

            break;
    }

    srand(time(0));
    placementIndicator = (rand() % 5);

    if (placementIndicator){ // 1 to 4 indicates successful pad placement
        sendDynamicSignal(PRINT,"PADS SUCCESSFULLY ATTACHED");
        sendStaticSignal(LIGHTUP_PADS, false);
        //TODO: call function for analysis

    }else{
        sendDynamicSignal(PRINT,"CHECK ELECTRODE PADS");
        return;
    }

}

AEDController::~AEDController(){
    QString currentThreadId = "AEDController Destructor Called As Thread: " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    logger->log(currentThreadId);
    delete automatedED;
    delete transmit;

}

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
    breakflag = false; //allows for controller to start looping after being killed
    int i = 0;
    while(!breakflag){
        //qDebug()<<"loop"<<i;
        QThread::msleep(100);
        //qDebug()<<"i value:"<<i%5;

        switch(i%6){
        case 0:
            transmit->sendStatic(LIGHTUP_OK);
            qDebug()<<"sending ok";
            break;

        case 1:
            transmit->sendStatic(LIGHTUP_911);
            qDebug()<<"sending 911";
            break;

        case 2:
            transmit->sendStatic(LIGHTUP_PADS);
            qDebug()<<"sending pads";
            break;

        case 3:
            transmit->sendStatic(LIGHTUP_STANDCLEAR);
            qDebug()<<"sending standclear";
            break;

        case 4:
            transmit->sendStatic(LIGHTUP_SHOCK);
            qDebug()<<"sending shock";
            break;

        case 5:
            transmit->sendStatic(LIGHTUP_COMPRESSIONS);
            qDebug()<<"sending compressions";
            break;

        default:
            break;
        }
        QCoreApplication::processEvents(); //allows for signals to propogate before looping another time
        i++;
    }
    semaphore->release();
    //qDebug()<<"sem released as thread id:"<<QThread::currentThreadId();
    this->moveToThread(QCoreApplication::instance()->thread());
}


void AEDController::cleanup(){
    //qDebug()<<"doing cleanup as thread id:"<<QThread::currentThreadId();
    breakflag = true;
}

void AEDController::placePads(PatientType type){

    //TODO: uncomment when previous step (preliminary checks) are implemented
    //if (processTracker->getCurrentStep() != ProcessSteps::ELECTRODE_PAD_PLACEMENT){
       // return;
    //}

    int placementIndicator;

    switch(type){

    case(PatientType::ADULT):
        qDebug() << "ADULT PADS";
        break;
    case(PatientType::CHILD):
        qDebug() << "PEDIATRIC PADS";
        break;
    }

    std::srand(std::time(0));
    placementIndicator = (std::rand() % 5);

    if (placementIndicator){ // 1 to 4 indicates successful pad placement
        qDebug() << "PADS SUCCESSFULLY ATTACHED";
        //TODO: call AEDWindow's setOneLight(LIGHTUP_PADS, false)SS

        //TODO: call function for analysis

    }else{
        qDebug() << "CHECK ELECTRODE PADS";
        return;
    }

}

AEDController::~AEDController(){
    //qDebug()<<"Within AEDController deconstructor as thread id:"<<QThread::currentThreadId();
    delete automatedED;
    delete transmit;

}

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
    pads = new ElectrodePads();
    patientAdult = new Patient(ADULT);
    patientChild = new Patient(CHILD);

    activePatient = patientAdult;

    breakflag=false;
    semaphore = sem;
    logger->log("Calling AEDController Constructor");
    timeElapsed = 0;
}

AEDTransmitter::AEDTransmitter(QObject* parent):QObject(parent){

}

void AEDTransmitter::sendDynamic(const SignalType& sig, const string& data){
    emit dynamicSignal(sig,data);
}

void AEDTransmitter::sendStatic(const SignalType& sig, bool state){
    emit staticSignal(sig, state);
}



void AEDController::setCurrentStep(const ProcessSteps& step){

    this->processTracker->setCurrentStep(step);
}

AEDTransmitter* AEDController::getTransmitter(){
    return transmit;
}

const ProcessSteps& AEDController::getCurrentStep() const{
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

Patient* AEDController::getPatient() const{
    return activePatient;
}


void AEDController::sendStaticSignal(const SignalType& signalType, bool state){
    transmit->sendStatic(signalType,state);
}


void AEDController::sendDynamicSignal(const SignalType& signalType, const string& data){
    transmit->sendDynamic(signalType, data);
}

void AEDController::stepProgress(){
    switch(processTracker->getCurrentStep()){
    case CHECK_OK:{
        sendStaticSignal(LIGHTUP_OK,true);
        //TODO: call checkOk function
        if(timeElapsed > 10){
            setCurrentStep(GET_HELP);
            timeElapsed=0;
        }
        break;
    }
    case GET_HELP:{
        sendStaticSignal(LIGHTUP_911, true);
        //TODO: call getHelp function
        if(timeElapsed > 10){
            setCurrentStep(ELECTRODE_PAD_PLACEMENT);
            timeElapsed=0;
        }
        break;
    }
    case ELECTRODE_PAD_PLACEMENT:{
        sendStaticSignal(LIGHTUP_PADS, true);
        qDebug() << "getHasPadsOn(): " << activePatient->getHasPadsOn();
        if(activePatient->getHasPadsOn()){
            setCurrentStep(ANALYZE_ECG);
            timeElapsed=0;
        }
        break;
    }
    case ANALYZE_ECG:{
        setCurrentStep(SHOCK);
        qDebug() << "in ANALYZE_ECG";
        break;
    }
    case SHOCK:{
        setCurrentStep(CPR);
        qDebug() << "in SHOCKS";
        break;
    }

    case CPR:{
        sendStaticSignal(LIGHTUP_COMPRESSIONS, true);
        break;
    }
            default:
        break;
    }
}

void AEDController::run(){
    breakflag = false; //allows for controller to start looping after being killed
    QThread::msleep(5000);
    while(!breakflag){
        QThread::msleep(200);
        QString currentThreadId = "AEDController Looping As " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
        logger->log(currentThreadId);

        stepProgress();
        sendDynamicSignal(BATTERY,std::to_string(automatedED->getBattery()->getBatteryLevels()));//update battery levels
        sendDynamicSignal(HEART_RATE,std::to_string(activePatient->getHeartRate()));//update heart rate
        QCoreApplication::processEvents(); //allows for signals to propogate before looping another time
        timeElapsed++;
    }
    QString currentThreadId = "Semaphore Released As Thread: " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    logger->log(currentThreadId);
    this->moveToThread(QCoreApplication::instance()->thread());
}


void AEDController::cleanup(){
    QString currentThreadId = "Cleanup Within AEDController As Thread: " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    logger->log(currentThreadId);
    breakflag = true;
}


bool AEDController::placePads(const PatientType& type){
    logger->log("Attempting To Place Pads");
    qDebug() << "in placePads";
    srand(time(0));
    bool correctlyPlaced = (rand() % 5) != 0;
    if(correctlyPlaced){
        switch(type){

            case(ADULT):
                logger->log("Placing Adult Pads");
                pads->setPadType(ADULT);
                break;
            case(CHILD):
                logger->log("Placing Pediatric Pads");
                pads->setPadType(ADULT);
                break;

        }

        pads->setPadPlacement(true);
        activePatient->setHasPadsOn(true);


        sendDynamicSignal(PRINT,"PADS SUCCESSFULLY ATTACHED");

        return true;
    }else{

        sendDynamicSignal(PRINT,"CHECK ELECTRODE PADS");
        logger->log("Pad Placement Failed: Applied Incorrectly");
        pads->setPadPlacement(false);

        return false;

    }


}

void AEDController::recharge(){
    automatedED->getBattery()->chargeBattery();
}

void AEDController::shockPressed(){
    automatedED->shock(1);
}

AEDController::~AEDController(){
    QString currentThreadId = "AEDController Destructor Called As Thread: " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    logger->log(currentThreadId);
    delete automatedED;
    delete transmit;
    delete pads;
    delete logger;
    delete processTracker;
    delete heartRateGenerator;
}

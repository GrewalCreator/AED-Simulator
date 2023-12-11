#include "aedcontroller.h"
#include "testcontroller.h"
#include "aed.h"
#include "QThread"
#include "QCoreApplication"
#include <cstdlib>
#include <ctime>
#include "aedstate.h"


// Transmitter to centralize the signals sent from the backend
AEDTransmitter::AEDTransmitter(QObject* parent):QObject(parent){

}

void AEDTransmitter::sendDynamic(const SignalType& sig, const string& data){
    emit dynamicSignal(sig,data);
}

void AEDTransmitter::sendStatic(const SignalType& sig, bool state){
    emit staticSignal(sig, state);
}

AEDTransmitter* AEDController::getTransmitter() const{
    return transmit;
}




AEDController::AEDController(QSemaphore *sem , QObject* parent){
    transmit = new AEDTransmitter(parent);
    automatedED = new AED(*this);
    logger = new Logger();
    processTracker = new ProcessTracker();
    heartRateGenerator = new HeartRateGenerator();
    pads = new ElectrodePads();
    patientAdult = new Patient(ADULT);
    patientChild = new Patient(CHILD);

    initStates();
    semaphore = sem;
    activePatient = patientAdult;

    timeElapsed = 0;
    breakflag=false;
    errorFlag = false;
    deathFlag = false;

    currentState = states[POWER_ON];

    logger->log("Calling AEDController Constructor");

}

void AEDController::initStates(){
    states.insert(POWER_ON, new PowerOnState(this));
    states.insert(CHECK_OK, new CheckPatientState(this));
    states.insert(GET_HELP, new GetHelpState(this));
    states.insert(ELECTRODE_PAD_PLACEMENT, new PadPlacementState(this));
    states.insert(ANALYZE_ECG, new AnalysisState(this));
    states.insert(SHOCK, new ShockState(this));
    states.insert(CPR, new CompressionsState(this));
    log("Initiallzing State Machine");
}


void AEDController::toggleActivePatient(){
    log("Switching Patients");
    if (activePatient == patientAdult){
        activePatient = patientChild;
    }else{
        activePatient = patientAdult;
    }
    updateHR(activePatient->getHeartRate());
}

void AEDController::setCurrentStep(const ProcessSteps& step){

    this->processTracker->setCurrentStep(step);
}



const ProcessSteps& AEDController::getCurrentStep() const{
    return this->processTracker->getCurrentStep();
}
TestController* AEDController::getTestController() const{
    return testControlSystem;
}

HeartRateGenerator* AEDController::getHeartRateGenerator() const{
    return heartRateGenerator;
}

void AEDController::setController(TestController* controller){
    this->testControlSystem = controller;
}

bool AEDController::powerAEDOn() const{
    return automatedED->powerOn();
}

bool AEDController::powerAEDOff(){

    logger->log("Calling AEDController PowerOff");
    this->cleanup();
    return true;
}

void AEDController::log(const QString& message) const{
    logger->log(message);
}

AED* AEDController::getAED() const{
    return automatedED;
}

Patient* AEDController::getPatient() const{
    return activePatient;
}

void AEDController::updateHR(int heartRate){
    activePatient->setHeartRate(heartRate);
    sendStaticSignal(SLIDER);
    sendStaticSignal(HEART_RATE);
    if(activePatient->isDead() && activePatient->getHasPadsOn() && !activePatient->getImproperPlacement()){
        setState(CPR);
    }
}

void AEDController::sendStaticSignal(const SignalType& signalType, bool state) const{
    transmit->sendStatic(signalType,state);
}


void AEDController::sendDynamicSignal(const SignalType& signalType, const string& data) const{
    transmit->sendDynamic(signalType, data);
}

void AEDController::run(){
    breakflag = false; //allows for controller to start looping after being killed

    while(!breakflag){
        QThread::msleep(200);
        QString currentThreadId = "AEDController Looping As " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
        //logger->log(currentThreadId);

        systemsCheck();
        if(errorFlag) setState(POWER_ON);

        currentState->stepProgress();
        sendStaticSignal(BATTERY);//update battery levels
        sendStaticSignal(HEART_RATE);
        QCoreApplication::processEvents(); //allows for signals to propogate before looping another time

        // Slowly Kill Patient

        slowDeath();


        ++timeElapsed;
    }
    QString currentThreadId = "Semaphore Released As Thread: " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    logger->log(currentThreadId);

    this->moveToThread(QCoreApplication::instance()->thread());
    sendStaticSignal(RESET,false);

    log("Run() Loop Ended");
}

void AEDController::slowDeath(){
    if(deathFlag){
        updateHR(activePatient->getHeartRate() - 5);
        if(activePatient->isDead()){
            deathFlag = false;
        }
    }

    if(timeElapsed % 5 == 0){

        if(activePatient->getHeartRate() == 250){
            print("Patients Heart Was Too Rapid & Blew Up");
            deathFlag = true;
        }
        else if(activePatient->getHeartRate() < 60){
            updateHR(activePatient->getHeartRate() - 2);
        }else if(activePatient->getHeartRate() > 150){
            updateHR(activePatient->getHeartRate() + 2);
        }else if(activePatient->getHeartRate() < 105){
            updateHR(activePatient->getHeartRate() + 1);
        }else if(activePatient->getHeartRate() > 105){
            updateHR(activePatient->getHeartRate() - 1);
        }
    }
}


void AEDController::cleanup(){
    QString currentThreadId = "Cleanup Within AEDController As Thread: " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    logger->log(currentThreadId);
    breakflag = true;
}

void AEDController::setState(const ProcessSteps& s){
    currentState = states[s];
    setCurrentStep(s);
}


bool AEDController::placePads(const PatientType& type){
    logger->log("Attempting To Place Pads");
    srand(time(0));
    bool correctlyPlaced = (rand() % 2) != 0;
    if(correctlyPlaced){
        switch(type){

            case(ADULT):
                logger->log("Placing Adult Pads");

                pads->setPadType(ADULT);
                break;
            case(CHILD):
                logger->log("Placing Pediatric Pads");

                pads->setPadType(CHILD);
                break;
        }

        pads->setPadPlacement(true);
        activePatient->setHasPadsOn(true);
        activePatient->setImproperPlacement(false);

        return true;
    }else{

        logger->log("Pad Placement Failed: Applied Incorrectly");
        pads->setPadPlacement(false);
        activePatient->setHasPadsOn(true);
        activePatient->setImproperPlacement(true);

        return false;

    }

}

//return true if there is an error IF: BATTERY<30 OR PAD DISCONNECTED FROM AED
void AEDController::systemsCheck(){
     errorFlag = (automatedED->getBattery()->getBatteryLevels() < 30) || !(pads->isConnectedToAED());
}

void AEDController::standClear(){
    sendStaticSignal(LIGHTUP_STANDCLEAR, true);
    print("STAND CLEAR");
}


void AEDController::checkOk() {
    print("Ask the patient, \"ARE YOU OK?\"");
}

void AEDController::getHelp() const{
    print("Call for help.");
}

int AEDController::getTimeElapsed() const{
    return timeElapsed;
}

void AEDController::resetTimeElapsed(){
    timeElapsed = 0;
}

void AEDController::print(const string& str) const{
    sendDynamicSignal(PRINT, str);
    log(QString::fromStdString(str));
}

void AEDController::illuminate(const SignalType& p){
    sendStaticSignal(p, true);
}

void AEDController::recharge(){
    automatedED->getBattery()->chargeBattery();
    log("Recharging Battery");
}

bool AEDController::shockPressed(){
    automatedED->setShockPressed();
    return true;
}

ElectrodePads* AEDController::getPads() const{
    return pads;
}

bool AEDController::getErrorFlag() const{
    return errorFlag;
}

bool AEDController::getDeathFlag() const{
    return deathFlag;
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
    delete patientAdult;
    delete patientChild;
}

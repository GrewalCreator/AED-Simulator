#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){
    sessionCompressions = 0;
    totalCompressions= 0;
}


void TestController::setController(AEDController* controller){
    this->controlSystem = controller;
}

void TestController::disableUI(){
    emit uiDisable();
}

void TestController::updateHeartRate(){
    int heartRateInt = controlSystem->getPatient()->getHeartRate();

    double heartRate(heartRateInt);
    HeartRateGenerator* heartRaterGenerator = controlSystem->getHeartRateGenerator();
    heartRaterGenerator->updateHeartRate(heartRate);

    vector<double> yValues = heartRaterGenerator->getYValues();

    emit updateHeartRateImage(yValues);
}

void TestController::toggleWetPatient(int index) const{
    if(index == 0){
        controlSystem->getPatient()->moveToInsulativeEnvironment();
    }else{
        controlSystem->getPatient()->moveToConductiveEnvironment();
    }


}

void TestController::resetSessionCompressions(){
    sessionCompressions = 0;
}

int TestController::getSessionCompressions() const{
    return sessionCompressions;
}

void TestController::incrementSessionCompressions(){
    ++sessionCompressions;
    ++totalCompressions;
}

void TestController::depleteBattery() const{
    if(controlSystem->getCurrentStep() > POWER_OFF){
        controlSystem->getAED()->getBattery()->depleteBatteryLevel();
    }
}

void TestController::updateCompressionHeartRate() const{
    int newHeartRate = getCurrentHeartRate();
    int randomValue = 0;

    randomValue = QRandomGenerator::global()->bounded(0, 11);

    if(getCurrentHeartRate() > MAX_NOMINAL_BPM){
        newHeartRate = getCurrentHeartRate() - randomValue;

     }else if(getCurrentHeartRate() < MIN_NOMINAL_BPM){
        newHeartRate = getCurrentHeartRate() + randomValue;

    }
    controlSystem->updateHR(newHeartRate);
}

AEDController* TestController::getControlSystem() const{
    return controlSystem;
}

void TestController::placePads(const PatientType& type) const{
    if(controlSystem->getCurrentStep() == ELECTRODE_PAD_PLACEMENT){
        controlSystem->placePads(type);
    }
}

int TestController::getCurrentHeartRate() const{
    return controlSystem->getPatient()->getHeartRate();
}



void TestController::updateSlider(){
    emit sliderUpdate();
}



void TestController::removePadsFromPatient() const{

    bool currentState = controlSystem->getPatient()->getHasPadsOn();
    if (currentState){
        controlSystem->getPatient()->setHasPadsOn(false);
    }

}

void TestController::togglePadConnection() const{
    bool previousConnectionValue = controlSystem->getPads()->isConnectedToAED();
    controlSystem->getPads()->setIsConnectedToAED(!previousConnectionValue);
}


TestController::~TestController(){

}

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

void TestController::toggleWetPatient(){
    bool isWet = controlSystem->getPatient()->getIsInWater();
    if(isWet){
        controlSystem->getPatient()->setIsInWater(false);
    }else{
        controlSystem->getPatient()->setIsInWater(true);
    }

}

void TestController::resetSessionCompressions(){
    sessionCompressions = 0;
}

int TestController::getSessionCompressions(){
    return sessionCompressions;
}

void TestController::incrementSessionCompressions(){
    ++sessionCompressions;
    ++totalCompressions;
}

void TestController::depleteBattery(){
    controlSystem->getAED()->getBattery()->depleteBatteryLevel();
}

void TestController::updateCompressionHeartRate(){
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

AEDController* TestController::getControlSystem(){
    return controlSystem;
}

void TestController::placePads(const PatientType& type){
    if(!(controlSystem->getCurrentStep() == ELECTRODE_PAD_PLACEMENT)){return;}
    controlSystem->placePads(type);
}

int TestController::getCurrentHeartRate(){
    return controlSystem->getPatient()->getHeartRate();
}



void TestController::updateSlider(){
    emit sliderUpdate();
}



void TestController::removePadsFromPatient(){

    bool currentState = controlSystem->getPatient()->getHasPadsOn();
    if (currentState){
        controlSystem->getPatient()->setHasPadsOn(false);
    }

}

void TestController::togglePadAED(){
    bool setTo = controlSystem->getPads()->isConnectedToAED()^true;
    controlSystem->getPads()->setIsConnectedToAED(setTo);

}


TestController::~TestController(){

}

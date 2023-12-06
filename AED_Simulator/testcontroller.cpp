#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){

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

void TestController::depleteBattery(){
    controlSystem->getAED()->getBattery()->depleteBatteryLevel();
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



void TestController::removePadsOffPatient(){

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

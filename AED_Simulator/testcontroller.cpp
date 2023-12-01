#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){

}


void TestController::setController(AEDController* controller){
    this->controlSystem = controller;
}

void TestController::updateHeartRate(int newHeartRate){
    double heartRate(newHeartRate);
    HeartRateGenerator* heartRaterGenerator = controlSystem->getHeartRateGenerator();
    heartRaterGenerator->updateHeartRate(heartRate);
    vector<double> xValues = heartRaterGenerator->getXValues();
    vector<double> yValues = heartRaterGenerator->getYValues();
    emit updateHeartRateImage(xValues, yValues);
}

void TestController::placePads(const PatientType& type){
    if(!(controlSystem->getCurrentStep() > POWER_OFF)){return;}
    bool placedSuccessfully = controlSystem->placePads(type);
    if(placedSuccessfully){
        controlSystem->setCurrentStep(ANALYZE_ECG);
    }
}

void TestController::setPatientHR(double heartRate){
    controlSystem->getPatient()->setHeartRate(heartRate);
}


TestController::~TestController(){

}

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

    vector<double> yValues = heartRaterGenerator->getYValues();

    emit updateHeartRateImage(yValues);
}

void TestController::placePads(const PatientType& type){
    if(!(controlSystem->getCurrentStep() == ELECTRODE_PAD_PLACEMENT)){return;}
    bool placedSuccessfully = controlSystem->placePads(type);
}

void TestController::setPatientHR(double heartRate){
    controlSystem->getPatient()->setHeartRate(heartRate);
}


TestController::~TestController(){

}

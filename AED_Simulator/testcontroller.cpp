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

int TestController::getCurrentHeartRate(){
    return controlSystem->getPatient()->getHeartRate();
}
void TestController::setPatientHR(double heartRate){
    controlSystem->getPatient()->setHeartRate(heartRate);
}

void TestController::updateSlider(){
    qDebug() << "TestController Update Slider";
    emit sliderUpdate();
}



void TestController::togglePadPatient(){
    bool setTo = controlSystem->getPatient()->getHasPadsOn()^true;
    controlSystem->getPatient()->setHasPadsOn(setTo);

}

void TestController::togglePadAED(){
    bool setTo = controlSystem->getPads()->isConnectedToAED()^true;
    controlSystem->getPads()->setIsConnectedToAED(setTo);

}


TestController::~TestController(){

}

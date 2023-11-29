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


TestController::~TestController(){

}

#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){
    this->controlSystem->setController(this);
}

void TestController::testAudio(){

}


void TestController::setController(AEDController* controller){
    this->controlSystem = controller;
}




TestController::~TestController(){

}

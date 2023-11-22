#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){
    //this->setController(windowController);
    //this->controlSystem->setController(this);
}

void TestController::testAudio(){

}


void TestController::setController(QObject* controller){
    this->controlSystem = controller;
}




TestController::~TestController(){

}

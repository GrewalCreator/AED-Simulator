#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){
    //this->setController(windowController);
    //this->controlSystem->setController(this);
}

void TestController::testAudio(){
    controlSystem->getAED()->playAudio("Testing Testing 1, 2,  3");
}


void TestController::setController(AEDController* controller){
    this->controlSystem = controller;
}




TestController::~TestController(){

}

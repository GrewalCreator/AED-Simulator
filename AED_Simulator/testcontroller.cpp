#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){

}

void TestController::testAudio(){
    controlSystem->getAED()->playAudio("Testing Testing 1, 2,  3");
}


void TestController::setController(AEDController* controller){
    this->controlSystem = controller;
}

// Remove Later
void TestController::logTest(){

}

// Remove Later
void TestController::illuminateTest(){
    //controlSystem->sendDynamicSignal(LIGHTUP_STEP, "integer");
}


TestController::~TestController(){

}

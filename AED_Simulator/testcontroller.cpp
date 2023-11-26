#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){

}

void TestController::testAudio(){
    controlSystem->getAED()->playAudio(STAND_CLEAR);
}


void TestController::setController(AEDController* controller){
    this->controlSystem = controller;
}

// Remove Later
void TestController::logTest(){
    controlSystem->getLogger()->log("Test");
}



// Remove Later
void TestController::illuminateTest(){
    //controlSystem->sendDynamicSignal(LIGHTUP_STEP, "integer");
}


TestController::~TestController(){

}

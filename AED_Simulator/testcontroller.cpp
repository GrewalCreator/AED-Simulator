#include "testcontroller.h"
#include "aedcontroller.h"

TestController::TestController(QObject* parent): QObject(parent){

}


void TestController::setController(AEDController* controller){
    this->controlSystem = controller;
}



TestController::~TestController(){

}

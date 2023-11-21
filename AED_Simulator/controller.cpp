#include "controller.h"
#include "aed.h"

Controller::Controller(QObject* parent): QObject(parent){
    automatedED = new AED(*this);
}










Controller::~Controller(){
    delete automatedED;
}

#include "electrodepads.h"

ElectrodePads::ElectrodePads(){

}


bool ElectrodePads::isOnPatient(){
    return onPatient;
}


bool ElectrodePads::isConnectedToAED(){
    return connectedToAED;
}

void ElectrodePads::setPadPlacement(bool onPatient){
    this->onPatient = onPatient;
}

void ElectrodePads::setIsConnectedToAED(bool connectedToAED){
    this->connectedToAED = connectedToAED;
}

const PatientType& ElectrodePads::getPadType(){
    return this->padType;
}


void ElectrodePads::setPadType(const PatientType& type){
    this->padType = type;
}

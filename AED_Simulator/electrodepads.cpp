#include "electrodepads.h"

ElectrodePads::ElectrodePads(){
    connectedToAED = true;
}


bool ElectrodePads::isOnPatient() const{
    return onPatient;
}


bool ElectrodePads::isConnectedToAED() const{
    return connectedToAED;
}

void ElectrodePads::setPadPlacement(bool onPatient){
    this->onPatient = onPatient;
}

void ElectrodePads::setIsConnectedToAED(bool connectedToAED){
    this->connectedToAED = connectedToAED;
}

const PatientType& ElectrodePads::getPadType() const{
    return this->padType;
}


void ElectrodePads::setPadType(const PatientType& type){
    this->padType = type;
}

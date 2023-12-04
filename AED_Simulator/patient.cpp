#include "patient.h"

Patient::Patient(const PatientType& type): patientType(type){
    hasPadsOn = false;
    isInWater = false;
    improperPlacement = true;
    heartRate = 105;
}

bool Patient::getIsInWater() const{
    return this->isInWater;
}


void Patient::setIsInWater(bool isInWater){
    this->isInWater = isInWater;
}

double Patient::getHeartRate() const{
    return this->heartRate;
}

void Patient::setHeartRate(double heartRate){
    this->heartRate = heartRate;
}

bool Patient::getHasPadsOn() const{
    return hasPadsOn;
}

void Patient::setHasPadsOn(bool hasPadsOn){
    this->hasPadsOn = hasPadsOn;
}

const PatientType& Patient::getPatientType() const{
    return patientType;
}


bool Patient::getImproperPlacement()const{
    return improperPlacement;
}

void Patient::setImproperPlacement(bool improper){
    improperPlacement = improper;
}

bool Patient::isDead(){return this->heartRate == 0;}

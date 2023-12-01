#include "patient.h"

Patient::Patient(const PatientType& type): patientType(type){

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

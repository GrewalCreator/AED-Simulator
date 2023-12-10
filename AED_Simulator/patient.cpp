#include "patient.h"

Patient::Patient(const PatientType& type): patientType(type){
    hasPadsOn = false;
    environmentIsConductive = false;
    improperPlacement = true;
    heartRate = 105;
}

bool Patient::isInConductiveEnvironment() const{
    return this->environmentIsConductive;
}


void Patient::moveToConductiveEnvironment(){
    this->environmentIsConductive = true;
}

void Patient::moveToInsulativeEnvironment(){
    this->environmentIsConductive = false;
}

double Patient::getHeartRate() const{
    return this->heartRate;
}

void Patient::setHeartRate(double heartRate){
    this->heartRate = heartRate;
    boundHeartRate();

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

bool Patient::isDead() const{
    return this->heartRate == 0;
}

void Patient::boundHeartRate(){
    if(heartRate < 0){
        heartRate = 0;
    }else if(heartRate > 250){
        heartRate = 250;
    }
}

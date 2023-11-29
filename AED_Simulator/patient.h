#ifndef PATIENT_H
#define PATIENT_H

#include "defs.h"
#include "PatientType.h"

class Patient {
public:
    // Constructor
    Patient(string& name, PatientType& type);

    // Getters and Setters for member variables
    bool getIsInWater() const;
    void setIsInWater(bool isInWater);

    double getHeartRate() const;
    void setHeartRate(double heartRate);

    bool getHasPadsOn() const;
    void setHasPadsOn(bool hasPadsOn);



private:
    bool isInWater;
    double heartRate;
    bool hasPadsOn;
    string name;
    PatientType patientType;
};

#endif // PATIENT_H

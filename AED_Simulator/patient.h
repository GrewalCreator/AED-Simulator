#ifndef PATIENT_H
#define PATIENT_H

#include "defs.h"
#include "PatientType.h"

class Patient {
public:
    // Constructor
    Patient(const PatientType& type);

    // Getters and Setters for member variables
    bool getIsInWater() const;
    void setIsInWater(bool isInWater);

    double getHeartRate() const;
    void setHeartRate(double heartRate);

    bool getHasPadsOn() const;
    void setHasPadsOn(bool hasPadsOn);

    bool getImproperPlacement()const;
    void setImproperPlacement(bool improper);

    const PatientType& getPatientType() const;



private:
    bool isInWater;
    double heartRate;
    bool hasPadsOn;
    bool improperPlacement;
    string name;
    PatientType patientType;
};

#endif // PATIENT_H

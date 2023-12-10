#ifndef PATIENT_H
#define PATIENT_H

#include "defs.h"
#include "PatientType.h"

class Patient {
public:
    // Constructor
    Patient(const PatientType& type);

    // Getters and Setters for member variables
    bool isInConductiveEnvironment() const;
    void moveToConductiveEnvironment();
    void moveToInsulativeEnvironment();

    double getHeartRate() const;
    void setHeartRate(double heartRate);

    bool getHasPadsOn() const;
    void setHasPadsOn(bool hasPadsOn);

    bool getImproperPlacement()const;
    void setImproperPlacement(bool improper);

    const PatientType& getPatientType() const;
    bool isDead() const;



private:
    bool environmentIsConductive;
    double heartRate;
    bool hasPadsOn;
    bool improperPlacement;
    string name;
    PatientType patientType;
    void boundHeartRate();
};

#endif // PATIENT_H

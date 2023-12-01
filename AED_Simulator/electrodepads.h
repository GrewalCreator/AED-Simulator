#ifndef ELECTRODEPADS_H
#define ELECTRODEPADS_H

#include "defs.h"
#include "PatientType.h"

class ElectrodePads
{
public:
    ElectrodePads();
    bool isOnPatient();
    bool isConnectedToAED();

    void setPadPlacement(bool onPatient);
    void setIsConnectedToAED(bool connectedToAED);

    const PatientType& getPadType();
    void setPadType(const PatientType& type);

private:
    bool onPatient;
    bool connectedToAED;
    PatientType padType;
};

#endif // ELECTRODEPADS_H

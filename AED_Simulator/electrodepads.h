#ifndef ELECTRODEPADS_H
#define ELECTRODEPADS_H

#include "defs.h"
#include "PatientType.h"

class ElectrodePads
{
public:
    explicit ElectrodePads();
    bool isOnPatient() const;
    bool isConnectedToAED() const;

    void setPadPlacement(bool onPatient);
    void setIsConnectedToAED(bool connectedToAED);

    const PatientType& getPadType() const;
    void setPadType(const PatientType& type);

private:
    bool onPatient;
    bool connectedToAED;
    PatientType padType;
};

#endif // ELECTRODEPADS_H

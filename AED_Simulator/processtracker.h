#ifndef PROCESSTRACKER_H
#define PROCESSTRACKER_H

#include "ProcessSteps.h"

class ProcessTracker
{
public:
    ProcessTracker();
    const ProcessSteps& getCurrentStep() const;
    const ProcessSteps& getPreviousStep() const;

    void setCurrentStep(const ProcessSteps&);
private:
    ProcessSteps previousStep;
    ProcessSteps currentStep;

    void setPreviousStep(const ProcessSteps&);
};

#endif // PROCESSTRACKER_H

#include "processtracker.h"

ProcessTracker::ProcessTracker(){
}


const ProcessSteps& ProcessTracker::getCurrentStep() const{
    return this->currentStep;
}

const ProcessSteps& ProcessTracker::getPreviousStep() const{
    return this->previousStep;
}

void ProcessTracker::setCurrentStep(const ProcessSteps& step){
    setPreviousStep(currentStep);
    currentStep = step;
}

void ProcessTracker::setPreviousStep(const ProcessSteps& step){
    previousStep = step;
}

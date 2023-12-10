#ifndef AEDSTATE_H
#define AEDSTATE_H

#include "aedcontroller.h"
#define VARIABILITY 4
class AEDState
{
public:
    virtual void stepProgress() = 0;
    explicit AEDState(AEDController*);


protected:
    AEDController* controller;
    QElapsedTimer timer;
    int delay;
    int compressionTarget;
    int compressionsDone;
};

class PowerOnState : public AEDState {
public:
    using AEDState::AEDState;
    virtual void stepProgress() override;
};

class CheckPatientState : public AEDState {
public:
    using AEDState::AEDState;
    virtual void stepProgress() override;
};

class GetHelpState : public AEDState {
public:
    using AEDState::AEDState;
    virtual void stepProgress() override;
};

class PadPlacementState : public AEDState {
public:
    using AEDState::AEDState;
    virtual void stepProgress() override;
};

class AnalysisState : public AEDState {
public:
    using AEDState::AEDState;
    virtual void stepProgress() override;

};

class ShockableState : public AEDState {
public:
    using AEDState::AEDState;
    virtual void stepProgress() override;
};

class ShockState : public AEDState {
public:
    using AEDState::AEDState;
    virtual void stepProgress() override;
};

class CompressionsState : public AEDState {
public:
    CompressionsState();
    using AEDState::AEDState;
    virtual void stepProgress() override;
};


#endif // AEDSTATE_H

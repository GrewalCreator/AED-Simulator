#ifndef AEDSTATE_H
#define AEDSTATE_H

#include "aedcontroller.h"

class AEDState
{
public:
    virtual void stepProgress() = 0;
    AEDState(AEDController*);

protected:
    AEDController* controller;
    int delay;

};

class PowerOnState : public AEDState {//we probably don't need this.
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
    using AEDState::AEDState;
    virtual void stepProgress() override;
};

class NominalState : public AEDState {
public:
    using AEDState::AEDState;
    virtual void stepProgress() override;
};
#endif // AEDSTATE_H

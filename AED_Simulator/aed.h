#ifndef AED_H
#define AED_H

class AEDController;

class AED
{
public:
    AED(AEDController& controller);

private:
    AEDController* controller;
};

#endif // AED_H

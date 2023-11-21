#ifndef AED_H
#define AED_H

class Controller;

class AED
{
public:
    AED(Controller& controller);

private:
    Controller* controller;
};

#endif // AED_H

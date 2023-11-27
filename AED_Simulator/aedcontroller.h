#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H
#include <QObject>
#include "defs.h"
#include "aed.h"
#include "testcontroller.h"
#include "logger.h"
#include "SignalType.h"
#include "AudioTypes.h"
#include "processtracker.h"

class TestController;

class AEDController: public QObject{
    Q_OBJECT
public:
    AEDController(QObject* parent = nullptr);
    void setController(TestController* controller);
    AED* getAED();
    Logger* getLogger();
    virtual ~AEDController();
    void sendStaticSignal(const SignalType& signalType);
    void sendDynamicSignal(const SignalType& signalType, const string& data);
    bool powerAEDOn();
    void setProcessTracker(const ProcessSteps& step);

private:
    AED* automatedED;
    TestController* testControlSystem;
    Logger* logger;
    ProcessTracker* processTracker;


signals:
    void dynamicSignal(const SignalType& sig, const string& data);
    void staticSignal(const SignalType& sig);
};

#endif // AEDCONTROLLER_H

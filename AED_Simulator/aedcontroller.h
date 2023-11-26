#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H
#include <QObject>
#include "defs.h"
#include "aed.h"
#include "testcontroller.h"
#include "logger.h"
#include "SignalType.h"
#include "AudioTypes.h"


class TestController;

class AEDController: public QObject{
    Q_OBJECT
public:
    AEDController(QObject* parent = nullptr);
    void setController(TestController* controller);
    AED* getAED();
    Logger* getLogger();
    virtual ~AEDController();
    void testSignals();
    void sendStaticSignal(const SignalType& signalType);
    void sendDynamicSignal(const SignalType& signalType, const string& data);

private:
    AED* automatedED;
    TestController* testControlSystem;
    Logger* logger;


signals:
    void dynamicSignal(const SignalType& sig, const string& data);
    void staticSignal(const SignalType& sig);
};

#endif // AEDCONTROLLER_H

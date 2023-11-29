#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H
#include <QObject>
#include "defs.h"
#include "aed.h"
#include "testcontroller.h"
#include "logger.h"
#include "SignalType.h"
#include "AudioTypes.h"
#include "QRunnable"
#include "processtracker.h"
#include "QSemaphore"

class TestController;

class AEDTransmitter: public QObject{
    Q_OBJECT
public:
    AEDTransmitter(QObject* parent = nullptr);
    void sendDynamic(const SignalType& sig, const string& data);
    void sendStatic(const SignalType& sig);
signals:
    void dynamicSignal(const SignalType& sig, const string& data);
    void staticSignal(const SignalType& sig);
};


class AEDController: public QObject{
    Q_OBJECT
public:
    AEDController(QSemaphore* sem, QObject* parent = nullptr);
    void setController(TestController* controller);
    AED* getAED();
    Logger* getLogger();
    AEDTransmitter* transmit;
    virtual ~AEDController();
    void testSignals();
    void sendStaticSignal(const SignalType& signalType);
    void sendDynamicSignal(const SignalType& signalType, const string& data);
    bool powerAEDOn();
    bool powerAEDOff();
    void setProcessTracker(const ProcessSteps& step);
    const ProcessSteps& getProcessTracker();

private:
    void checkAll();
    QSemaphore* semaphore;
    bool breakflag;
    AED* automatedED;
    TestController* testControlSystem;
    Logger* logger;
    ProcessTracker* processTracker;
    void cleanup();
private slots:
    void run();

};





#endif // AEDCONTROLLER_H

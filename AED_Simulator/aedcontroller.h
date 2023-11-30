#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H
#include <QObject>
#include "QSemaphore"

#include "defs.h"
#include "aed.h"
#include "testcontroller.h"
#include "logger.h"
#include "SignalType.h"
#include "AudioTypes.h"
#include "processtracker.h"
#include "heartrategenerator.h"
#include "PatientType.h"

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
    HeartRateGenerator* getHeartRateGenerator();
    void placePads(PatientType);

private:
    void checkAll();
    void updateHR();
    QSemaphore* semaphore;
    bool breakflag;
    AED* automatedED;
    TestController* testControlSystem;
    Logger* logger;
    ProcessTracker* processTracker;
    HeartRateGenerator* heartRateGenerator;
    void cleanup();
private slots:
    void run();
};





#endif // AEDCONTROLLER_H

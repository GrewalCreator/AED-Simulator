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
class AEDController: public QRunnable{


public:
    AEDController(QObject* parent = nullptr);
    void setController(TestController* controller);
    AED* getAED();
    Logger* getLogger();
    void run() override;
    AEDTransmitter* transmit;
    virtual ~AEDController();
    void cleanup();
    void testSignals();
    void sendStaticSignal(const SignalType& signalType);
    void sendDynamicSignal(const SignalType& signalType, const string& data);

private:
    void checkAll();
    AED* automatedED;
    TestController* testControlSystem;
    Logger* logger;
};




#endif // AEDCONTROLLER_H

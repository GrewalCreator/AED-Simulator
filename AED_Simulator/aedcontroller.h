#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H
#include <QObject>
#include "defs.h"
#include "aed.h"
#include "testcontroller.h"
#include "logger.h"


class TestController;

class AEDController: public QObject{
    Q_OBJECT
public:
    AEDController(QObject* parent = nullptr);
    void setController(TestController* controller);
    AED* getAED();
    Logger* getLogger();
    virtual ~AEDController();

private:
    AED* automatedED;
    TestController* testControlSystem;
    Logger* logger;

signals:
    void dynamicSignal(SignalType sig, string& data);
    void staticSignal(SignalType sig);
};

#endif // AEDCONTROLLER_H

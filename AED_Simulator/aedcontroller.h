#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H
#include <QObject>
#include "defs.h"
#include "aed.h"
#include "testcontroller.h"

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
};

#endif // AEDCONTROLLER_H

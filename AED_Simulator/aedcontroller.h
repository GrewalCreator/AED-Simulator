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
    virtual ~AEDController();

private:
    AED* automatedED;
    TestController* testControlSystem;
};

#endif // AEDCONTROLLER_H

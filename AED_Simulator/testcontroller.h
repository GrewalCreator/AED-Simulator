#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include "aedcontroller.h"
class AEDController;

class TestController: public QObject{
    Q_OBJECT


public slots:
    void testAudio();


public:
    TestController(QObject* parent = nullptr);

    void setController(AEDController* controller);

    virtual ~TestController();


private:
    AEDController* controlSystem;
};

#endif // TESTCONTROLLER_H

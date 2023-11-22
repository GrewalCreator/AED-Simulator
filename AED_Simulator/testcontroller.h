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

    void setController(QObject* controller);

    virtual ~TestController();


private:
    QObject* controlSystem;
};

#endif // TESTCONTROLLER_H

#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include "aedcontroller.h"

class AEDController;

class TestController: public QObject{
    Q_OBJECT


public slots:
    void updateHeartRate(int);
signals:
    void updateHeartRateImage(vector<double>&, vector<double>&);

public:
    TestController(QObject* parent = nullptr);

    void setController(AEDController* controller);

    virtual ~TestController();


private:
    AEDController* controlSystem;
};

#endif // TESTCONTROLLER_H

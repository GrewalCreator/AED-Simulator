#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include "aedcontroller.h"
#include "PatientType.h"

class AEDController;

class TestController: public QObject{
    Q_OBJECT


public slots:

signals:
    void updateHeartRateImage(vector<double>&, vector<double>&);

public:
    TestController(QObject* parent = nullptr);

    void setController(AEDController* controller);

    virtual ~TestController();

    void placePads(PatientType);
    void updateHeartRate(int);


private:
    AEDController* controlSystem;
};

#endif // TESTCONTROLLER_H

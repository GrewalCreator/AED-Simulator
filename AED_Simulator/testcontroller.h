#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include "aedcontroller.h"
#include "PatientType.h"

class AEDController;

class TestController: public QObject{
    Q_OBJECT


public slots:
    void removePadsOffPatient();
    void togglePadAED();
    void toggleWetPatient();
    void depleteBattery();

signals:
    void updateHeartRateImage(vector<double>&);
    void sliderUpdate();
    void updateHR_LCD();


public:
    TestController(QObject* parent = nullptr);

    AEDController* getControlSystem();

    void setController(AEDController* controller);


    void updateHeartRate();

    void placePads(const PatientType& type);

    void updateSlider();
    int getCurrentHeartRate();
    virtual ~TestController();





private:
    AEDController* controlSystem;
};

#endif // TESTCONTROLLER_H

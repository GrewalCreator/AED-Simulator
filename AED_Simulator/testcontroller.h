#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include "aedcontroller.h"
#include "PatientType.h"

class AEDController;

class TestController: public QObject{
    Q_OBJECT


public slots:
    void removePadsFromPatient() const;
    void togglePadConnection() const;
    void toggleWetPatient(int) const;
    void depleteBattery() const;

signals:
    void updateHeartRateImage(vector<double>&);
    void sliderUpdate();
    void updateHR_LCD();
    void uiDisable();


public:
    explicit TestController(QObject* parent = nullptr);

    AEDController* getControlSystem() const;
    void disableUI();

    void setController(AEDController* controller);

    int getSessionCompressions() const;
    void incrementSessionCompressions();

    void resetSessionCompressions();

    void updateCompressionHeartRate() const;

    void updateHeartRate();

    void placePads(const PatientType& type) const;

    void updateSlider();
    int getCurrentHeartRate() const;
    virtual ~TestController();





private:
    AEDController* controlSystem;
    int sessionCompressions;
    int totalCompressions;
};

#endif // TESTCONTROLLER_H

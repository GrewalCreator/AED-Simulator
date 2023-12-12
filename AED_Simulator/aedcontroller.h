#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H
#include <QObject>
#include "QSemaphore"

#include "defs.h"
#include "aed.h"
#include "testcontroller.h"
#include "logger.h"
#include "SignalType.h"
#include "AudioTypes.h"
#include "processtracker.h"
#include "heartrategenerator.h"
#include "PatientType.h"
#include "electrodepads.h"
#include "patient.h"

class AEDState;
class TestController;

class AEDTransmitter: public QObject{
    Q_OBJECT
public:
    explicit AEDTransmitter(QObject* parent = nullptr);
    void sendDynamic(const SignalType& sig, const string& data);
    void sendStatic(const SignalType& sig, bool state);
signals:
    void dynamicSignal(const SignalType& sig, const string& data);
    void staticSignal(const SignalType& sig, bool state);

};


class AEDController: public QObject{
    Q_OBJECT
public:
    explicit AEDController(QSemaphore* sem, QObject* parent = nullptr);
    AEDTransmitter* getTransmitter() const;
    void setController(TestController* controller);
    void updateHR(int heartRate);
    void toggleActivePatient();
    AED* getAED() const;
    void log(const QString& message) const;

    void print(const string& message) const;


    void sendStaticSignal(const SignalType& signalType, bool state = true) const;

    bool powerAEDOn() const;
    bool powerAEDOff();

    int getTimeElapsed() const;
    void resetTimeElapsed();
    void setState(const ProcessSteps&);


    void setCurrentStep(const ProcessSteps& step);
    const ProcessSteps& getCurrentStep() const;

    void recharge();
    void standClear();
    bool shockPressed();
    void decreaseBPM(int amperage);
    void setProcessTracker(const ProcessSteps& step);
    const ProcessSteps& getProcessTracker() const;
    bool getDeathFlag() const;
    void updateSlider();
    TestController* getTestController() const;

    HeartRateGenerator* getHeartRateGenerator() const;

    bool placePads(const PatientType& type);
    Patient* getPatient() const;
    ElectrodePads* getPads() const;


    void checkOk();
    void getHelp() const;

    void illuminate(const SignalType&);

    bool getErrorFlag() const;
    virtual ~AEDController();



private:
    void initStates();
    AEDTransmitter* transmit;
    void systemsCheck();


    int timeElapsed;
    QSemaphore* semaphore;
    bool breakflag;
    bool errorFlag;
    AED* automatedED;
    void stepProgress();
    TestController* testControlSystem;
    Logger* logger;
    ProcessTracker* processTracker;
    HeartRateGenerator* heartRateGenerator;
    ElectrodePads* pads;
    Patient* patientAdult;
    Patient* patientChild;
    Patient* activePatient;
    AEDState* currentState;
    bool deathFlag;

    void slowDeath();



    QMap<ProcessSteps, AEDState*> states;
    void cleanup();
    void sendDynamicSignal(const SignalType& signalType, const string& data) const;


private slots:
    void run();

};





#endif // AEDCONTROLLER_H

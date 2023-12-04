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
    AEDTransmitter(QObject* parent = nullptr);
    void sendDynamic(const SignalType& sig, const string& data);
    void sendStatic(const SignalType& sig, bool state);
signals:
    void dynamicSignal(const SignalType& sig, const string& data);
    void staticSignal(const SignalType& sig, bool state);
};


class AEDController: public QObject{
    Q_OBJECT
public:
    AEDTransmitter* getTransmitter();
    AEDController(QSemaphore* sem, QObject* parent = nullptr);
    void setController(TestController* controller);

    AED* getAED() const;
    Logger* getLogger() const;

    void print(string message);

    void sendStaticSignal(const SignalType& signalType, bool state);
    void sendDynamicSignal(const SignalType& signalType, const string& data);
    bool powerAEDOn();
    bool powerAEDOff();

    int getTimeElapsed() const;
    void resetTimeElapsed();
    void setState(ProcessSteps);// public so that states can set other states


    void setCurrentStep(const ProcessSteps& step);
    const ProcessSteps& getCurrentStep() const;

    void recharge();
    void standClear();
    bool shockPressed();
    void decreaseBPM(int amperage);
    void setProcessTracker(const ProcessSteps& step);
    const ProcessSteps& getProcessTracker() const;

    void updateSlider();
    TestController* getTestController() const;

    HeartRateGenerator* getHeartRateGenerator() const;

    bool placePads(const PatientType& type);
    Patient* getPatient() const;
    ElectrodePads* getPads() const;

    ElectrodePads* getPads();

    void checkOk();
    void getHelp();

    void illuminate(SignalType);

    bool getErrorFlag();
    virtual ~AEDController();



private:
    void initStates();
    AEDTransmitter* transmit;
    void systemsCheck();
    void checkAll();
    void updateHR();
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



    QMap<ProcessSteps,AEDState*> states;
    void cleanup();


private slots:
    void run();

};





#endif // AEDCONTROLLER_H

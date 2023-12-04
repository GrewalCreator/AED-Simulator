#include "aed.h"
#include "aedcontroller.h"
#include "mediaplayer.h"

#define AMPERAGE 20

AED::AED(AEDController& controller): controller(&controller){
    audioPlayer = new MediaPlayer();
    battery = new Battery();
    numShocks = 0;
    amperage = AMPERAGE;
    shockPressed= false;
}

void AED::playAudio(const AudioTypes& audio){
    audioPlayer->play(audio);
}

bool AED::powerOn(){
    // Run General Safety Checks
    if(!safetyChecks()){return false;}

    controller->getLogger()->log("AED Powering On");
    audioPlayer->play(INTRO_AUDIO);
    return true;


}


bool AED::safetyChecks(){

    return true;
}

bool AED::checkShockSafety(){
    return controller->getCurrentStep() == SHOCK ? true : false;
}

Battery* AED::getBattery() const{return this->battery;}

bool AED::getShockPressed(){
    return shockPressed;
}

int AED::getAmperage(){
    return amperage;
}

void AED::resetShockPressed(){
    shockPressed = false;
}

bool AED::shock(){

    if(!checkShockSafety()){
        return false;
    }
    if(controller->getPatient()->getIsInWater()){
        controller->getPatient()->setHeartRate(MAX_BPM);
        controller->sendDynamicSignal(HEART_RATE,std::to_string(controller->getPatient()->getHeartRate()));

    }

    if(battery->getBatteryLevels() < 30){
        controller->print("BATTERY LEVELS TOO LOW, PLEASE REPLACE");
        return false;
    }

    int currentHR = getCurrentHR();
    controller->updateHR(currentHR - randomModifier(currentHR - 105));

    controller->getLogger()->log("Shocking!");



    battery->depleteBatteryLevel();

    return true;
}

int AED::randomModifier(int diff) {
    srand(time(0));

    if (!controller->getPatient()->getHasPadsOn()) {
        qDebug() << "You Shouldn't Be In AED::randomModifier. This is a bug.";
        return 0;
    }

    PatientType patientType = controller->getPatient()->getPatientType();
    PatientType padType = controller->getPads()->getPadType();

    int shockedAmps = 0;
    if ((patientType == CHILD && padType == CHILD) || (patientType == ADULT && padType == ADULT)) {
        shockedAmps = random(0, ceil(sqrt(diff)));
        qDebug() << "SHOCKING SAME WITH SAME PADS FROM POSSIBLE RANGE 0 -" << ceil(sqrt(diff));
    } else if (padType == CHILD && patientType == ADULT) {
        shockedAmps = random(0, ceil(cbrt(diff)));
        qDebug() << "SHOCKING ADULT WITH CHILD PADS FROM POSSIBLE RANGE 0 -" << ceil(cbrt(diff));
    } else if (padType == ADULT && patientType == CHILD) {
        shockedAmps = random(diff, getCurrentHR());
        qDebug() << "SHOCKING CHILD WITH ADULT PADS FROM POSSIBLE RANGE 0 -" << getCurrentHR();
    }

    qDebug() << "Shocking At Amps: " << shockedAmps;

    return shockedAmps;
}

void AED::setShockPressed(){
    shockPressed = true;
}

int AED::random(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int AED::getCurrentHR(){
    return controller->getPatient()->getHeartRate();
}


AED::~AED(){
    delete battery;
    delete audioPlayer;
}

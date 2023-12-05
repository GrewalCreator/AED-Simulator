#include "aed.h"
#include "aedcontroller.h"
#include "mediaplayer.h"


AED::AED(AEDController& controller): controller(&controller){
    audioPlayer = new MediaPlayer();
    battery = new Battery();
    numShocks = 0;
    shockPressed= false;
}

void AED::playAudio(const AudioTypes& audio){
    audioPlayer->play(audio);
}

bool AED::powerOn(){
    // Run General Safety Checks
    if(!safetyChecks()){return false;}

    controller->log("AED Powering On");
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



void AED::resetShockPressed(){
    shockPressed = false;
}

bool AED::shock(){

    if(!checkShockSafety()){
        return false;
    }
    if(controller->getPatient()->getIsInWater()){
        controller->updateHR(MAX_BPM);
        controller->sendStaticSignal(HEART_RATE);

    }

    if(battery->getBatteryLevels() < 30){
        controller->print("BATTERY LEVELS TOO LOW, PLEASE REPLACE");
        return false;
    }

    int currentHR = getCurrentHR();

    controller->updateHR(currentHR - randomModifier(currentHR - 105));

    audioPlayer->play(STAND_CLEAR);
    controller->log("Shocking!");



    battery->depleteBatteryLevel();

    return true;
}

int AED::randomModifier(int diff) {
    srand(time(0));

    if (!controller->getPatient()->getHasPadsOn()) {return 0;}

    PatientType patientType = controller->getPatient()->getPatientType();
    PatientType padType = controller->getPads()->getPadType();

    int shockedAmps = 0;
    if ((patientType == CHILD && padType == CHILD) || (patientType == ADULT && padType == ADULT)) {
        shockedAmps = random(0, ceil(diff/2));

        controller->log("SHOCKING SAME WITH SAME PADS FROM POSSIBLE RANGE 0 -" + QString::number(diff/2));
    } else if (padType == CHILD && patientType == ADULT) {
        shockedAmps = random(0, ceil(diff/3));
        controller->log("SHOCKING ADULT WITH CHILD PADS FROM POSSIBLE RANGE 0 -" + QString::number(diff/3));
    } else if (padType == ADULT && patientType == CHILD) {
        shockedAmps = random(diff, getCurrentHR());
        controller->log("SHOCKING CHILD WITH ADULT PADS FROM POSSIBLE RANGE 0 -" + QString::number(getCurrentHR()));
    }

    controller->log("Shocking At Amps: " + QString::number(shockedAmps));

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

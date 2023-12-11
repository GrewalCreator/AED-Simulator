#include "aed.h"
#include "aedcontroller.h"
#include "mediaplayer.h"

// AED Constructor
AED::AED(AEDController& controller): controller(&controller){
    audioPlayer = new MediaPlayer();
    battery = new Battery();
    shockPressed= false;
}

// Access AED MediaPlayer to play an Audio File
void AED::playAudio(const AudioTypes& audio){
    audioPlayer->play(audio);
}

bool AED::powerOn(){
    controller->log("AED Powering On");
    return true;
}

// Check if AED is in the SHOCK State. Shocking should not be possible outside this state
bool AED::checkShockSafety() const{
    return controller->getCurrentStep() == SHOCK ? true : false;
}

Battery* AED::getBattery() const{return this->battery;}

bool AED::getShockPressed() const{
    return shockPressed;
}

void AED::resetShockPressed(){
    shockPressed = false;
}

void AED::setShockPressed(){
    shockPressed = true;
}

/*
 * Shock Patient When Shock Button is Pressed
 * If Not in SHOCK state, return false
 * Determines the affect the shock will have on the patient based on the Pads placed
*/

bool AED::shock() const{
    if(!checkShockSafety()){
        return false;
    }

    // If Batter is below 30%, unable to shock
    if(battery->getBatteryLevels() < 30){
        controller->print("BATTERY LEVELS TOO LOW, PLEASE REPLACE");
        return false;
    }

    audioPlayer->play(SHOCKING_AUDIO);
    controller->log("Shocking!");

    int currentHR = getCurrentHR();
    int userDeath = false;

    // If the patient is shocked in water, HeartRate Spikes to MAX_BPM & user dies
    if(controller->getPatient()->isInConductiveEnvironment()){
        controller->updateHR(MAX_BPM);
        userDeath = true;
    }else{
        controller->updateHR(currentHR - randomModifier(currentHR - 105));
    }

    battery->depleteBatteryLevel();

    if(userDeath){
        controller->sendStaticSignal(DEATH);
    }

    return true;
}

// Determine Shock based on pad placement
int AED::randomModifier(int diff) const{
    srand(time(0));

    if (!controller->getPatient()->getHasPadsOn()) {return 0;}

    PatientType patientType = controller->getPatient()->getPatientType();
    PatientType padType = controller->getPads()->getPadType();

    int shockedAmps = 0;
    if ((patientType == CHILD && padType == CHILD) || (patientType == ADULT && padType == ADULT)) {
        shockedAmps = random(0, ceil(diff/2));

        controller->log("SHOCKING PATIENT WITH COORECT PADS FROM POSSIBLE RANGE 0 -" + QString::number(diff/2));
    } else if (padType == CHILD && patientType == ADULT) {
        shockedAmps = random(0, ceil(diff/3));
        controller->log("SHOCKING ADULT WITH CHILD PADS FROM POSSIBLE RANGE 0 -" + QString::number(diff/3));
    } else if (padType == ADULT && patientType == CHILD) {
        shockedAmps = random(diff, getCurrentHR());
        controller->log("SHOCKING CHILD WITH ADULT PADS FROM POSSIBLE RANGE 0 -" + QString::number(getCurrentHR()));
    }

    controller->log("Shocking At: " + QString::number(shockedAmps));

    return shockedAmps;
}

// Generate random number between min & max
int AED::random(int min, int max) const{
    return QRandomGenerator::global()->bounded(min, max+1);
}

int AED::getCurrentHR() const{
    return controller->getPatient()->getHeartRate();
}


AED::~AED(){
    delete battery;
    delete audioPlayer;
}

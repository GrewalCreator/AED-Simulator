#include "aedstate.h"



AEDState::AEDState(AEDController* c){
    controller = c;
    delay = 0;
}

void PowerOnState::stepProgress(){

    if(controller->getErrorFlag()){
        controller->getAED()->resetShockPressed();//for the case where we get an error mid-shock
        if(controller->getAED()->getBattery()->getBatteryLevels()<=20){
            controller->print("CHANGE BATTERIES.");
            //set the status light to red and don't move on
        }
        else if(!controller->getPads()->isConnectedToAED()){
            controller->print("PLUG IN ELECTRODE CABLE.");
        }
    }

    if (controller->getPatient()->getHasPadsOn()){
        if (controller->getPatient()->getImproperPlacement()){
            controller->setState(ELECTRODE_PAD_PLACEMENT);
        }else{
            controller->setState(ANALYZE_ECG);
        }
    }else{
        controller->setState(CHECK_OK);
    }
    delay = 0;
    controller->resetTimeElapsed();
}

void CheckPatientState::stepProgress(){
    delay++;
    controller->print("PLEASE CHECK IF THE PATIENT IS OK.");
    controller->illuminate(LIGHTUP_OK);

    if(controller->getTimeElapsed()>10){
        controller->setState(GET_HELP);
        delay = 0;
        controller->resetTimeElapsed();
    }
}

void GetHelpState::stepProgress(){
    delay++;
    controller->print("PLEASE CALL FOR HELP OR CALL 911.");
    controller->illuminate(LIGHTUP_911);

    if(controller->getTimeElapsed()>10){
        delay = 0;
        controller->setState(ELECTRODE_PAD_PLACEMENT);
        controller->resetTimeElapsed();
    }
}

void PadPlacementState::stepProgress(){
    controller->illuminate(LIGHTUP_PADS);
    qDebug()<<controller->getPatient()->getHasPadsOn();
    if(!controller->getPatient()->getHasPadsOn()){
        controller->print("PLACE PADS ON THE PATIENT.");
    }
    else if(controller->getPatient()->getHasPadsOn() && !controller->getPatient()->getImproperPlacement()){//IMPORTANT: if pads are on and they are properly placed. replace this with a proper check function later.
        delay++;
        if(delay<10){
            controller->print("PADS SUCESSFULLY ATTACHED.");
        }
        else{
            delay = 0;
            controller->resetTimeElapsed();
            controller->setState(ANALYZE_ECG);
        }
    }
    else if(controller->getPatient()->getHasPadsOn() && controller->getPatient()->getImproperPlacement()){//if patient has pads on but not properly placed. again, replace this with a simple function. this is ugly and not reusable.
        controller->print("CHECK ELECTRODE PADS");
    }
}


void AnalysisState::stepProgress(){
    controller->getAED()->resetShockPressed();
    if(!controller->getPatient()->getHasPadsOn()){
        controller->setState(ELECTRODE_PAD_PLACEMENT);
    }
    delay++;
    controller->illuminate(LIGHTUP_STANDCLEAR);
    if(delay <= 10){
        controller->print("ANALYZING PATIENT... DON'T TOUCH!");
    }
    else{
        if(controller->getPatient()->getHeartRate() > MAX_NOMINAL_BPM){
            delay = 0;
            controller->resetTimeElapsed();
            controller->setState(SHOCK);
        }
        else if(controller->getPatient()->getHeartRate() < MIN_NOMINAL_BPM){
            delay = 0;
            controller->resetTimeElapsed();
            controller->setState(CPR);
        }
        else{
            controller->print("Patient is nominal.");
        }
    }

}

void ShockState::stepProgress(){
    if(!controller->getPatient()->getHasPadsOn()){
        controller->setState(ELECTRODE_PAD_PLACEMENT);
    }
    controller->illuminate(LIGHTUP_SHOCK);
    controller->print("SHOCKABLE RHYTHM DETECTED.");
    if(controller->getPatient()->getHeartRate() <= MAX_NOMINAL_BPM){
        delay = 0;
        controller->setState(ANALYZE_ECG);
    }

    if(controller->getAED()->getShockPressed()){
            if(delay<4){
                controller->print("3...");
            }
            else if(delay<8){
                controller->print("2...");
            }
            else if(delay<12){
                controller->print("1...");
            }
            else if(delay >= 12){
                controller->getAED()->shock();
                delay = 0;
                controller->resetTimeElapsed();
                controller->setState(CPR);
            }
        delay++;
    }
}

void CompressionsState::stepProgress(){
    if(!controller->getPatient()->getHasPadsOn()){
        controller->setState(ELECTRODE_PAD_PLACEMENT);
    }

    controller->illuminate(LIGHTUP_COMPRESSIONS);
    if(controller->getPatient()->getHeartRate() <= MIN_NOMINAL_BPM){
        controller->print("UNSHOCKABLE RHYTHM DETECTED. SHOCK NOT ADVISED.");
    }
    else if(controller->getAED()->getShockPressed() && controller->getPatient()->getHeartRate() >= MAX_NOMINAL_BPM){
        controller->print("SHOCK DELIVERED. STARTING COMPRESSIONS...");
    }
    else{//IMPORTANT: if the patient's HR enters the nominal range, do we want to stop compressions? right now, if we get them into this range, then we stop and analyse.
        delay = 0;
        controller->resetTimeElapsed();
        controller->setState(ANALYZE_ECG);
    }

    if(delay < 120){//2 minutes for compression stage
        //do compression stuff here

    }
    else{
        delay = 0;
        controller->resetTimeElapsed();
        controller->setState(ANALYZE_ECG);
    }
    delay++;
}

void NominalState::stepProgress(){
    controller->print("PLACEHOLDER MESSAGE FOR AFTERCARE/NOMINAL");

}

#include "aedstate.h"
#include "defs.h"




AEDState::AEDState(AEDController* c){
    controller = c;
    delay = 0;

    compressionTarget = 9;
    compressionsDone = 0;
}



void PowerOnState::stepProgress(){
    //controller->log("In Power On State");
    controller->getTestController()->resetSessionCompressions();

    if(controller->getErrorFlag()){
        controller->getAED()->resetShockPressed();//for the case where we get an error mid-shock
        controller->illuminate(RESET);
        if(controller->getAED()->getBattery()->getBatteryLevels()<30){
            controller->print("CHANGE BATTERIES.");

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
    //controller->log("In Check Patient State");
    controller->print("PLEASE CHECK IF THE PATIENT IS OK.");
    controller->illuminate(LIGHTUP_OK);



    if(controller->getTimeElapsed()>10){
        controller->setState(GET_HELP);
        delay = 0;
        controller->resetTimeElapsed();
    }

   delay++;

}

void GetHelpState::stepProgress(){
    //controller->log("In Get Help State");
    ++delay;
    controller->print("PLEASE CALL FOR HELP OR CALL 911.");
    controller->illuminate(LIGHTUP_911);
    if(delay == 1) controller->getAED()->playAudio(INTRO_AUDIO);

    if(controller->getTimeElapsed()>10){
        delay = 0;
        controller->setState(ELECTRODE_PAD_PLACEMENT);
        controller->resetTimeElapsed();
    }
}

void PadPlacementState::stepProgress(){
    //controller->log("In Pad Placement Step");
    controller->illuminate(LIGHTUP_PADS);
    if(!controller->getPatient()->getHasPadsOn()){
        controller->print("PLACE PADS ON THE PATIENT.");
    }
    else if(controller->getPatient()->getHasPadsOn() && !controller->getPatient()->getImproperPlacement()){
        ++delay;
        if(delay<10){
            controller->print("PADS SUCCESSFULLY ATTACHED.");
        }
        else{
            delay = 0;
            controller->resetTimeElapsed();
            controller->setState(ANALYZE_ECG);
        }
    }
    else if(controller->getPatient()->getHasPadsOn() && controller->getPatient()->getImproperPlacement()){
        controller->print("CHECK ELECTRODE PADS");
    }
}


void AnalysisState::stepProgress(){
    //controller->log("In Analysis State");
    controller->getAED()->resetShockPressed();
    if(!controller->getPatient()->getHasPadsOn()){
        controller->setState(ELECTRODE_PAD_PLACEMENT);
    }
    ++delay;
    controller->illuminate(LIGHTUP_STANDCLEAR);
    if(delay <= 10){
        controller->print("ANALYZING PATIENT... DON'T TOUCH!");
    }
    else{
        int heartRate = controller->getPatient()->getHeartRate();
        if(heartRate > MAX_NOMINAL_BPM){
            delay = 0;
            controller->resetTimeElapsed();
            controller->setState(SHOCK);
        }
        else if(heartRate < MIN_NOMINAL_BPM){
            delay = 0;
            controller->resetTimeElapsed();
            controller->setState(CPR);
        }
        else{
            controller->print("Patient has nominal BPM.");
        }
    }

}

void ShockState::stepProgress(){
    //controller->log("In Shock State");
    if(!controller->getPatient()->getHasPadsOn()){
        controller->setState(ELECTRODE_PAD_PLACEMENT);
    }
    controller->illuminate(LIGHTUP_SHOCK);
    if(!controller->getAED()->getShockPressed()){
        controller->print("SHOCKABLE RHYTHM DETECTED.");
    }
    if(controller->getPatient()->getHeartRate() <= MAX_NOMINAL_BPM){
        delay = 0;
        controller->setState(ANALYZE_ECG);
    }

    if(controller->getAED()->getShockPressed()){
            if(delay==0){
                controller->getAED()->playAudio(STAND_CLEAR);
                controller->print("3...");
            }
            else if(delay==6){
                controller->getAED()->playAudio(CHARGING_AUDIO);
                controller->print("2...");
            }
            else if(delay==18){
                controller->print("1...");
            }
            else if(delay >= 20){
                controller->getAED()->shock();
                delay = 0;
                controller->resetTimeElapsed();
                controller->setState(CPR);
            }
        ++delay;
    }
}

void CompressionsState::stepProgress(){
    //controller->log("In Compression State");
    if(!controller->getPatient()->getHasPadsOn()){
        controller->setState(ELECTRODE_PAD_PLACEMENT);
    }

    controller->illuminate(LIGHTUP_COMPRESSIONS);
    if(controller->getPatient()->getHeartRate() < MIN_NOMINAL_BPM){
        if(controller->getPatient()->isDead()){
            controller->print("Patient is asystolic.");
        }else if(delay<=10){
            controller->print("UNSHOCKABLE RHYTHM DETECTED. SHOCK NOT ADVISED. BEGIN COMPRESSIONS");
        }
    }
    else if(controller->getAED()->getShockPressed() && controller->getPatient()->getHeartRate() > MAX_NOMINAL_BPM){
        if(delay<=10)controller->print("SHOCK DELIVERED. STARTING COMPRESSIONS...");
    }
    else{
        controller->getTestController()->resetSessionCompressions();
        delay = 0;
        controller->resetTimeElapsed();
        controller->setState(ANALYZE_ECG);
    }


    if(10 < delay && delay < 60){
        compressionsDone = controller->getTestController()->getSessionCompressions() - (delay / 5);

        if(compressionsDone <= compressionTarget - VARIABILITY){

            controller->print("Compressions Too Slow. Please Speed Up");
        }else if(compressionsDone >= compressionTarget + VARIABILITY){

            controller->print("Compressions Too Fast. Please Slow Down");
        }else{

            controller->print("Steady Compression Rhythm");
            controller->getTestController()->updateCompressionHeartRate();


        }
    }
    else if (delay > 60){
        controller->getTestController()->resetSessionCompressions();
        delay = 0;
        controller->resetTimeElapsed();
        controller->setState(ANALYZE_ECG);
    }
    ++delay;
}



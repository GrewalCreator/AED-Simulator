#include "aedstate.h"

AEDState::AEDState(AEDController* c){
    controller = c;
    delay = 0;
}

void PowerOffState::stepProgress(){
    controller->setState(CHECK_OK);//example of switching state to the next step. if there is actually any useful logic for the off state, put it here.
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
    controller->print("Place pads on the patient.");
    qDebug()<<controller->getPatient()->getHasPadsOn();
    if(controller->getPatient()->getHasPadsOn() && !controller->getPatient()->getImproperPlacement()){//IMPORTANT: if pads are on and they are properly placed. replace this with a proper check function later.
        delay++;
        if(delay<10){
            controller->print("PADS SUCESSFULLY ATTACHED.");
        }
        else{
            delay = 0;
            controller->setState(ANALYZE_ECG);
        }
    }
    else if(controller->getPatient()->getHasPadsOn() && controller->getPatient()->getImproperPlacement()){//if patient has pads on but not properly placed. again, replace this with a simple function. this is ugly and not reusable.
        controller->print("CHECK ELECTRODE PADS");
    }
}


void AnalysisState::stepProgress(){
    delay++;
    controller->illuminate(LIGHTUP_STANDCLEAR);
    controller->print("PLACEHOLDER MESSAGE FOR ANALYSIS");

}

void ShockState::stepProgress(){
    delay++;
    controller->illuminate(LIGHTUP_SHOCK);
    controller->print("PLACEHOLDER MESSAGE FOR SHOCK");

}

void CompressionsState::stepProgress(){
    delay++;
    controller->illuminate(LIGHTUP_COMPRESSIONS);
    controller->print("PLACEHOLDER MESSAGE FOR CPR");

}

void NominalState::stepProgress(){
    controller->print("PLACEHOLDER MESSAGE FOR AFTERCARE/NOMINAL");

}

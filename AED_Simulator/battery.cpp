#include "battery.h"

Battery::Battery(){
    batteryLevels = 100;
}



void Battery::depleteBatteryLevel(){
    batteryLevels -= 10;
    if(batteryLevels < 0){
        batteryLevels = 0;
    }
}


void Battery::chargeBattery(){
    batteryLevels += 5;
    if(batteryLevels > 100){
        batteryLevels = 100;
    }
}

int Battery::getBatteryLevels(){
    return batteryLevels;
}

Battery::~Battery(){

}

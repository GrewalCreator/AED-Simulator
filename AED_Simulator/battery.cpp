#include "battery.h"

Battery::Battery(){
    batteryLevels = 100;
}



void Battery::depleteBatteryLevel(){
    batteryLevels -= 10;
}


void Battery::chargeBattery(){
    batteryLevels += 5;
}

int Battery::getBatteryLevels(){
    return batteryLevels;
}
Battery::~Battery(){

}

#include "heartrategenerator.h"
#include <cmath>
#include <time.h>
#include <random>
#define FREQ_COEFF 7

HeartRateGenerator::HeartRateGenerator(){

}

void HeartRateGenerator::updateHeartRate(double newHeartRate) {
    generateHeartRateValues(newHeartRate);
}



const vector<double>& HeartRateGenerator::getYValues() const {
    return yValues;
}


void HeartRateGenerator::generateHeartRateValues(double heartRate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10000);

    yValues.clear();

    if((heartRate > MAX_NOMINAL_BPM) && (heartRate <200)){
        const double A1 = 1.2;
        const double A3 = 1.2;
        const double B1 = 1.8;
        const double B3 = 1.8;
        const double frequencyQ = FREQ_COEFF * 0.9 * (heartRate / 60.0);
        const double frequencyS = FREQ_COEFF * 2.7 * (heartRate / 60.0);
        const double timeInterval = 1.0 / 100.0;
        for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
            double y = 0.3*((A1 * cos(frequencyQ * t) + (B1 * sin(frequencyQ * t)) + (A3 * cos(frequencyS * t)+ B3 * sin(frequencyS * t)) ) );
            yValues.push_back(y);
        }
    }
    else if(heartRate > 200){
        double randMod = 1+ (double(dist(gen)))/10000;
        double stretchMod = (double(dist(gen)) - 5000)/10000;
        double ampMod = (double(dist(gen)))/10000;
        const double A1 = ampMod * 1.2;
        const double A2 = 0.9;
        const double A3 = 0.6;
        const double B1 = ampMod * 1.8;
        const double B2 = 0.8;
        const double B3 = 0.4;
        const double frequencyQ = stretchMod * FREQ_COEFF * 1.8 * (heartRate / 60.0);
        const double frequencyR = randMod * FREQ_COEFF * 1.5 * (heartRate / 60.0);
        const double frequencyS = FREQ_COEFF * 1.2 * (heartRate / 60.0);
        const double timeInterval = 1.0 / 100.0;
        for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
            double y = 0.3*((A1 * cos(frequencyQ * t) + (B1 * sin(frequencyQ * t)) + (A2 * cos(frequencyR * t) + B2 * sin(frequencyR * t)) + (A3 * cos(frequencyS * t)+ B3 * sin(frequencyS * t)) ) );
            yValues.push_back(y);
        }
    }
    else if((heartRate < MAX_NOMINAL_BPM)&&(heartRate > MIN_NOMINAL_BPM)){
        const double A1 = 1.2;
        const double A2 = 0.9;
        const double A3 = 1.2;
        const double B1 = 1.8;
        const double B2 = 0.8;
        const double B3 = 1.8;
        const double frequencyQ = FREQ_COEFF * 1.8 * (heartRate / 60.0);
        const double frequencyR = FREQ_COEFF * 1.5 * (heartRate / 60.0);
        const double frequencyS = FREQ_COEFF * 1.2 * (heartRate / 60.0);
        const double timeInterval = 1.0 / 100.0;
        for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
            double y = 0.2*((A1 * cos(frequencyQ * t) + (B1 * sin(frequencyQ * t)) + (A2 * cos(frequencyR * t) + B2 * sin(frequencyR * t)) + (A3 * cos(frequencyS * t)+ B3 * sin(frequencyS * t)) ) );
            yValues.push_back(y);
        }
    }
    else{
        const double A1 = 1.2;
        const double B3 = 0.4;
        const double frequencyQ = FREQ_COEFF * 1.8 * (heartRate / 60.0);
        const double timeInterval = 1.0 / 100.0;
        for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
            double y = 0.3*(A1 * cos(frequencyQ * t) + + B3 * sin(frequencyQ * t));
            yValues.push_back(y);
        }
    }


    for (auto& i : yValues) {
        double randval = (double(dist(gen))-5000)/30000;
        qDebug()<<randval;
        i += randval;
    }
}

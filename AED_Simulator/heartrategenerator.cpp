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

/*
Sequential Estimation of the Sum of Sinusoidal Model Parameters
https://home.iitk.ac.in/~kundu/paper125.pdf

The parameters of the sinusoidal functions were derived from this paper.

The type of generation changes based on what heart rate region the patient is in.
above 200: VF, signal's frequency and amplitude vary greatly
between 150 and 200: signal is rapid but consistent
between 60 and 150: signal is steady and consistent
below 60: signal is weak and smooth.
*/
void HeartRateGenerator::generateHeartRateValues(double heartRate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(1, 10000);

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
        double randMod = 1+ ((dist(gen)))/10000;
        double stretchMod = ((dist(gen)) - 5000)/10000;
        double ampMod = ((dist(gen)))/10000;
        const double A1 = ampMod * 1.2;
        const double A2 = 0.9;
        const double A3 = ampMod * 0.6;
        const double B1 = ampMod * 1.8;
        const double B2 = 0.8;
        const double B3 = ampMod * 0.4;
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
        double randval = ((dist(gen))-5000)/50000;

        i += randval;
    }
}

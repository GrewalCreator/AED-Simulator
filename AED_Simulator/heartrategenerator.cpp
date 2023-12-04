#include "heartrategenerator.h"
#include <cmath>

HeartRateGenerator::HeartRateGenerator(){

}

void HeartRateGenerator::updateHeartRate(double newHeartRate) {
    generateHeartRateValues(newHeartRate);
}



const vector<double>& HeartRateGenerator::getYValues() const {
    return yValues;
}


void HeartRateGenerator::generateHeartRateValues(double heartRate) {

    yValues.clear();

    const double amplitude = 1.0;
    const double frequency = heartRate / 60.0;
    const double timeInterval = 1.0 / 100.0;

    for (double t = 0; t <= 2 * M_PI; t += timeInterval) {

        double y = amplitude * cos(frequency * t);


        yValues.push_back(y);
    }
}

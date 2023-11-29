#include "heartrategenerator.h"
#include <cmath>

HeartRateGenerator::HeartRateGenerator(){

}

void HeartRateGenerator::updateHeartRate(double newHeartRate) {
    generateHeartRateValues(newHeartRate);
}

const vector<double>& HeartRateGenerator::getXValues() const {
        return xValues;
    }

const vector<double>& HeartRateGenerator::getYValues() const {
    return yValues;
}


void HeartRateGenerator::generateHeartRateValues(double heartRate) {
    xValues.clear();
    yValues.clear();

    const double amplitude = 1.0;
    const double frequency = heartRate / 60.0;
    const double timeInterval = 1.0 / 100.0;

    for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
        double x = amplitude * sin(frequency * t);
        double y = amplitude * cos(frequency * t);

        xValues.push_back(x);
        yValues.push_back(y);
        qDebug() << "X: " << x << " Y: " << y << Qt::endl;
    }
}

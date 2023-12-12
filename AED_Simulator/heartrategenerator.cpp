#include "heartrategenerator.h"

// Constants for frequency coefficient and heart rate boundaries
#define FREQ_COEFF 7


HeartRateGenerator::HeartRateGenerator() {}

void HeartRateGenerator::updateHeartRate(double newHeartRate){
    generateHeartRateValues(newHeartRate);
}

const std::vector<double>& HeartRateGenerator::getYValues() const {
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
void HeartRateGenerator::generateHeartRateValues(double heartRate){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(1, 10000);

    yValues.clear();

    double A1, A2, A3, B1, B2, B3;
    double frequencyQ, frequencyR, frequencyS;

    if (heartRate > MAX_NOMINAL_BPM && heartRate < 200) {
        A1 = 1.2;
        A2 = 0.0;
        A3 = 1.2;
        B1 = 1.8;
        B2 = 0.0;
        B3 = 1.8,
        frequencyQ = FREQ_COEFF * 0.9 * (heartRate / 60.0);
        frequencyR = FREQ_COEFF * 2.7 * (heartRate / 60.0);
        frequencyS = FREQ_COEFF * 2.7 * (heartRate / 60.0);
    } else if (heartRate > 200) {
        double randMod = 1 + ((dist(gen))) / 10000;
        double stretchMod = ((dist(gen)) - 5000) / 10000;
        double ampMod = (dist(gen)) / 10000;

        A1 = ampMod * 1.2;
        A2 = 0.9;
        A3 = ampMod * 0.6;
        B1 = ampMod * 1.8;
        B2 = 0.8;
        B3 = ampMod * 0.4;
        frequencyQ = stretchMod * FREQ_COEFF * 1.8 * (heartRate / 60.0);
        frequencyR = randMod * FREQ_COEFF * 1.5 * (heartRate / 60.0);
        frequencyS = FREQ_COEFF * 1.2 * (heartRate / 60.0);

    } else if (heartRate < MAX_NOMINAL_BPM && heartRate > MIN_NOMINAL_BPM) {
        A1 = 1.2;
        A2 = 0.9;
        A3 = 1.2;
        B1 = 1.8;
        B2 = 0.8;
        B3 = 1.8;
        frequencyQ = FREQ_COEFF * 1.8 * (heartRate / 60.0);
        frequencyR = FREQ_COEFF * 1.5 * (heartRate / 60.0);
        frequencyS = FREQ_COEFF * 1.2 * (heartRate / 60.0);
    } else {
        A1 = 1.2;
        A2 = 0.0;
        A3 = 0.0;
        B1 = 0.0;
        B2 = 0.0;
        B3 = 0.4;
        frequencyQ = FREQ_COEFF * 1.8 * (heartRate / 60.0);
        frequencyR = 0.0;
        frequencyS = 0.0;
    }

    const double timeInterval = 1.0 / 100.0;
    for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
        double y = 0.0;
        y += A1 * cos(frequencyQ * t) + B1 * sin(frequencyQ * t);
        y += A2 * cos(frequencyR * t) + B2 * sin(frequencyR * t);
        y += A3 * cos(frequencyS * t) + B3 * sin(frequencyS * t);
        yValues.push_back(0.3 * y);
    }

    for (auto& i : yValues) {
        double randval = ((dist(gen)) - 5000) / 50000;
        i += randval;
    }
}

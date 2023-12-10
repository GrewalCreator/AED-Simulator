#include "heartrategenerator.h"

// Constants for frequency coefficient and heart rate boundaries
#define FREQ_COEFF 7


struct HeartRateParameters {
    double A1, A2, A3, B1, B2, B3;
    double frequencyQ, frequencyR, frequencyS;
};

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
    HeartRateParameters params;

    if (heartRate > MAX_NOMINAL_BPM && heartRate < 200) {
        params = {1.2, 0.0, 1.2, 1.8, 0.0, 1.8,
                  FREQ_COEFF * 0.9 * (heartRate / 60.0),
                  FREQ_COEFF * 2.7 * (heartRate / 60.0),
                  FREQ_COEFF * 2.7 * (heartRate / 60.0)};
    } else if (heartRate > 200) {
        double randMod = 1 + ((dist(gen))) / 10000;
        double stretchMod = ((dist(gen)) - 5000) / 10000;
        double ampMod = (dist(gen)) / 10000;

        params = {ampMod * 1.2, 0.9, ampMod * 0.6,
                  ampMod * 1.8, 0.8, ampMod * 0.4,
                  stretchMod * FREQ_COEFF * 1.8 * (heartRate / 60.0),
                  randMod * FREQ_COEFF * 1.5 * (heartRate / 60.0),
                  FREQ_COEFF * 1.2 * (heartRate / 60.0)};
    } else if (heartRate < MAX_NOMINAL_BPM && heartRate > MIN_NOMINAL_BPM) {
        params = {1.2, 0.9, 1.2, 1.8, 0.8, 1.8,
                  FREQ_COEFF * 1.8 * (heartRate / 60.0),
                  FREQ_COEFF * 1.5 * (heartRate / 60.0),
                  FREQ_COEFF * 1.2 * (heartRate / 60.0)};
    } else {
        params = {1.2, 0.0, 0.0, 0.0, 0.0, 0.4,
                  FREQ_COEFF * 1.8 * (heartRate / 60.0),
                  0.0, 0.0};
    }

    const double timeInterval = 1.0 / 100.0;
    for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
        double y = 0.0;
        y += params.A1 * cos(params.frequencyQ * t) + params.B1 * sin(params.frequencyQ * t);
        y += params.A2 * cos(params.frequencyR * t) + params.B2 * sin(params.frequencyR * t);
        y += params.A3 * cos(params.frequencyS * t) + params.B3 * sin(params.frequencyS * t);
        yValues.push_back(0.3 * y);
    }

    for (auto& i : yValues) {
        double randval = ((dist(gen)) - 5000) / 50000;
        i += randval;
    }
}

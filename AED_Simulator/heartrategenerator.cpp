#include "heartrategenerator.h"

// Constants for frequency coefficient and heart rate boundaries
#define FREQ_COEFF 7


struct HeartRateParameters {
    double A1, A2, A3, B1, B2, B3;
    double frequencyQ, frequencyR, frequencyS;
};

HeartRateGenerator::HeartRateGenerator() {
a0 = -0.06553077059777584;
aparams = {31850.25401998958, -7436.722909257774, 73802.12265796811, 177350.4401527944, 48082.04984059936,
        -231216.1551518796, -299506.30704903544, -86630.47420328006, 114309.13572902745, 108097.34168345772,
        16049.315781216428, -362.3393875395978, 46179.08488221256, 77601.21532208622, 85757.13456280711,
        63679.12627420872, -43418.82673364617, -186919.3653670645, -169863.70694551966, 48267.94673609894,
        188800.04994674659, 38131.107980292734, -177246.82370742393, -132282.49724539145, 98112.58465099621,
        193444.64789201564, 88408.3133090747, -31016.848142799827, -67630.2870483687, -71903.07639163591,
        -61076.10170714717, -10281.72461706547, 44288.38375704314, 47221.92009656568, 10942.563739066876,
        -12678.642782759322, -10498.740700751347, -1743.5653387034176, 926.8615299673058, 410.6376504193072};
bparams = {180459.3858365228, 263243.9235556828, -56823.16095950832, -317800.90164631983, -232589.13936779948, -8871.378506436853, 103377.58531290703, 121977.33610104323, 115967.3362619044, 63078.991588167686, -9396.075793614882, -4708.816458420512, 62665.09646791327, 45546.56268126789, -97181.30488365835, -190839.97395634546, -97461.69292171177, 59332.16100569218, 86003.00710538565, 20207.524291700425, 5385.885899854501, 20646.533821980996, -13895.103464915188, -16832.40675690143, 83716.75010801111, 131311.72683255438, -10871.106205445443, -183601.42782187846, -156036.83194863398, 16445.68218720273, 114591.64036684879, 73555.02784449322, 2913.1818460287436, -21148.379327454502, -14743.207872586645, -7608.189851996478, -2897.469844899731, 1008.3779033244973, 1860.6610859024668, 756.2186581587371};
}

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
        const double timeInterval = 1.0 / 100.0;
        for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
            double y = 0.0;
            y += params.A1 * cos(params.frequencyQ * t) + params.B1 * sin(params.frequencyQ * t);
            y += params.A2 * cos(params.frequencyR * t) + params.B2 * sin(params.frequencyR * t);
            y += params.A3 * cos(params.frequencyS * t) + params.B3 * sin(params.frequencyS * t);
            yValues.push_back(0.3 * y);
        }
    } else if (heartRate > 200) {
        double randMod = 1 + ((dist(gen))) / 10000;
        double stretchMod = ((dist(gen)) - 5000) / 10000;
        double ampMod = (dist(gen)) / 10000;

        params = {ampMod * 1.2, 0.9, ampMod * 0.6,
                  ampMod * 1.8, 0.8, ampMod * 0.4,
                  stretchMod * FREQ_COEFF * 1.8 * (heartRate / 60.0),
                  randMod * FREQ_COEFF * 1.5 * (heartRate / 60.0),
                  FREQ_COEFF * 1.2 * (heartRate / 60.0)};
        const double timeInterval = 1.0 / 100.0;
        for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
            double y = 0.0;
            y += params.A1 * cos(params.frequencyQ * t) + params.B1 * sin(params.frequencyQ * t);
            y += params.A2 * cos(params.frequencyR * t) + params.B2 * sin(params.frequencyR * t);
            y += params.A3 * cos(params.frequencyS * t) + params.B3 * sin(params.frequencyS * t);
            yValues.push_back(0.3 * y);
        }
    } else if (heartRate < MAX_NOMINAL_BPM && heartRate > MIN_NOMINAL_BPM) {//normal
        params = {1.2, 0.9, 1.2, 1.8, 0.8, 1.8,
                  (heartRate / 60.0),
                  FREQ_COEFF * 1.5 * (heartRate / 60.0),
                  FREQ_COEFF * 1.2 * (heartRate / 60.0)};
        const double timeInterval = 1.0 / 100.0;
        for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
            double y = a0/2;
            for(unsigned long i = 0; i< aparams.size(); i++){
                int harmonic = 2*i + 1;
                y += aparams[i] * cos(params.frequencyQ* harmonic * t) + bparams[i] * sin(params.frequencyQ* harmonic* t);
            }
            yValues.push_back(copysign(pow((fabs(y)*.000001),.5),y));
        }
        for (auto& i : yValues) {
            double randval = ((dist(gen)) - 5000) / 500000;
            i += randval;
        }
        return;
    } else {
        params = {1.2, 0.0, 0.0, 0.0, 0.0, 0.4,
                  FREQ_COEFF * 1.8 * (heartRate / 60.0),
                  0.0, 0.0};
        const double timeInterval = 1.0 / 100.0;
        for (double t = 0; t <= 2 * M_PI; t += timeInterval) {
            double y = 0.0;
            y += params.A1 * cos(params.frequencyQ * t) + params.B1 * sin(params.frequencyQ * t);
            y += params.A2 * cos(params.frequencyR * t) + params.B2 * sin(params.frequencyR * t);
            y += params.A3 * cos(params.frequencyS * t) + params.B3 * sin(params.frequencyS * t);
            yValues.push_back(0.3 * y);
        }
    }



    for (auto& i : yValues) {
        double randval = ((dist(gen)) - 5000) / 50000;
        i += randval;
    }
}

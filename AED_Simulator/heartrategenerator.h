#ifndef HEARTRATEGENERATOR_H
#define HEARTRATEGENERATOR_H

#include "defs.h"
#include <QObject>
#include <QThread>

#include <vector>
#include <cmath>
#include <random>

class HeartRateGenerator {


public:
    explicit HeartRateGenerator();

    void updateHeartRate(double newHeartRate);


    const vector<double>& getYValues() const;


private:
    void generateHeartRateValues(double heartRate);
    vector<double> xValues;
    vector<double> yValues;



};

#endif // HEARTRATEGENERATOR_H

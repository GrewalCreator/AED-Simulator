#ifndef DEFS_H
#define DEFS_H

#include <string>
#include <QDebug>

#define MIN_NOMINAL_BPM 60
#define MAX_NOMINAL_BPM 150

#define MAX_BPM 250
#define MIN_BPM 0

#define MAX_NUMBER_COMPRESSION 120

#define IMAGE_PATH "../AED_Simulator/Resources/images/"
#define LOG_PATH "../AED_Simulator/Resources/logs/"
#define AUDIO_PATH "../AED_Simulator/Resources/audio/"
#define STYLESHEET_PATH "../AED_Simulator/Resources/stylesheets/"

#define CHILD_AMPS 50
#define ADULT_AMPS 100

using std::string;
using std::vector;
using std::srand;
using std::time;
using std::rand;

#endif // DEFS_H

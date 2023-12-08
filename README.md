# AED Pulse Simulator


### Build:
    Execute the setup script 'setup.sh' with "sudo ./setup.sh"
    
    
### Introduction 

Our goal for the COMP3004 Final Project involved creating a practical simulation mirroring a genuine Automated External Defibrillator [AED]. This simulation comprehensively replicates the functionalities of the AED, utilizing concurrency to deliver real-time updates to the user.

AED Simulator leverages the QT Creator Development Platform to design an easy-to-use UI to represent the physical AED device, as well as a seperate window designed to containing testing features of the program. The AED detects the users live Heart-Rate using sensors on the Pads. As a result heart rate will not be updated [Graph & LCD] until the pads have been placed.


// OWEN: Talk about you implementation of the AEDState
Using a AEDState class, the simulation can transition between states whilst modifying any variables, allowing for a smooth transition between states.

// GURTEJ: MediaPlayer implementation. KIROS: Add any other audios included if I missed any you added 
Further more, we were unable to utilize the QMediaPlayer Class for this project, so instead we use an OS based Audio Player package called the Alsa Project. The alsa-utils package allows us to play audio files through the operating systems shell. Currently we provide audios for Power On, Power Off, Shocking Charge, Stand Clear Instructions & Delivery Sound Effects.

// GURTEJ: Logger Implementation
To ease the debug process, we developed a system of logging function calls and user actions 


// GURTEJ & OWEN: Talk about HeartRateGenerator


### Description:
    The AED Plus Simulator is a software application designed to simulate the core functionality of an Automated External Defibrillator
    (AED) Plus device. This simulation allows users to practice and enhance their skills in responding to life-threatening cardiac arrh-
    ythmias, such as ventricular fibrillation and ventricular tachycardia, in a virtual environment

### List of sources:
    AED_Simulator.pro (Qt Creator project file)
    aed.cpp, aed.h
    aedcontroller.cpp, aedcontroller.h
    aedstate.cpp, aedstate.h
    aedwindow.cpp, aedwindow.h
    AudioTypes.h
    battery.cpp, battery.h
    defs.h
    electrodepads.cpp, electrodepads.h
    heartrategenerator.cpp, heartrategenerator.h
    logger.cpp, logger.h
    main.cpp
    mediaplayer.cpp, mediaplayer.h
    patient.cpp, patient.h
    PatientType.h
    ProcessSteps.h
    processtracker.cpp, processtracker.h
    SignalType.h
    testcontroller.cpp, testcontroller.h
    testwindow.cpp, testwindow.h

# Build and Test
1.	Execute the setup script 'setup.sh' with "sudo ./setup.sh" BEFORE running the program. Please ensure this step is done or you will recieve error messages and error audio throught the simulation. For information on the package we request be installed, please refer to the links provided below.

# Contributors
	- Gurtej Grewal [101221758], gurtejgrewal@cmail.carleton.ca

    	- Boris Zugic, boriszugic123@gmail.com

    	- Owen Lucas [101226679], OWENLUCAS3@cmail.carleton.ca

	-  Libeamlak Kiros, LIBEAMLAKKIROS@cmail.carleton.ca


### Issues/Limitations:
    No known issues or limitations at this time.

# Alsa Project Reference Links
1. https://github.com/alsa-project/alsa-utils
2. https://www.alsa-project.org/wiki/Main_Page

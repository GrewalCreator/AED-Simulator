# AED Pulse Simulator


### Build:
    Execute the setup script 'setup.sh' with "sudo ./setup.sh"
    
    
### Introduction 

Our goal for the COMP3004 Final Project involved creating a practical simulation mirroring a genuine Automated External Defibrillator [AED]. This simulation comprehensively replicates the functionalities of the AED, utilizing concurrency to deliver real-time updates to the user.

AED Simulator leverages the QT Creator Development Platform to design an easy-to-use UI to represent the physical AED device, as well as a seperate window designed to containing testing features of the program. The AED detects the users live Heart-Rate using sensors on the Pads. As a result heart rate will not be updated [Graph & LCD] until the pads have been placed.


## Important Note Regarding Sequence Diagrams
1. Multiple sequence diagrams may be in the same PNG image, within a sequence diagram frame followed by their title. This title is used in reference frames to avoid duplicate diagrams and prevent crowding.
2. Our safety for the preliminary checks is done in the thread loop. So in the run() function of the Tmain sequence diagram, you will see a function 'safetyChecks()' being run. This contains the checks and is not the responsibility of the states to return any error flags.
3. Please read any notes found in the diagrams as they will explain details omitted or provide clarification where needed.
4. Alt frames have been used to show cricual details in different possible paths which could not be ommited
5. The Threadloop sequence diagram outlines the main flow of the states which controls the programs progression. Other functionalities such as button clicks are mainly used to set variables, which will aid the states decision making. This concurrency was outlined in the diagram sequencally to be as accurate as possible.

## Individual Contributions

### Gurtej Grewal
	Throughout this project, I took on multiple responsibilities, starting with the management of Azure DevOps and the breakdown of the project, enabling me to assign tasks efficiently to my fellow team members. This particular structure sped up the development of our program to be a highly functional simulation, surpassing all required implementations and allowing for the incorporation of additional features.

	In addition to overseeing project management, I reviewed all pull requests from my group members before merging them with the main program. This approach to source control prevented issues such as duplicate code, accidental overwrites of other members' implementations, and potential errors stemming from any miscommunication.

	Furthermore, I hosted regular weekly meetings with group members on Discord. These meetings served to discuss upcoming tasks, next steps in the project, and to address any questions and/or concerns. From a technical perspective, my responsibilities included creating the Logger Class. Its main function was to log statements into a generated .log file located in the Resources > Log folder. This logging system tracks our program's progression and expedited the debugging process. The .log files were excluded from git tracking by utilizing .gitignore to prevent individual program cluttering, serving exclusively for debugging purposes.

	Moreover, I implemented the MediaPlayer. Although we understood that a text version of the speaker met the project requirements, I believed there was room for improvement. As a result, I found the Alsa Project, a package enabling the playback of audio files from the shell. This acted as a replacement for QT's built-in mediaplayer. The MediaPlayer object was used in Power On, Power Off, Stand Clear, Charging & Shock audios, enhancing the program's realistic feel for the AED.

	Amongst the classes, I was responsible for the implementation of AED, Patient, Battery, Electrode Pads, HeartRate Generator [which was later improved by Owen to add noise], Process Tracker, TestController & TestWindow. Additionally, I made minor refinements to Owen's UI, improving the usability and presentation of the buttons, incorporating the dark theme into the test window, and refining the AEDWindow styling to ensure a smooth look and feel with the UI elements and color shading. Thank you to Owen & Boris for their contributions to the UI styling, which I later migrated to a separate .qss file located in the Resources > Stylesheets folder.
	
	Finally, from a documentation standpoint, I was responsible for creating the sequence diagrams to detail all use-cases as well as recording the demo video. Please note the important message regarding the sequence diagrams above this documentation.
	
	
### Owen Lucas



### Boris Zugic



### Libeamlak Kiros




### Description:
    The AED Pulse Simulator is a software application designed to simulate the core functionality of an Automated External Defibrillator
    (AED) Pulse device. This simulation allows users to practice and enhance their skills in responding to life-threatening cardiac arrhythmias,
    such as ventricular fibrillation, ventricular tachycardia and PEA in a virtual environment

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

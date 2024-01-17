# AED Pulse Simulator


# Build and Test

1. Execute Program with the setup script 'setup.sh'. This should already be an executable but incase of an issue please convert the file to an executable using 'sudo chmod +x ./setup.sh'. This file will install the required packages to play audio & run the program.
2. If you encounter any errors, you may install the package seperatly using [sudo apt update] & [sudo apt install alsa-utils], and then run the program in QT.
3. Please note this alsa-utils package is required for the audio. More information regarding the package can be found below.
4. If you run into any other issues, attempt to run the unixConversion Script. If this does not resolve your issue, please contact us and we will provide an immediate fix.
    
### Introduction 

Our goal for the COMP3004 Final Project involved creating a practical simulation mirroring a genuine Automated External Defibrillator [AED]. This simulation comprehensively replicates the functionalities of the AED, utilizing concurrency to deliver real-time updates to the user.

AED Simulator leverages the QT Creator Development Platform to design an easy-to-use UI to represent the physical AED device, as well as a seperate window designed to containing testing features of the program. The AED detects the users live Heart-Rate using sensors on the Pads. As a result heart rate will not be updated [Graph & LCD] until the pads have been placed.


## Important Note Regarding Sequence Diagrams
1. Multiple sequence diagrams may be in the same PNG image, within a sequence diagram frame followed by their title. This title is used in reference frames to avoid duplicate diagrams and prevent crowding.

2. Our safety for the preliminary checks is done in the thread loop. So in the run() function of the Tmain sequence diagram, you will see a function 'safetyChecks()' being run. This contains the checks and is not the responsibility of the states to return any error flags.

3. Please read any notes found in the diagrams as they will explain details omitted or provide clarification where needed.

4. Alt frames have been used to show cricual details in different possible paths which could not be ommited

5. The Threadloop sequence diagram outlines the main flow of the states which controls the programs progression. Other functionalities such as button clicks are mainly used to set variables, which will aid the states decision making. This concurrency was outlined in the diagram sequencally to be as accurate as possible.

## Design decisions
1. The AEDController ties every element of the program together: it progresses the simulation with each loop, processing input from the user and updating the UI with its current state constantly. It is a mediator pattern, which manages communication between classes like AED, Patient and ProcessTracker and the UI. We have a lot of classes, so a mediator pattern made such a process seamless.
It is greatly supported by the AEDState class. 

2. The AEDState class, with its 6 concrete implementations is a State pattern, which takes on a majority of AEDController's logic, deciding when to move to the next step, when to shock, when to wait and so on. This separates the logic part of AEDController from the update and communicate part, avoiding a potential god object. It also made the state logic modular and much easier to work on as a team, not to mention the modularity enabled us to write more complex behaviour. 

3. If you want to take a bit of a stretch, the AEDWindow is a bit of a facade from the point of view of the controllers: All they have to do is send a signal, with an enum, and either a string or bool. This signal allows for every possible UI update on the AEDWindow, and makes it easy to use for AEDController without having to know what UI element is what. AEDController simply sends StaticSignal(LIGHTUP_CHECK_OK,true) and makes the AEDWindow go through 6 QLabel elements and 6 label assets, all to set a single light to on, ensuring no other light is on. This also goes for printing a message to the console, updating the battery, and updating the heart rate LCD.


## Individual Contributions

### Gurtej Grewal

Throughout this project, I took on multiple responsibilities, starting with the management of Azure DevOps 
and the breakdown of the project, enabling me to assign tasks efficiently to my fellow team members. 
This particular structure sped up the development of our program to be a highly functional simulation, 
surpassing all required implementations and allowing for the incorporation of additional features.

In addition to overseeing project management, I reviewed all pull requests from my group members before 
merging them with the main program. This approach to source control prevented issues such as duplicate code,
accidental overwrites of other members' implementations, and potential errors stemming from any miscommunication.

Furthermore, I hosted regular weekly meetings with group members on Discord. These meetings served to discuss 
upcoming tasks, next steps in the project, and to address any questions and/or concerns. From a technical perspective, 
my responsibilities included creating the Logger Class. Its main function was to log statements into a generated .log 
file located in the Resources > Log folder. This logging system tracks our program's progression and expedited the debugging process.
The .log files were excluded from git tracking by utilizing .gitignore to prevent individual program 
cluttering, serving exclusively for debugging purposes.

Moreover, I implemented the MediaPlayer. Although we understood that a text version of the speaker met the project requirements, I believed there was room for improvement. 
As a result, I found the Alsa Project, a package enabling the playback of audio files from the shell. This acted as a replacement for QT's built-in mediaplayer. 
The MediaPlayer object was used in Power On, Power Off, Stand Clear, Charging & Shock audios, enhancing the program's realistic feel for the AED.

Amongst the classes, I was responsible for the implementation of AED, Patient, Battery, Electrode Pads, HeartRate Generator [which was later improved by Owen to add noise], 
Process Tracker, TestController & TestWindow. For the AED Shock Functionality, with the help of Owen we figured out the best way to apply a different shock strength to patients with the incorrect pad, adding to the realism of our design. Additionally, I made minor refinements to Owen's UI, improving the usability and presentation of the buttons, incorporating the dark theme into the test 	window, and refining the AEDWindow styling to ensure a smooth look and feel with the UI elements and color shading. Thank you to Owen & Boris for their contributions to the UI styling, which I later migrated to a separate .qss file located in the Resources > Stylesheets folder.

Finally, from a documentation standpoint, I was responsible for creating the sequence diagrams to detail all use-cases as well as recording the demo video. Please note the important message 		regarding the sequence diagrams above this documentation.
	
	
### Owen Lucas
    In the first week of the project, I made a rough draft of the use cases, state diagram, and class diagram. One of first things our team did after reading the requirements was come together to figure out the structure of the program, and I documented and expanded on it by relating the admin guide and what our team came up with into the use cases, which later found its way into the final documents I made: the state diagram, traceability matrix, and the use case summary/diagram (made using Overleaf, draw.io and Mermaid). I also edited Libeamlak's class diagram a bit to be more readable and UML-compliant.

    The second week was spent creating the foundation of our program's UI: I ripped assets from the Zoll AED-Plus using GIMP, then figured out how to display the assets on QT's UI. From there, I made sure to make reusable and reliable functions to avoid future image-related debugging pains. Boris improved on my design by adding styling to the elements, while Gurtej made it so the styling was no longer hardcoded into the program.
    
    Between the second and third week, I added connectivity between AEDController and AEDWindow, so that AEDController had the ability to light up AEDWindow's indicator lights.

    At this point, I had also handled the concurrency part of our program, turning AEDController into an object that ran in a different thread than our main window. I also modularized part of AEDController into AEDTransmitter, which was created to avoid multiple inheritance due to the threaded implementation.

    Week 3 was where I took on a large part of the program's logic: I essentially made AEDController the heart of the program, ticking every .2 seconds to move to the next operation. Initially, The program had a processtracker, implemented by Gurtej to keep track of the AED's state. So naturally, I made a single function to handle every state (this would not end well). This function would be responsible for the progression and logic from powering on all the way to CPR. As Boris, Libeamlak and I added onto the function, we would constantly run into merge conflicts, so I refactored the entire function into a state pattern with 6 different states. This would ultimately be worth it, as we encountered less merge conflicts when working on different states. This also allowed for more complex behaviour of our AED; things like the real-time compression feedback, operational safety, shock safety, and message delays were some of the things I worked on with my teammates that this new state pattern allowed for.

    I also worked with Gurtej to come up with a way to make the patient class stabilize and destabilize depending on the current heart rate with each tick, giving it a physics simulation-like quality. I would also later go on to improve on Gurtej's wave generator, combining harmonic sine waves, noise, and randomness to approximate the ECG signatures of vtach, vfib, PEA and a normal heart signal.


### Boris Zugic
    
    New Features:

    Dynamic Patient Selection:
    Implemented a feature allowing users to switch between adult and child patient modes seamlessly during runtime, providing greater flexibility in handling different scenarios.
    
    AED Power-On Logic:
    Developed a functionality ensuring that upon powering on the AED, it follows the correct sequence based on whether the pads are attached and correctly placed. This enhances the application's usability and adherence to proper AED operation.
    
    Post-Shock BPM Adjustment:
    Created a feature where the BPM displayed on the LCD decreases after the shock button is pressed, adding realism and a dynamic element to the application.
    
    Real-Time BPM Analysis:
    Implemented a real-time BPM analysis feature where the state of the AED is updated in parallel with the numerical value of the slider. This enhances the accuracy and responsiveness of the application.
    
    Pads-Related Features:
    Designed functionalities ensuring that the BPM is not displayed unless pads are attached to the patient, and implemented a 'place pads' feature for proper AED setup.
    
    Visual Styling:
    Styled the BPM slider to indicate low, nominal, and high BPM using colors. Also, improved the styling of the cursor used to move the slider, enhancing the application's visual appeal.

    LCD Display Enhancements:
    Integrated a feature where the BPM is displayed on the LCD based on the numerical value of the slider, improving the user interface and providing accurate feedback.
    
    Window Interaction:
    Ensured that both application windows close simultaneously, enhancing user experience and maintaining consistency in the application's behavior.

    
    Bug Fixes:
    
    Program Flow Corrections:
    Resolved a bug where pressing buttons before powering on the AED led to incorrect program flow, ensuring a more reliable sequence of operations.

    Preventing Display Issues:
    Fixed bugs related to premature display of the graph and BPM on the LCD before powering on the AED and placing pads on patient, providing a smoother user experience.

    Pad Placement and Shock Logic:
    Addressed issues preventing pads from being placed at any point and ensuring correct shock light behavior during transitions between BPM states.

    User Interface Fixes:
    Resolved bugs related to display overwriting, incorrect background color, and fatal errors when showing the test window, enhancing the overall application stability and aesthetics.

    
    Additional Contributions:

    Documentation and ReadMe:
    Worked on the ReadMe file, providing clear instructions for users and developers. 

    Collaboration and Meetings:
    Actively participated and held meetings, collaborated with team members to resolve issues, and provided assistance with feature development.

    Code Refactoring:
    Engaged in code refactoring activities to improve code quality, readability, and adherence to best practices.

    Sequence Diagrams:
    Created a rough draft of sequence diagrams, facilitating communication and understanding of the application's flow, which was presented during personal demo.


### Libeamlak Kiros

    Incorporated CheckPatientState functionality into the system. This strategic integration improves the system's overall performance and 
    responsiveness by introducing two essential features that contribute to monitoring and aiding the patient. The CheckPatientState function 
    allows for real-time assessment of the patient's condition, enabling the system to dynamically respond to any changes in their health status.

    Incorporated GetHelpState functionality into the system. The GetHelpState feature is like a really important tool for getting help quickly, 
    making sure the system can handle emergencies well.

    I successfully implemented the compression feature into the system. Additionally, I ensured that the slider, LCD, and graph components undergo 
    automatic updates in synchronisation with every execution of the compression process. Integrating these two techniques ensures that the user is 
    provided with both a seamless and responsive user experience, as well as real-time visual feedback during compression. Also, the values of each 
    compression are randomly set to make the application more realistic.

    I added sounds to the system to make the AED easier for users. These sounds help people interact with the AED better by giving them sound effects 
    they can hear. Sounders like intro sound,  charging sound and shocking sound were added.

    I have generated an initial draft of the UML class diagram for the AED system. This diagram encapsulates the structural representation of the system, 
    showcasing the various classes, their attributes, and the relationships between them.

    Actively collaborating with teammates and attending meetings as needed.

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


# Contributors
	- Gurtej Grewal [101221758], gurtejgrewal@cmail.carleton.ca

    - Boris Zugic [101223924], boriszugic@cmail.carleton.ca

    - Owen Lucas [101226679], OWENLUCAS3@cmail.carleton.ca

	- Libeamlak Kiros [101228966], LIBEAMLAKKIROS@cmail.carleton.ca


### Issues/Limitations:
    No known issues or limitations at this time.

# Alsa Project Reference Links
1. https://github.com/alsa-project/alsa-utils
2. https://www.alsa-project.org/wiki/Main_Page

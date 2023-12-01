#include "aedwindow.h"
#include "ui_aedwindow.h"

AEDWindow::AEDWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AEDWindow){
    ui->setupUi(this);
    semaphore = new QSemaphore(0);
    controller = new AEDController(semaphore, this);
    controller->setProcessTracker(POWER_OFF);
    signalToString();
    initializeConnects();
    setUpVisuals();
    controlThread = new QThread();


}

void AEDWindow::setUpVisuals(){
    // Sequence of Function Calls Must Remain In Order! initImgs() relys on loadImgs()
    loadImgs();
    initImgs();
    styling();
}


void AEDWindow::signalToString(){

    uiMap[LIGHTUP_OK] = ui->ok_image;
    uiMap[LIGHTUP_COMPRESSIONS] = ui->compressions_image;
    uiMap[SET_STATUS] = ui->statusLight_image;
    uiMap[LIGHTUP_911] = ui->help_image;
    uiMap[LIGHTUP_PADS] = ui->pads_image;
    uiMap[LIGHTUP_STANDCLEAR] = ui->standclear_image;
}
void AEDWindow::styling(){
    this->setStyleSheet("QPushButton {\n\
                        border-radius: 50%;\n\
                        padding: 8px 16px;\n\
                        color: #FF0000;\n\
                        font-size: 14px;}\n\
                    QPushButton:hover {\n\
                        background-color: #FF0000;\n\
                        color: #FFFFFF;}\n\
                    QFrame#mainFrame{\n\
                        background-color: #12a32a;\n\
                        border: 2px solid #FFFFFF;\n\
                        border-radius: 10px;}\n\
                    QFrame#frame_2{\n\
                        background-color: #5ff578;\n\
                        border: 2px solid #FFFFFF;\n\
                        border-radius: 10px;}\n\
                    QLabel {\n\
                        border-radius: 9px;\n\
                        padding: 5px;\n\
                        }\n\
                    QPushButton:pressed {\n\
                        background-color: #FFFF00;}\n\
                        QProgressBar {\n\
                            border: 2px solid grey;\n\
                            border-radius: 5px;\n\
                            background-color: #5ff578;\n\
                            height: 20px;\n\
                            text-align: center;\n\
                        }\n\
                        QProgressBar::chunk {\n\
                            background-color: #ffcc00;\n\
                            width: 10px;\n\
                        }\n\
QProgressBar {\n\
border: 2px solid grey;\n\
border-radius: 5px;\n\
background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.3 red, stop:0.5 yellow, stop:0.7 #5ff578);\n\
}\n\
QProgressBar::chunk {\n\
background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 white, stop:1 white);\n\
width: 5px;\n\
margin: 0.5px;\n\
}\n"
);
}


void AEDWindow::initializeConnects(){
    // Static Signal Connections
    connect(controller->getTransmitter(), SIGNAL(staticSignal(const SignalType&, bool)), this, SLOT(receiveStaticSignal(const SignalType&, bool)));

    // Dynamic Signal Connections
    connect(controller->getTransmitter(),SIGNAL(dynamicSignal(const SignalType&, const string&)), this, SLOT(receiveDynamicSignal(const SignalType&, const string&)));

    // Power Button
    connect(ui->power_button, SIGNAL(released()), this, SLOT(togglePower()));

    // Adult Pads Button
    connect(ui->adultPads_button, SIGNAL(released()), this, SLOT(toggleAdultPads()));

    // Child Pads Button
    connect(ui->childPads_button, SIGNAL(released()), this, SLOT(toggleChildPads()));

    connect(ui->battery, SIGNAL(clicked()), this, SLOT(recharge()));

    connect(ui->shock_button, SIGNAL(clicked()), this, SLOT(shockPressed()));


}

void AEDWindow::shockPressed(){
    controller->shockPressed();
}

void AEDWindow::togglePower(){

    if(controller->getProcessTracker() != POWER_OFF){   // Power is On, Turn it Off
        controller->powerAEDOff();
        if (controlThread->isRunning()) {
            controlThread->quit();
            controlThread->wait();
        }
        disconnect(controlThread, SIGNAL(started()), controller, SLOT(run()));

        controller->getAED()->playAudio(POWER_OFF_AUDIO);
        //controller->powerAEDOff(); previous position of poweroff.
        controller->setProcessTracker(POWER_OFF);
        setPowerLight(false);
        setAllLights(false);


    }else{

        // Power is Off, Turn It On

        connect(controlThread, SIGNAL(started()), controller, SLOT(run()));
        controller->moveToThread(controlThread);
        controlThread->start();
        controller->getAED()->playAudio(POWER_ON_AUDIO);
        controller->setProcessTracker(CHECK_OK);
        bool successfulPowerOn = controller->powerAEDOn();
        setPowerLight(true);
        if(!successfulPowerOn){
            // AED NOT SAFE TO RUN, Shutting Down
            consoleOut("AED Did Not Pass Tests. Powering Off . . .");
            togglePower();
        }


    }

}

void AEDWindow::toggleAdultPads(){
    controller->placePads(ADULT);
}

void AEDWindow::toggleChildPads(){
    controller->placePads(CHILD);
}

void AEDWindow::consoleOut(const string& message){
    QString qMessage = QString::fromStdString(message);
    QMetaObject::invokeMethod(ui->instruction_console, "setPlainText", Qt::QueuedConnection, Q_ARG(QString, qMessage));
}

void AEDWindow::receiveStaticSignal(const SignalType& sig, bool state){
    if(sig == LIGHTUP_SHOCK){
        setShockLight(state);
    }
    else if(sig == POWER_INDICATOR){
        setPowerLight(state);
    }
    else{
        setOneLight(sig, state);
    }
}



void AEDWindow::receiveDynamicSignal(const SignalType& sig, const string& data){
    switch(sig){

        case BATTERY:{
            int batteryvalue = stoi(data);
            updateBattery(batteryvalue);
            break;
    }


        case PRINT:
            consoleOut(data);
            break;

        default:
            break;
    }

}

void AEDWindow::updateBattery(int value){
    ui->batteryBar->setValue(value);
}

void AEDWindow::initImgs(){//TODO: make image name == ui element name, so a simple file replace will make a quick change in ui
    ui->ok_image->setPixmap(*(imageMap["ok_image_off"]));
    ui->standclear_image->setPixmap(*(imageMap["standclear_image_off"]));
    ui->compressions_image->setPixmap(*(imageMap["compressions_image_off"]));
    ui->pads_image->setPixmap(*(imageMap["pads_image_off"]));
    ui->help_image->setPixmap(*(imageMap["help_image_off"]));

    setShockLight(false);
    setPowerLight(false);
}


void AEDWindow::loadImgs(){
    QDir directory(IMAGE_PATH);
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.png",QDir::Files);
    foreach(QString filename, images) {
        filename.resize(filename.length()-4);
        QString belongsTo = QString(filename).remove("_off").remove("_on");
        QPixmap* p = new QPixmap(IMAGE_PATH+filename);
        if(belongsTo == "compressions_image"){
            *p = p->scaled(ui->compressions_image->size());//scales pixmap to compression image
        }
        else if(belongsTo == "shock_button")
            *p = p->scaled(ui->shock_button->size());//scales pixmap to the size of shock button
        else{
            *p = p->scaled(ui->ok_image->size());//scales pixmap to the size of standard indicator
        }
        imageMap[filename] = p;
    }

}

void AEDWindow::setAllLights(bool lit){
    QString uiname;
    foreach(auto i,uiMap){
        uiname = i->objectName();
        if(!imageMap.contains(uiname+"_on") || !imageMap.contains(uiname+"_off") ){
            controller->getLogger()->log("Image For " + uiname + "' Turning " + lit  + " Was Not Found");
             continue;
        }

        if(lit){
            i->setPixmap(*(imageMap[uiname+"_on"]));
        }
        else{
            i->setPixmap(*(imageMap[uiname+"_off"]));
        }
        setShockLight(lit);
    }
}

void AEDWindow::setOneLight(const SignalType sig,bool lit){
    setAllLights(false);
    QLabel* label = uiMap[sig];


    if(lit){
        label->setPixmap(*(imageMap[label->objectName()+"_on"]));
    }
    else{
        label->setPixmap(*(imageMap[label->objectName()+ "_off"]));
    }
}

void AEDWindow::setShockLight(bool isLightOn){
    QIcon shockimg;
    //setAllLights(false);
    if(isLightOn){
        shockimg = QIcon(*imageMap["shock_button_on"]);
    }
    else
        shockimg = QIcon(*imageMap["shock_button_off"]);

    ui->shock_button->setIcon(shockimg);
    ui->shock_button->setIconSize((*imageMap["shock_button_off"]).size());
}

void AEDWindow::setPowerLight(bool isLightOn){
    QIcon powerimg;
    qDebug()<<"set to "<<isLightOn;
    //setAllLights(false);
    if(isLightOn){
        powerimg = QIcon(*imageMap["power_button_on"]);
    }
    else
        powerimg = QIcon(*imageMap["power_button_off"]);

    ui->power_button->setIcon(powerimg);
    ui->power_button->setIconSize(QSize(91,91));
}

void AEDWindow::closeEvent(QCloseEvent* event){
    qDebug()<<"in closeeevent, before emitting aboutoclose";
    emit aboutToClose();
    controller->powerAEDOff();
    //semaphore->acquire(); this was causing problems
    qDebug()<<"in closeeevent";
    QString currentThreadId = "Semaphore Acquired As Thread : " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    controller->getLogger()->log(currentThreadId);
    QWidget::closeEvent(event);
}

AEDController* AEDWindow::getController(){
    return controller;
}

AEDWindow::~AEDWindow(){
    controller->getLogger()->log("AEDWindow Destructor Called");
    delete ui;
    controller->powerAEDOff();
    if (controlThread->isRunning()) {
        controlThread->quit();
        controlThread->wait();
    }
    delete controller;
    delete controlThread;
}

void AEDWindow::recharge(){
    controller->recharge();
}
void AEDWindow::on_adultPads_button_clicked()
{

}


void AEDWindow::on_childPads_button_clicked()
{

}


#include "aedwindow.h"
#include "ui_aedwindow.h"

AEDWindow::AEDWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AEDWindow){
    ui->setupUi(this);
    semaphore = new QSemaphore(0);
    controller = new AEDController(semaphore, this);
    controlThread = new QThread();
    controller->setCurrentStep(POWER_OFF);
    signalToString();
    setUpVisuals();
    initializeConnects();
}

void AEDWindow::setUpVisuals(){
    // Sequence of Function Calls Must Remain In Order! initImgs() relys on loadImgs()
    loadImgs();
    //initImgs();
    styling();

    ui->batteryBar->setValue(0);
}


void AEDWindow::signalToString(){

    uiMap[LIGHTUP_OK] = ui->ok_image;
    uiMap[LIGHTUP_COMPRESSIONS] = ui->compressions_image;
    uiMap[LIGHTUP_911] = ui->help_image;
    uiMap[LIGHTUP_PADS] = ui->pads_image;
    uiMap[LIGHTUP_STANDCLEAR] = ui->standclear_image;
}
void AEDWindow::styling(){
    QFile styleFile(QString(STYLESHEET_PATH) + "aedWindowStyles.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    this->setStyleSheet(styleSheet);
}


void AEDWindow::initializeConnects() const{
    // Static Signal Connections
    connect(controller->getTransmitter(), SIGNAL(staticSignal(const SignalType&, bool)), this, SLOT(receiveStaticSignal(const SignalType&, bool)));

    // Dynamic Signal Connections
    connect(controller->getTransmitter(),SIGNAL(dynamicSignal(const SignalType&, const string&)), this, SLOT(receiveDynamicSignal(const SignalType&, const string&)));

    // Power Button
    connect(ui->power_button, SIGNAL(released()), this, SLOT(togglePower()));

    //Recharge Button
    connect(ui->battery, SIGNAL(clicked()), this, SLOT(recharge()));

    // Shock Button
    connect(ui->shock_button, SIGNAL(clicked()), this, SLOT(shockPressed()));




}

void AEDWindow::shockPressed() const{
    if(controller->getCurrentStep() == SHOCK){
        controller->shockPressed();
    }
}

void AEDWindow::updateSlider() const{
   controller->getTestController()->updateSlider();
}

void AEDWindow::resetUI(bool lightOnly) const{
    QCoreApplication::processEvents();
    setAllLights(false);
    if(lightOnly)return;

    setPowerLight(false);
    ui->heartRate_LCD->display(0);
    ui->instruction_console->setPlainText("");

}

void AEDWindow::togglePower() const{

    if(controller->getCurrentStep() != POWER_OFF){

        // Power is On, Turn it Off
        disconnect(controlThread, SIGNAL(started()), 0, 0);
        controller->powerAEDOff();
        if (controlThread->isRunning()) {
            controlThread->quit();
            controlThread->wait();
            controller->log("Waiting in AEDWindow::togglepower() ...");
        }
        controller->getAED()->playAudio(POWER_OFF_AUDIO);
        controller->setState(POWER_OFF);


    }else{

        // Power is Off, Turn It On
        connect(controlThread, SIGNAL(started()), controller, SLOT(run()));

        controller->moveToThread(controlThread);
        ui->batteryBar->setTextVisible(true);
        controlThread->start();
        controller->getAED()->playAudio(POWER_ON_AUDIO);
        controller->setState(POWER_ON);
        bool successfulPowerOn = controller->powerAEDOn();
        setPowerLight(true);
        if(!successfulPowerOn){
            // AED NOT SAFE TO RUN, Shutting Down
            consoleOut("AED Did Not Pass Tests. Powering Off . . .");
            togglePower();
        }



    }

}

void AEDWindow::consoleOut(const string& message) const{
    QString qMessage = QString::fromStdString(message);
    QMetaObject::invokeMethod(ui->instruction_console, "setPlainText", Qt::QueuedConnection, Q_ARG(QString, qMessage));
}

void AEDWindow::receiveStaticSignal(const SignalType& sig, bool state) const{

    switch(sig){
        case HEART_RATE:
            if (!controller->getPatient()->getHasPadsOn()){
                break;
            }

            controller->getTestController()->updateHeartRate();
            ui->heartRate_LCD->display(controller->getPatient()->getHeartRate());
            break;


        case LIGHTUP_SHOCK:
            setShockLight(state);
            break;


        case POWER_INDICATOR:
            setPowerLight(state);
            break;

        case RESET:
            resetUI(state);
            break;

        case SLIDER:
            updateSlider();
            break;

        case BATTERY:
            updateBattery();
            break;

        case DEATH:
            ui->aed_frame->setEnabled(false);
            controller->getTestController()->disableUI();
            break;

        default:
            setOneLight(sig, state);
            break;

    }

}

void AEDWindow::setController(TestController* controller){
    this->controller->setController(controller);
}


void AEDWindow::receiveDynamicSignal(const SignalType& sig, const string& data) const{
    switch(sig){

        case PRINT:
            consoleOut(data);
            break;

        default:
            qDebug() << "DYNAMICLLYY CALLED SIGNAL NOT FOUND. LIKELY MOVED TO STATIC";
            break;
    }

}

void AEDWindow::updateBattery() const{
    ui->batteryBar->setValue(controller->getAED()->getBattery()->getBatteryLevels());
}


void AEDWindow::initImgs() const{
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
            *p = p->scaled(ui->shock_button->size());//scales pimap to the size of shock button
        else{
            *p = p->scaled(ui->ok_image->size());//scales pixmap to the size of standard indicator
        }
        imageMap[filename] = p;
    }
    initImgs();

}

void AEDWindow::setAllLights(bool lit) const{
    QString uiname;
    foreach(auto i,uiMap){
        uiname = i->objectName();
        if(!imageMap.contains(uiname+"_on") || !imageMap.contains(uiname+"_off") ){
            controller->log("Image For " + uiname + "' Turning " + lit  + " Was Not Found");
             continue;
        }

        if(lit){
            i->setPixmap(*(imageMap[uiname+"_on"]));
        }
        else{
            i->setPixmap(*(imageMap[uiname+"_off"]));
        }
    }
    QIcon shockimg;
    if(lit){
        shockimg = QIcon(*imageMap["shock_button_on"]);
    }
    else
        shockimg = QIcon(*imageMap["shock_button_off"]);
    ui->shock_button->setIcon(shockimg);
    ui->shock_button->setIconSize((*imageMap["shock_button_off"]).size());
}

void AEDWindow::setOneLight(const SignalType sig, bool lit) const{
    setAllLights(false);
    QLabel* label = uiMap[sig];


    if(lit){
        label->setPixmap(*(imageMap[label->objectName()+"_on"]));
    }
    else{
        label->setPixmap(*(imageMap[label->objectName()+ "_off"]));
    }
}

void AEDWindow::setShockLight(bool isLightOn) const{
    QIcon shockimg;

    if(isLightOn){
        setAllLights(false);
        shockimg = QIcon(*imageMap["shock_button_on"]);
    }
    else
        shockimg = QIcon(*imageMap["shock_button_off"]);

    ui->shock_button->setIcon(shockimg);
    ui->shock_button->setIconSize((*imageMap["shock_button_off"]).size());
}

void AEDWindow::setPowerLight(bool isLightOn) const{
    QIcon powerimg;

    if(isLightOn){
        powerimg = QIcon(*imageMap["power_button_on"]);
    }
    else
        powerimg = QIcon(*imageMap["power_button_off"]);

    ui->power_button->setIcon(powerimg);
    ui->power_button->setIconSize(QSize(91,91));
}


void AEDWindow::closeEvent(QCloseEvent* event){
    controller->log("AEDWindow Close Event");
    emit aboutToClose();
    QString currentThreadId = "Semaphore Acquired As Thread : " + QString::number(reinterpret_cast<qulonglong>(QThread::currentThreadId()));
    controller->log(currentThreadId);
    QWidget::closeEvent(event);
}


AEDController* AEDWindow::getController() const{
    return controller;
}



void AEDWindow::recharge() const{
    controller->recharge();
}

AEDWindow::~AEDWindow(){
    controller->log("AEDWindow Destructor Called");

    controller->powerAEDOff();
    if (controlThread->isRunning()) {
        controlThread->quit();
        controlThread->wait();
    }

    delete ui;
    delete semaphore;
    delete controller;
    delete controlThread;


}



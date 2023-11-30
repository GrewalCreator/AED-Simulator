#include "aedwindow.h"
#include "ui_aedwindow.h"

AEDWindow::AEDWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AEDWindow){
    ui->setupUi(this);
    semaphore = new QSemaphore(0);
    controller = new AEDController(semaphore, this);
    controller->setProcessTracker(POWER_OFF);
    signalToString();
    initializeConnects();
    loadImgs();//the following sequence of function calls must maintain order: initImgs depends on loadImgs.
    initImgs();
    styling();
    controlThread = new QThread();


}
void AEDWindow::signalToString(){

    uiMap[LIGHTUP_OK] = ui->ok_image;
    uiMap[LIGHTUP_COMPRESSIONS] = ui->compressions_image;
    //uiMap[SET_STATUS] = ui->statusLight_image;
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
");
}


void AEDWindow::initializeConnects(){
    qDebug()<<"did transmitter connect?"<<connect(controller->transmit, SIGNAL(staticSignal(const SignalType&, bool)), this, SLOT(receiveStaticSignal(const SignalType&, bool)));
    connect(controller->transmit, SIGNAL(dynamicSignal(const SignalType&, const string&)), this, SLOT(receiveDynamicSignal(const SignalType&, const string&)));

    // Static Signal Connections
    connect(controller->transmit, SIGNAL(staticSignal(const SignalType&, bool)), this, SLOT(receiveStaticSignal(const SignalType&, bool)));

    // Dynamic Signal Connections
    connect(controller->transmit,SIGNAL(dynamicSignal(const SignalType&, const string&)), this, SLOT(receiveDynamicSignal(const SignalType&, const string&)));

    // Power Button
    connect(ui->power_button, SIGNAL(released()), this, SLOT(togglePower()));

    // Adult Pads Button
    connect(ui->adultPads_button, SIGNAL(released()), this, SLOT(toggleAdultPads()));

    // Child Pads Button
    connect(ui->childPads_button, SIGNAL(released()), this, SLOT(toggleChildPads()));

    // Print Messages To Console
    connect(controller)
}

void AEDWindow::onCleanup(){
    qDebug()<<"i fucking hate threads";
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


    }else{                                              // Power is Off, Turn It On
        connect(controlThread, SIGNAL(started()), controller, SLOT(run()));
        controller->moveToThread(controlThread);
        controlThread->start();
        controller->getAED()->playAudio(POWER_ON_AUDIO);
        controller->setProcessTracker(POWER_ON);
        bool successfulPowerOn = controller->powerAEDOn();
        if(!successfulPowerOn){
            // AED NOT SAFE TO RUN, Shutting Down
            consoleOut("AED Did Not Pass Tests. Powering Off . . .");
            togglePower();
        }


    }

}

void AEDWindow::toggleAdultPads(){
    controller->placePads(PatientType::ADULT);
}

void AEDWindow::toggleChildPads(){
    controller->placePads(PatientType::CHILD);
}

void AEDWindow::consoleOut(const string& message){
    QString qMessage = QString::fromStdString(message);
    ui->instruction_console->append(qMessage);
}

void AEDWindow::receiveStaticSignal(const SignalType& sig, bool state){
    //qDebug()<<uiMap[sig]<< " has been targeted.";
    if(sig == LIGHTUP_SHOCK){
        setShockLight(state);
    }
    else if(sig == POWER_INDICATOR){
        //setPowerLight(state);
    }
    else{
        setOneLight(sig, state);
    }
}



void AEDWindow::receiveDynamicSignal(const SignalType& sig, const string& data){
    switch(sig){
        case PRINT:
            consoleOut(data);
            break;
        default:
            break;
    }

    qDebug()<<uiMap[sig]<< " has been targeted with data "<< QString::fromStdString(data);
}

void AEDWindow::initImgs(){//TODO: make image name == ui element name, so a simple file replace will make a quick change in ui
    ui->ok_image->setPixmap(*(imageMap["ok_image_off"]));
    ui->standclear_image->setPixmap(*(imageMap["standclear_image_off"]));
    ui->compressions_image->setPixmap(*(imageMap["compressions_image_off"]));
    ui->pads_image->setPixmap(*(imageMap["pads_image_off"]));
    ui->help_image->setPixmap(*(imageMap["help_image_off"]));
    setShockLight(false);
}


void AEDWindow::loadImgs(){
    QDir directory(IMAGE_PATH);
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.png",QDir::Files);
    foreach(QString filename, images) {
        filename.resize(filename.length()-4);
        QString belongsTo = QString(filename).remove("_off").remove("_on");
        //qDebug()<<filename<<" Added to map";
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
        //qDebug()<<i->objectName()<<!imageMap.contains(uiname);
        if(!imageMap.contains(uiname+"_on") || !imageMap.contains(uiname+"_off") ){
            qDebug()<<uiname<<"image for case:" << lit <<" was not found in the map for whatever reason";
             continue;
        }
        //qDebug()<<i->objectName();
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
    //qDebug()<<label->objectName()<<"is being targeted";

    if(lit){
        label->setPixmap(*(imageMap[label->objectName()+"_on"]));
    }
    else{
        label->setPixmap(*(imageMap[label->objectName()+"_off"]));
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

void AEDWindow::closeEvent(QCloseEvent* event){
    emit aboutToClose();
    controller->powerAEDOff();
    semaphore->acquire();
    qDebug()<<"sem acquired as thread id:"<<QThread::currentThreadId();
    QWidget::closeEvent(event);
}

AEDController* AEDWindow::getController(){
    return controller;
}

AEDWindow::~AEDWindow(){
    qDebug()<<"in aedwindow decons";
    delete ui;
    delete controller;
}


void AEDWindow::on_adultPads_button_clicked()
{

}


void AEDWindow::on_childPads_button_clicked()
{

}


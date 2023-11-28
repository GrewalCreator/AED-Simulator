#include "aedwindow.h"
#include "ui_aedwindow.h"

AEDWindow::AEDWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AEDWindow){
    ui->setupUi(this);
    controller = new AEDController(this);


    controller->setProcessTracker(POWER_OFF);
    controlPool = new QThreadPool();
    controlPool->start(controller);
    signalToString();
    initializeConnects();
    loadImgs();//the following sequence of function calls must maintain order: initImgs depends on loadImgs.
    initImgs();
    styling();

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
    connect(controller->transmit, SIGNAL(staticSignal(const SignalType&)), this, SLOT(receiveStaticSignal(const SignalType& )));
    connect(controller->transmit, SIGNAL(dynamicSignal(const SignalType&, const string&)), this, SLOT(receiveDynamicSignal(const SignalType&, const string&)));

    // Static Signal Connections
    connect(controller->transmit, SIGNAL(staticSignal(const SignalType&)), this, SLOT(receiveStaticSignal(const SignalType& )));

    // Dynamic Signal Connections
    connect(controller->transmit,SIGNAL(dynamicSignal(const SignalType&, const string&)), this, SLOT(receiveDynamicSignal(const SignalType&, const string&)));

    // Power Button
    connect(ui->power_button, SIGNAL(released()), this, SLOT(togglePower()));
}

void AEDWindow::togglePower(){
    if(controller->getProcessTracker() != POWER_OFF){   // Power is On, Turn it Off
        controller->getAED()->playAudio(POWER_OFF_AUDIO);
        controller->powerAEDOff();
        controller->setProcessTracker(POWER_OFF);
    }else{                                              // Power is Off, Turn It On
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

void AEDWindow::consoleOut(const QString& message){
    ui->instruction_console->append(message);
}

void AEDWindow::receiveStaticSignal(const SignalType& sig){
    qDebug()<<uiMap[sig]<< " has been targeted.";
}

void AEDWindow::receiveDynamicSignal(const SignalType& sig, const string& data){
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
        qDebug()<<i->objectName()<<!imageMap.contains(uiname);
        if(!imageMap.contains(uiname+"_on") || !imageMap.contains(uiname+"_off") ){
            qDebug()<<uiname<<"image for case:" << lit <<" was not found in the map for whatever reason";
             continue;
        }
        qDebug()<<i->objectName();
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
        label->setPixmap(*(imageMap[label->objectName()+"_off"]));
    }
}

void AEDWindow::setShockLight(bool isLightOn){
    QIcon shockimg;
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

    QWidget::closeEvent(event);
}

AEDController* AEDWindow::getController(){
    return controller;
}

AEDWindow::~AEDWindow(){
    delete controlPool;
    delete controller;
    delete ui;
}


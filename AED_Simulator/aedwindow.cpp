#include "aedwindow.h"
#include "ui_aedwindow.h"
#include "QDir"
#include "QRegularExpression"
AEDWindow::AEDWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AEDWindow){
    ui->setupUi(this);
    controller = new AEDController(this);

    signalToString();
    initializeConnects();
    loadImgs();
    initImgs();
}

void AEDWindow::signalToString(){

    uiMap[LIGHTUP_OK] = ui->ok_image;
    uiMap[LIGHTUP_COMPRESSIONS] = ui->compressions_image;
    uiMap[SET_STATUS] = ui->statusLight_image;
    uiMap[LIGHTUP_911] = ui->help_image;
    uiMap[LIGHTUP_PADS] = ui->pads_image;
    uiMap[LIGHTUP_STANDCLEAR] = ui->standclear_image;
}

void AEDWindow::initializeConnects(){
    qDebug()<<"connection verify: "<< connect(controller, SIGNAL(staticSignal(SignalType sig)), this,SLOT(receiveStaticSignal(SignalType sig)));
    qDebug()<<"connection verify: "<< connect(controller, SIGNAL(dynamicSignal(SignalType sig, string& data)), this,SLOT(receiveDynamicSignal(SignalType, string& data)));

}

void AEDWindow::receiveStaticSignal(SignalType sig){
    qDebug()<<uiMap[sig]<< " has been targeted.";
}

void AEDWindow::receiveDynamicSignal(SignalType sig, string& data){
    qDebug()<<uiMap[sig]<< " has been targeted with data "<< QString::fromStdString(data);
}

void AEDWindow::initImgs(){//TODO: make image name == ui element name, so a simple file replace will make a quick change in ui

    ui->ok_image->setPixmap(*(imageMap["check_ok_off"]));
    ui->standclear_image->setPixmap(*(imageMap["stand_clear_off"]));
    ui->compressions_image->setPixmap(*(imageMap["compressions_off"]));
    ui->pads_image->setPixmap(*(imageMap["pads_off"]));
    ui->help_image->setPixmap(*(imageMap["get_help_off"]));
}

QList<QLabel *> AEDWindow::allimages(){
    QRegularExpression imgexp("(/image/g");
    QList<QLabel *> allimages = ui->frame->findChildren<QLabel*>(imgexp);
    return allimages;
}

void AEDWindow::loadImgs(){//TODO: introduce variable pixmap size to display compression icon better
    qDebug()<<"hi";
    QDir directory(IMAGE_PATH);
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.png",QDir::Files);
    foreach(QString filename, images) {
        filename.resize(filename.length()-4);
        qDebug()<<filename<<" Added to map";
        QPixmap* p = new QPixmap(IMAGE_PATH+filename);
        *p = p->scaled(ui->ok_image->size());//scales pixmap to the size of labels. MUST KEEP ALL LABELS UNIFORM
        imageMap[filename] = p;
    }
}


AEDController* AEDWindow::getController(){
    return controller;
}

AEDWindow::~AEDWindow(){
    delete ui;
}


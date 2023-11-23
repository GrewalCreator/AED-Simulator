#include "aedwindow.h"
#include "ui_aedwindow.h"
#include "QDir"
AEDWindow::AEDWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AEDWindow){
    ui->setupUi(this);
    controller = new AEDController(this);


    initializeConnects();
    loadImgs();
}


void AEDWindow::initializeConnects(){

}

void AEDWindow::loadImgs(){

    QDir directory("../AED_Simulator/images");
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
    foreach(QString filename, images) {
        qDebug()<<filename;
    }

}


AEDController* AEDWindow::getController(){
    return controller;
}
//void AEDWindow::setTestController(TestController *controller){
   // this->controlSystem->setController(controller);
//}

AEDWindow::~AEDWindow(){
    delete ui;
}


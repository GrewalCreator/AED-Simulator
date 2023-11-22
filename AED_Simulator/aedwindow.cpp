#include "aedwindow.h"
#include "ui_aedwindow.h"


AEDWindow::AEDWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AEDWindow){
    ui->setupUi(this);
    controlSystem = new AEDController(this);


    initializeConnects();
}


void AEDWindow::initializeConnects(){

}

AEDWindow::~AEDWindow(){
    delete ui;
}


#include "aedwindow.h"
#include "ui_aedwindow.h"


AEDWindow::AEDWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AEDWindow){
    ui->setupUi(this);
    controlSystem = new Controller(this);

    initializeConnects();
}


void AEDWindow::initializeConnects(){
    connect(ui->power_button, SIGNAL(released()), controlSystem, SLOT());
}

AEDWindow::~AEDWindow()
{
    delete ui;
}


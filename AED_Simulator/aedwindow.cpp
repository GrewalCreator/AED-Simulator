#include "aedwindow.h"
#include "ui_aedwindow.h"

AEDWindow::AEDWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AEDWindow)
{
    ui->setupUi(this);
}

AEDWindow::~AEDWindow()
{
    delete ui;
}


#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::TestWindow){
    ui->setupUi(this);
    testController = new TestController(this);
    initializeConnection();
}

void TestWindow::initializeConnection(){

}

void TestWindow::setController(AEDController* controller){
    testController->setController(controller);
}

void TestWindow::closeEvent(QCloseEvent* event){
    emit aboutToClose();

    QWidget::closeEvent(event);
}

TestWindow::~TestWindow(){
    delete ui;
}

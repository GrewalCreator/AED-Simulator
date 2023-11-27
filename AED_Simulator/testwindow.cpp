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



TestWindow::~TestWindow(){
    delete ui;
}

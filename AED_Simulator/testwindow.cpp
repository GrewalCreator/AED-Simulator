#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::TestWindow){
    ui->setupUi(this);
    testController = new TestController(this);
    initializeConnection();
}

void TestWindow::initializeConnection(){
    connect(ui->audioTest_button, SIGNAL(released()), testController, SLOT(testAudio()));

    // Remove Later
    connect(ui->logTest_button, SIGNAL(released()), testController, SLOT(logTest()));

    // Remove Later
    connect(ui->illuminateStepTest_button, SIGNAL(released()), testController, SLOT(illuminateTest()));

}

void TestWindow::setController(AEDController* controller){
    testController->setController(controller);
}



TestWindow::~TestWindow(){
    delete ui;
}

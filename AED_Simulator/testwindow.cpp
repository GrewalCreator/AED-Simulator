#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::TestWindow){
    ui->setupUi(this);
    testController = new TestController(this);
    initializeConnection();
}

void TestWindow::initializeConnection(){
    connect(ui->heartRate_slider, SIGNAL(valueChanged(int)), testController, SLOT(updateHeartRate(int)));
    connect(testController, SIGNAL(updateHeartRateImage(vector<double>&, vector<double>&)), this, SLOT(generateHeartRateImage(vector<double>&, vector<double>&)));
}

void TestWindow::setController(AEDController* controller){
    testController->setController(controller);
}

void TestWindow::closeEvent(QCloseEvent* event){
    emit aboutToClose();

    QWidget::closeEvent(event);
}

void TestWindow::generateHeartRateImage(vector<double>& xValues, vector<double>& yValues) {
    // Has not been working
}




TestWindow::~TestWindow(){  
    delete ui;
}

void TestWindow::on_testChildPads_button_clicked()
{
    testController->placePads(PatientType::CHILD);
}


void TestWindow::on_testAdultPads_button_clicked()
{
    testController->placePads(PatientType::ADULT);
}


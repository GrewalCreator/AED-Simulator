#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::TestWindow){
    ui->setupUi(this);
    testController = new TestController(this);
    initializeConnection();
            this->setStyleSheet(
                "QSlider::groove:horizontal {"
                "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FF0000, stop:1 #00FF00);"
                "    border: 1px solid #4A708B;"
                "    height: 10px;"
                "    border-radius: 4px;"
                "}"
                "QSlider::handle:horizontal {"
                "    background: #4A708B;"
                "    border: 1px solid #4A708B;"
                "    width: 14px;"
                "    height: 5px;"
                "    margin: -500px 0;"
                "    border-radius: 7px;"
                "}"
            );
}

void TestWindow::initializeConnection(){

    // Slider Connection
    connect(ui->heartRate_slider, SIGNAL(sliderReleased()), this, SLOT(updateHR()));

    // HeartRate Image
    connect(testController, SIGNAL(updateHeartRateImage(vector<double>&, vector<double>&)), this, SLOT(generateHeartRateImage(vector<double>&, vector<double>&)));

    // Pad Placement
    connect(ui->childPad_button, SIGNAL(released()), this, SLOT(padPlaced()));
    connect(ui->adultPad_button, SIGNAL(released()), this, SLOT(padPlaced()));
}

void TestWindow::padPlaced(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    qDebug()<<button->objectName();
    if(button){
        if(button->objectName() == "childPad_button"){
            testController->placePads(CHILD);
        }else if(button->objectName() == "adultPad_button"){
            testController->placePads(ADULT);
        }

    }
}


void TestWindow::updateHR(){
    testController->updateHeartRate(ui->heartRate_slider->value());
    testController->setPatientHR(ui->heartRate_slider->value());
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

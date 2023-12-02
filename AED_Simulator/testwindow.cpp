#include "testwindow.h"
#include "ui_testwindow.h"

#define MAX_HEART_RATE 250

TestWindow::TestWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::TestWindow){
    ui->setupUi(this);
    testController = new TestController(this);
    initializeConnection();

    styling();
}

void TestWindow::initializeConnection(){

    // Slider Connection
    connect(ui->heartRate_slider, SIGNAL(sliderReleased()), this, SLOT(updateHR()));

    // HeartRate Image
    connect(testController, SIGNAL(updateHeartRateImage(vector<double>&, vector<double>&)), this, SLOT(generateHeartRateImage(vector<double>&, vector<double>&)));

    // Pad Placement
    connect(ui->childPad_button, SIGNAL(released()), this, SLOT(padPlaced()));
    connect(ui->adultPad_button, SIGNAL(released()), this, SLOT(padPlaced()));

    //Heart rate testing buttons
    connect(ui->Systole, SIGNAL(clicked()), this, SLOT(setHR()));

    connect(ui->vtach, SIGNAL(clicked()), this, SLOT(setHR()));
}

void TestWindow::setHR(){

    QPushButton* button = qobject_cast<QPushButton*>(sender());

   if(button->objectName()=="Systole"){
       qDebug()<<"setting systole";
       ui->heartRate_slider->setValue(10);
   }
   else if(button->objectName()=="VTach"){
       ui->heartRate_slider->setValue(250);
   }
}

void TestWindow::styling(){

    //float normalBPMstart = 60;
    //float normalBPMend = 150;

    //float greenAreaStartValue = MAX_HEART_RATE / normalBPMstart;
    //float greenAreaEndValue = MAX_HEART_RATE / normalBPMend;

    this->setStyleSheet(
    "QSlider::handle::horizontal{"
    "   background: #4A708B; \
        width: 14px; \
        height: 14px; \
        border-radius: 7px; \
        margin: -5px 0;} \
    QSlider::groove:horizontal{ \
        border: 1px solid #999999; \
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.2399 red, stop:0.24 #90EE90, stop:0.6 #90EE90, stop:0.6001 red); \
        height: 10px; \
        border-radius: 4px;}"
    );

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

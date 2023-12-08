#include "testwindow.h"
#include "ui_testwindow.h"
#include "defs.h"



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
    connect(testController, SIGNAL(updateHeartRateImage(vector<double>&)), this, SLOT(generateHeartRateImage(vector<double>&)));

    // Pad Placement testing buttons
    connect(ui->childPad_button, SIGNAL(released()), this, SLOT(padPlaced()));
    connect(ui->adultPad_button, SIGNAL(released()), this, SLOT(padPlaced()));
    connect(ui->togglePadAED, SIGNAL(clicked()), testController, SLOT(togglePadAED()));
    connect(ui->togglePadPatient, SIGNAL(clicked()), testController, SLOT(removePadsFromPatient()));

    //Heart rate testing buttons
    connect(ui->systole_button, SIGNAL(clicked()), this, SLOT(setHR()));
    connect(ui->vtach_button, SIGNAL(clicked()), this, SLOT(setHR()));

    // Compressions
    connect(ui->compressionButton, SIGNAL(released()), this, SLOT(handleCompressionButtonPress()));

    // Update Slider after Shock
    connect(testController, SIGNAL(sliderUpdate()), this, SLOT(updateSlider()));

    // Wet Patient
    connect(ui->toggle_wet, SIGNAL(released()), testController, SLOT(toggleWetPatient()));

    // Deplete battery
    connect(ui->depleteBattery_button, SIGNAL(released()), testController, SLOT(depleteBattery()));

    // Disable UI on User Death [Not Patient Death]
    connect(testController, SIGNAL(uiDisable()), this, SLOT(disableUI()));

    // Patient Swap
    connect(ui->patientSwap_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(patientSwap(int)));

    // Evaluate the patient's status
    connect(ui->eval_button,SIGNAL(clicked()), this, SLOT(evaluate()));
}

void TestWindow::disableUI(){
    ui->test_frame->setEnabled(false);
}

void TestWindow::handleCompressionButtonPress() {
    int currentValue = ui->compressionNumber->value();



    if(testController->getControlSystem()->getCurrentStep() != CPR){return;}
    if(currentValue >= MAX_NUMBER_COMPRESSION){
        testController->getControlSystem()->print("MAXIMUM NUMBER OF COMPRESSIONS REACHED");
        return;
    }


    testController->incrementSessionCompressions();
    ui->compressionNumber->display(testController->getSessionCompressions());



}





void TestWindow::updateSlider(){
    ui->heartRate_slider->setValue(getCurrentHeartRate());
}

int TestWindow::getCurrentHeartRate(){
    return testController->getCurrentHeartRate();
}

void TestWindow::setHR(){

    QPushButton* button = qobject_cast<QPushButton*>(sender());

   if(button->objectName()=="systole_button"){
       ui->heartRate_slider->setValue(10);
       testController->getControlSystem()->updateHR(20);
   }
   else if(button->objectName()=="vtach_button"){
       testController->getControlSystem()->updateHR(220);
   }
}

void TestWindow::styling(){

    this->setStyleSheet(
    "QSlider::handle::horizontal{"
    "   background: #4A708B; \
        width: 14px; \
        height: 14px; \
        border-radius: 7px; \
        margin: -5px 0;} \
    QSlider::groove:horizontal{ \
        border: 1px solid #999999; \
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.2399 orange, stop:0.24 #90EE90, stop:0.6 #90EE90, stop:0.6001 red, stop: 0.8 red, stop: 0.8001 black); \
        height: 10px; \
        border-radius: 4px;}"
    );

}

void TestWindow::padPlaced(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if(button){
        if(button->objectName() == "childPad_button"){
            testController->placePads(CHILD);
        }else if(button->objectName() == "adultPad_button"){
            testController->placePads(ADULT);
        }

    }
}


void TestWindow::updateHR(){
    testController->getControlSystem()->updateHR(ui->heartRate_slider->value());
}

void TestWindow::setController(AEDController* controller){
    testController->setController(controller);
}

TestController* TestWindow::getController(){return testController;}


void TestWindow::closeEvent(QCloseEvent* event){
    emit aboutToClose();
    QWidget::closeEvent(event);
}


void TestWindow::generateHeartRateImage(vector<double>& yValues) {

    if (!this->testController->getControlSystem()->getPatient()->getHasPadsOn()){
        return;
    }

    QLabel* l = ui->graph_label;

    QPixmap pixmap(l->width(), l->height());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    QPen Red(QColor(255, 0, 0), 1);
    painter.setPen(Red);


    const double amplitude = 0.75;
    const double frequency =  2 * M_PI * (ui->heartRate_slider->value()/5) / yValues.size();

    /*for (size_t i = 0; i < yValues.size(); ++i) {
        yValues[i] = amplitude * sin(frequency * i);
    }*/


    for (size_t i = 0; i < yValues.size() - 1; ++i) {

        int startY = floor(yValues[i] * 50 + 50);

        int endY = floor(yValues[i + 1] * 50 + 50);

        painter.drawLine(i, startY, i+1, endY);
    }

    l->setPixmap(pixmap);
    l->show();
}




TestWindow::~TestWindow(){  
    delete ui;
    delete testController;
}


void TestWindow::patientSwap(int index){
    AEDController* aedController = testController->getControlSystem();
    aedController->toggleActivePatient();



}

void TestWindow::evaluate(){
    int currHR = testController->getCurrentHeartRate();
    if(testController->getControlSystem()->getDeathFlag()){
        ui->eval_label->setText("Status: PATIENT IS RAPIDLY DETERIORATING");
        ui->eval_label->setStyleSheet("QLabel{background-color: black;"
                                      "color: red;}");
    }
    else if(currHR <=0){
        ui->eval_label->setText("Status: PATIENT IS DEAD. RIP");
        ui->eval_label->setStyleSheet("QLabel{background-color: black;"
                                      "color: red;}");
    }
    else if((currHR>MAX_NOMINAL_BPM) || (currHR < MIN_NOMINAL_BPM)){
        ui->eval_label->setText("Status: PATIENT IS IN DANGER");
        ui->eval_label->setStyleSheet("QLabel{"
                                      "color: red;}");
    }
    else{
        ui->eval_label->setText("Status: PATIENT IS RECOVERING");
        ui->eval_label->setStyleSheet("QLabel{background-color: white;"
                                      "color: green;}");
    }
}

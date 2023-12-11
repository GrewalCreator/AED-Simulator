#include "testwindow.h"
#include "ui_testwindow.h"
#include "defs.h"



TestWindow::TestWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::TestWindow){
    ui->setupUi(this);
    testController = new TestController(this);
    initializeConnection();

    styling();
    ui->userDeath_label->hide();
}

void TestWindow::initializeConnection(){

    // Slider Connection
    connect(ui->heartRate_slider, SIGNAL(sliderReleased()), this, SLOT(updateHR()));

    // HeartRate Image
    connect(testController, SIGNAL(updateHeartRateImage(vector<double>&)), this, SLOT(generateHeartRateImage(vector<double>&)));

    // Pad Placement
    connect(ui->childPad_button, SIGNAL(released()), this, SLOT(padPlaced()));
    connect(ui->adultPad_button, SIGNAL(released()), this, SLOT(padPlaced()));


    connect(ui->togglePadConnection, SIGNAL(clicked()), testController, SLOT(togglePadConnection()));
    connect(ui->togglePadPatient, SIGNAL(clicked()), testController, SLOT(removePadsFromPatient()));

    //Heart rate testing buttons
    connect(ui->systole_button, SIGNAL(clicked()), this, SLOT(setHR()));
    connect(ui->vtach_button, SIGNAL(clicked()), this, SLOT(setHR()));

    // Compressions
    connect(ui->compressionButton, SIGNAL(released()), this, SLOT(executeCompression()));

    // Update Slider after Shock
    connect(testController, SIGNAL(sliderUpdate()), this, SLOT(updateSlider()));

    // Wet Patient
    connect(ui->currentEnvironment_comboBox, SIGNAL(currentIndexChanged(int)), testController, SLOT(toggleWetPatient(int)));

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

    ui->userDeath_label->setText("Shocked In Conductive Environment, You Died!");
    ui->userDeath_label->setStyleSheet("font-size: 24px; color: red; font-weight: bold;"); // Style the message label
    ui->userDeath_label->setWordWrap(true); // Enable word wrapping
    ui->userDeath_label->setAlignment(Qt::AlignCenter); // Align text to center (optional)
    ui->userDeath_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // Allow expanding horizontally
    ui->userDeath_label->show();
}

void TestWindow::executeCompression() {
    int compressionsDone = ui->compressionNumber->value();

    if(testController->getControlSystem()->getCurrentStep() != CPR){return;}
    if(compressionsDone >= MAX_NUMBER_COMPRESSION){
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

    QFile styleFile(QString(STYLESHEET_PATH) + "testWindowStyle.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    this->setStyleSheet(styleSheet);


}

void TestWindow::padPlaced(){
    if(testController->getControlSystem()->getCurrentStep() > POWER_OFF){
        QPushButton* button = qobject_cast<QPushButton*>(sender());

        if(button != nullptr){
            if(button->objectName() == "childPad_button"){
                testController->placePads(CHILD);
            }else if(button->objectName() == "adultPad_button"){
                testController->placePads(ADULT);
            }
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


    for (size_t i = 0; i < yValues.size() - 1; ++i) {

        int startY = floor(yValues[i] * 50 + 50);

        int endY = floor(yValues[i + 1] * 50 + 50);

        painter.drawLine(i, startY, i+1, endY);
    }

    l->setPixmap(pixmap);
    l->show();
}



void TestWindow::patientSwap(int index){
    Q_UNUSED(index); // Mark the index parameter as unused
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

TestWindow::~TestWindow(){
    delete ui;
    delete testController;
}

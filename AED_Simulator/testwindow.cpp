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
    connect(testController, SIGNAL(updateHeartRateImage(vector<double>&)), this, SLOT(generateHeartRateImage(vector<double>&)));

    // Pad Placement
    connect(ui->childPad_button, SIGNAL(released()), this, SLOT(padPlaced()));
    connect(ui->adultPad_button, SIGNAL(released()), this, SLOT(padPlaced()));

    //Heart rate testing buttons
    connect(ui->systole_button, SIGNAL(clicked()), this, SLOT(setHR()));
    connect(ui->togglePadAED, SIGNAL(clicked()), testController, SLOT(togglePadAED()));
    connect(ui->togglePadPatient, SIGNAL(clicked()), testController, SLOT(togglePadPatient()));
    connect(ui->vtach_button, SIGNAL(clicked()), this, SLOT(setHR()));

    connect(ui->compressionButton, SIGNAL(released()), this, SLOT(handleCompresstionButtonPress()));

    // Update Slider after Shock
    connect(testController, SIGNAL(sliderUpdate()), this, SLOT(updateSlider()));
}

void TestWindow::handleCompresstionButtonPress() {
    int currentValue = ui->compresstionNumber->value();

        // Ensure the value doesn't exceed 30
        if (currentValue < 30) {
            ui->compresstionNumber->display(currentValue + 1);
        }
}

void TestWindow::updateSlider(){
    qDebug() << "Updating Slider TestWindow";
    ui->heartRate_slider->setValue(getCurrentHeartRate());

}

int TestWindow::getCurrentHeartRate(){
    return testController->getCurrentHeartRate();
}

void TestWindow::setHR(){

    QPushButton* button = qobject_cast<QPushButton*>(sender());

   if(button->objectName()=="systole_button"){
       qDebug()<<"setting systole";
       ui->heartRate_slider->setValue(10);
   }
   else if(button->objectName()=="vtach_button"){
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

    if(button){
        if(button->objectName() == "childPad_button"){
            testController->placePads(CHILD);
        }else if(button->objectName() == "adultPad_button"){
            testController->placePads(ADULT);
        }

    }
}


void TestWindow::updateHR(){
    //testController->updateHeartRate(ui->heartRate_slider->value());
    testController->setPatientHR(ui->heartRate_slider->value());
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
    QLabel* l = ui->graph_label;

    QPixmap pixmap(l->width(), l->height());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    QPen Red(QColor(255, 0, 0), 1);
    painter.setPen(Red);

    // Assuming xValues and yValues have the same size and represent a circular pattern

    // Transform circular points into a wave-like pattern
    const double amplitude = 0.75;
    const double frequency =  2 * M_PI * (ui->heartRate_slider->value()/5) / yValues.size();  // Adjust frequency for the number of points

    for (size_t i = 0; i < yValues.size(); ++i) {
        yValues[i] = amplitude * sin(frequency * i); // Adjust amplitude and phase shift as needed
    }

    // Plot lines connecting transformed points to create a wave
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
}



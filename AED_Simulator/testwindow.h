#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>

#include "testcontroller.h"
#include "QPainter"
#include "QImage"
#include "PatientType.h"
#include "cmath"
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class TestWindow; }
QT_END_NAMESPACE

class TestWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit TestWindow(QWidget *parent = nullptr);
    virtual ~TestWindow();
    void setController(AEDController*);
    TestController* getController();
    void styling();
    int getCurrentHeartRate();



signals:
    void aboutToClose();

protected:
    void closeEvent(QCloseEvent *event) override;


private slots:
    void padPlaced();
    void generateHeartRateImage(vector<double>& yValues);
    void updateHR();
    void setHR();
    void updateSlider();
    void executeCompression();
    void patientSwap(int index);
    void disableUI();
    void evaluate();



private:
    Ui::TestWindow *ui;
    TestController* testController;
    void initializeConnection();


};

#endif // TESTWINDOW_H

#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>

#include "testcontroller.h"
#include "QPainter"
#include "QImage"
#include "PatientType.h"

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

signals:
    void aboutToClose();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void generateHeartRateImage(vector<double>& xValues, vector<double>& yValues);

private slots:
    void on_testChildPads_button_clicked();

    void on_testAdultPads_button_clicked();

private:
    Ui::TestWindow *ui;
    TestController* testController;
    void initializeConnection();

};

#endif // TESTWINDOW_H

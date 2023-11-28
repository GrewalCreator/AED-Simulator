#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>

#include "testcontroller.h"

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

private:
    Ui::TestWindow *ui;
    TestController* testController;
    void initializeConnection();
};

#endif // TESTWINDOW_H

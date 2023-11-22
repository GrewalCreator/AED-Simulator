#ifndef AEDWINDOW_H
#define AEDWINDOW_H

#include <QMainWindow>
#include "aedcontroller.h"
#include "testcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AEDWindow; }
QT_END_NAMESPACE

class AEDWindow : public QMainWindow
{
    Q_OBJECT

public:
    AEDWindow(QWidget *parent = nullptr);
    virtual ~AEDWindow();
    AEDController* getController();
    //void setTestController(TestController* controller);

private:
    Ui::AEDWindow *ui;
    AEDController* controller;

    void initializeConnects();
};
#endif // AEDWINDOW_H

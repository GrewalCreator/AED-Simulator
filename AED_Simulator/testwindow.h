#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>

#include "testcontroller.h"

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    virtual ~TestWindow();

private:
    Ui::TestWindow *ui;
    TestController* testController;
    void initializeConnection();
};

#endif // TESTWINDOW_H

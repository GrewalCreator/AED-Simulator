#ifndef AEDWINDOW_H
#define AEDWINDOW_H

#include <QMainWindow>
#include "aedcontroller.h"
#include "testcontroller.h"
#include <QMap>
#include <QPixmap>
#include <QLabel>
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
    QMap<QString, QPixmap*> imageMap;
    QMap<SignalType,QLabel*> uiMap;
    AEDController* controller;
    //TODO: make 2 signal handlers: static and dynamic
    void loadImgs();
    void initImgs();
    QList<QLabel*> allimages();
    void signalToString();
    void initializeConnects();
private slots:
    void receiveStaticSignal(SignalType sig);
    void receiveDynamicSignal(SignalType sig, string& data);

};
#endif // AEDWINDOW_H

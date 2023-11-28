#ifndef AEDWINDOW_H
#define AEDWINDOW_H

#include <QMainWindow>
#include "aedcontroller.h"
#include "testcontroller.h"
#include <QMap>
#include <QPixmap>
#include <QLabel>
#include "QThreadPool"
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
    QThreadPool controlPool;
    //TODO: make 2 signal handlers: static and dynamic
    void loadImgs();
    void initImgs();
    void signalToString();
    void initializeConnects();
    void setOneLight(const SignalType sig, bool lit);
    void setAllLights(bool);
    void styling();
    void setShockLight(bool);
private slots:
    void receiveStaticSignal(const SignalType& sig);
    void receiveDynamicSignal(const SignalType& sig, const string& data);

};
#endif // AEDWINDOW_H

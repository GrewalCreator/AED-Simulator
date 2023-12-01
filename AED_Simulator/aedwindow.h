#ifndef AEDWINDOW_H
#define AEDWINDOW_H
#include "QThread"
#include <QMainWindow>
#include "aedcontroller.h"
#include "testcontroller.h"
#include <QMap>
#include <QPixmap>
#include <QLabel>
#include "QDir"
#include "QRegularExpression"

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


private:
    Ui::AEDWindow *ui;
    QMap<QString, QPixmap*> imageMap;
    QMap<SignalType,QLabel*> uiMap;
    AEDController* controller;
    QSemaphore* semaphore;
    QThread* controlThread;
    //TODO: make 2 signal handlers: static and dynamic
    void loadImgs();
    void initImgs();
    void signalToString();
    void initializeConnects();
    void setOneLight(const SignalType sig, bool lit);
    void setAllLights(bool);
    void styling();
    void setShockLight(bool);
    void setPowerLight(bool);
    void setUpVisuals();

signals:
    void aboutToClose();

protected:
    //void closeEvent(QCloseEvent *event) override;

private slots:
    void receiveStaticSignal(const SignalType& sig, bool);
    void receiveDynamicSignal(const SignalType& sig, const string& data);
    void togglePower();
    void toggleAdultPads();
    void toggleChildPads();
    void consoleOut(const string& message);


};
#endif // AEDWINDOW_H

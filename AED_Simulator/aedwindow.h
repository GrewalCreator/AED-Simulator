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
    explicit AEDWindow(QWidget *parent = nullptr);
    virtual ~AEDWindow();
    AEDController* getController() const;
    void setController(TestController*);


private:
    Ui::AEDWindow *ui;
    QMap<QString, QPixmap*> imageMap;
    QMap<SignalType,QLabel*> uiMap;
    AEDController* controller;
    QSemaphore* semaphore;
    QThread* controlThread;

    void loadImgs();
    void initImgs() const;
    void signalToString();
    void initializeConnects() const;
    void setOneLight(const SignalType sig, bool lit) const;
    void setAllLights(bool) const;
    void styling();
    void setShockLight(bool) const;
    void setPowerLight(bool) const;
    void setUpVisuals();
    void updateBattery() const;

    void resetUI(bool) const;
    void updateSlider() const;

signals:
    void aboutToClose();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void receiveStaticSignal(const SignalType& sig, bool) const;
    void receiveDynamicSignal(const SignalType& sig, const string& data) const;
    void togglePower() const;
    void consoleOut(const string& message) const;

    void recharge() const;
    void shockPressed() const;


};
#endif // AEDWINDOW_H

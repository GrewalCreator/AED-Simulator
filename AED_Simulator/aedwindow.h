#ifndef AEDWINDOW_H
#define AEDWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AEDWindow; }
QT_END_NAMESPACE

class AEDWindow : public QMainWindow
{
    Q_OBJECT

public:
    AEDWindow(QWidget *parent = nullptr);
    ~AEDWindow();

private:
    Ui::AEDWindow *ui;
};
#endif // AEDWINDOW_H

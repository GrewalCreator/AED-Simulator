#include "aedwindow.h"
#include "testwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AEDWindow w;
    TestWindow tw;
    tw.setController(w.getController());

    QObject::connect(&w, &AEDWindow::aboutToClose, &tw, &TestWindow::close);
    QObject::connect(&tw, &TestWindow::aboutToClose, &w, &AEDWindow::close);

    tw.show();
    w.show();
    return a.exec();
}

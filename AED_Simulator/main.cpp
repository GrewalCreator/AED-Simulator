#include "aedwindow.h"
#include "testwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AEDWindow w;
    TestWindow tw;
    tw.setController(w.getController());

    QObject::connect(&w, SIGNAL(aboutToClose()), &tw, SLOT(close()));
    QObject::connect(&tw, SIGNAL(aboutToClose()), &w, SLOT(close()));

    tw.show();
    w.show();
    return a.exec();
}

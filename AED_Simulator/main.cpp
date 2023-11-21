#include "aedwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AEDWindow w;
    w.show();
    return a.exec();
}

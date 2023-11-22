#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "defs.h"
#include "aed.h"



class Controller: public QObject{
    Q_OBJECT
public:
    Controller(QObject* parent = nullptr);
    virtual ~Controller();

private:
    AED* automatedED;

};

#endif // CONTROLLER_H

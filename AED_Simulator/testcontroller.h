#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>

class TestController: public QObject{
    Q_OBJECT
public:
    TestController(QObject* parent = nullptr);
    virtual ~TestController();
};

#endif // TESTCONTROLLER_H

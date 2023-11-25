#ifndef LOGGER_H
#define LOGGER_H

#include "defs.h"
#include "QDateTime"
#include "QFile"
#include "QDir"

class Logger
{
public:
    Logger();

    void setup();

    virtual ~Logger();
private:
    QFile* activeFile;
    QDateTime* dateHandler;
};

#endif // LOGGER_H

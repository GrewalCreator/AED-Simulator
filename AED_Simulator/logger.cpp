#include "logger.h"

Logger::Logger(){
    dateHandler = new QDateTime();
    activeFile = new QFile();
}

//TO-DO: Make setup test button and log test button
void Logger::setup(){
    QString currentDate = dateHandler->currentDateTime().toString("yyyy:MM:dd") + "-AED";
    if(QDir(currentDate).exists()){
        QString activeFileName = dateHandler->currentDateTime().toString("yyyy:MM:dd hh:mm:ss") + "-AED_LOG.log";
        activeFile->setFileName(activeFileName);
        activeFile->open(QIODevice::WriteOnly | QIODevice::Text);
    }
    // check if Folder YYYY:MM::DDD-AED Exists
        // If True, Open
        // If False, Create
    // & add YYY:MM:DD-AED_LOG.log
    // Set this file as this runtimes file to write to [activeFile]
}

Logger::~Logger(){
    delete dateHandler;
}

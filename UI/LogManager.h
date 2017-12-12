#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#define LOG_FILES_PATH "log/"

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>
#include <windows.h>

#include "ConsoleManager.h"


using namespace std;

enum LogType {
    LOG_TYPE_INFO,
    LOG_TYPE_WARNING,
    LOG_TYPE_ERROR,
    LOG_TYPE_SUCCESS
};

class LogManager {
public:
    LogManager();
    ~LogManager();
    void streamLog(ostream &log, LogType _logType);

private:
    string getCurrentTime();
    string getLogFileName();
    void printInfoLog(string log);
    void printSuccessLog(string log);
    void printWarningLog(string log);
    void printErrorLog(string log);
    void saveLogToFile(string log);

private:
    ConsoleManager console;
    ofstream logFile;
    string logFileName;
};

#endif // LOGMANAGER_H

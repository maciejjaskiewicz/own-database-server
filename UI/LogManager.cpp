#include "LogManager.h"

LogManager::LogManager() {
    console.clearConsole();
    console.setColorAttribute(CONSOLE_COLOR_LIGHT_GREEN);
    cout<<"[Database server]"<<endl;
    printInfoLog("Server starting...");
}

LogManager::~LogManager() {
    printInfoLog("Stopping server...");
}

void LogManager::streamLog(ostream &log, LogType _logType) {
    ostringstream& logStr = dynamic_cast<ostringstream&>(log);

    switch(_logType) {
    case LOG_TYPE_INFO:
        printInfoLog(logStr.str());
        break;
    case LOG_TYPE_SUCCESS:
        printSuccessLog(logStr.str());
        break;
    case LOG_TYPE_WARNING:
        printWarningLog(logStr.str());
        break;
    case LOG_TYPE_ERROR:
        printErrorLog(logStr.str());
        break;
    default:
        printInfoLog(logStr.str());
        break;
    }
}

string LogManager::getCurrentTime() {
    stringstream timeStr;
    time_t t = time(0);
    struct tm * now = localtime( & t );

    if(now->tm_hour > 9) timeStr<<now->tm_hour;
    else timeStr<<"0"<<now->tm_hour;

    timeStr<<":";

    if(now->tm_min > 9) timeStr<<now->tm_min;
    else timeStr<<"0"<<now->tm_min;

    timeStr<<":";

    if(now->tm_sec > 9) timeStr<<now->tm_sec;
    else timeStr<<"0"<<now->tm_sec;

    return timeStr.str();
}

string LogManager::getLogFileName() {
    stringstream fileName;
    fileName<<"log_";
    time_t t = time(0);
    struct tm * now = localtime( & t );

    if(now->tm_mday > 9) fileName<<now->tm_mday;
    else fileName<<"0"<<now->tm_mday;

    fileName<<"-";

    if(now->tm_mon+1 > 9) fileName<<now->tm_mon+1;
    else fileName<<"0"<<now->tm_mon+1;

    fileName<<"-";

    fileName<<now->tm_year+1900;

    fileName<<"_";

    if(now->tm_hour > 9) fileName<<now->tm_hour;
    else fileName<<"0"<<now->tm_hour;

    fileName<<"-";

    if(now->tm_min > 9) fileName<<now->tm_min;
    else fileName<<"0"<<now->tm_min;

    fileName<<"-";

    if(now->tm_sec > 9) fileName<<now->tm_sec;
    else fileName<<"0"<<now->tm_sec;

    return fileName.str();
}

void LogManager::printInfoLog(string log) {
    console.setColorAttribute(CONSOLE_COLOR_LIGHT_YELLOW);
    cout<<"["<<getCurrentTime()<<"] ";
    console.restoreDefaultColors();
    cout<<log<<endl;
}

void LogManager::printSuccessLog(string log) {
    console.setColorAttribute(CONSOLE_COLOR_LIGHT_GREEN);
    cout<<"["<<getCurrentTime()<<"] [SUCCESS] "<<log<<endl;
}

void LogManager::printWarningLog(string log) {
    console.setColorAttribute(CONSOLE_COLOR_LIGHT_YELLOW);
    cout<<"["<<getCurrentTime()<<"] [WARNING] "<<log<<endl;
}

void LogManager::printErrorLog(string log) {
    console.setColorAttribute(CONSOLE_COLOR_LIGHT_RED);
    cout<<"["<<getCurrentTime()<<"] [ERROR] "<<log<<endl;
}

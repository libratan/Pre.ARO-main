//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: LogClient.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for LogClient
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef LOGCLIENT_H
#define LOGCLIENT_H

#include <../header/Network.h>

struct LogRecordStruct
{
    char dateTime[24];
    int csciId;
    int classification;
    int recordLevel;
    char freeText[1000];
};

class LogClient
{
    enum LogRecordDestEnum
    {
        WRITE_LOG_RECORD_TO_NONE = 0,
        WRITE_LOG_RECORD_TO_FILE = 1,
        WRITE_LOG_RECORD_TO_SHELL = 2,
        WRITE_LOG_RECORD_TO_FILE_AND_SHELL = 3
    };

public:
    LogClient();

    virtual ~LogClient(void);

    //Singleton
    static LogClient* getInstance()
    {
        while (instance_ == 0)
        {
            instance_ = new LogClient();
        }
        return instance_;
    }

    void sendLogRecord(const char* logText, int csciId, int classification, int recordLevel);

    void writeLog(const char* logText, int csciId = 2, int classification = 1, int recordLevel = 2, const LogRecordDestEnum& printStatus = WRITE_LOG_RECORD_TO_FILE_AND_SHELL);

    // For the future - virtual void writeSecurityLog(char* logText, int csciId, int classification, int recordLevel, const LogRecordDestEnum& printStatus = WRITE_LOG_RECORD_TO_FILE_AND_SHELL);
        
protected:
    Network::TCPSocket socketObj;

private:
    static LogClient* instance_;
    LogRecordStruct recordInstance;

    void writeLogToShell(const char* logText, int csciId, int classification, int recordLevel);
    void currentDateTime(char* dateTime);
};

#endif // !LOGCLIENT_H
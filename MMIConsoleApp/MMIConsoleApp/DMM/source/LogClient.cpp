//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: LogClient.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for Log Client
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../DMM/header/LogClient.h>

using namespace Network;

LogClient* LogClient::instance_ = NULL;

//****************************************************************************
//* Function Name  : LogClient()
//* Purpose        : Constructor of LogClient
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
LogClient::LogClient()
{
    memset(&recordInstance, 0, sizeof(recordInstance));
    // connect the client socket to server socket
    socketObj.tcpConnect(CONNECT_TYPE::TCP_UNICAST, "127.0.0.1", 63864);
}

//****************************************************************************
//* Function Name  : ~LogClient(void)
//* Purpose        : Destructor of LogClient
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
LogClient::~LogClient(void)
{

}

//****************************************************************************
//* Function Name  : sendLogRecord(const char* logText, int csciId, int classification, int recordLevel)
//* Purpose        : Send Logs to Log Server over TCP socket
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void LogClient::sendLogRecord(const char* logText, int csciId, int classification, int recordLevel)
{
    string s;
    char buffer[8];
    currentDateTime(recordInstance.dateTime);
    recordInstance.csciId = csciId;
    recordInstance.classification = classification;
    recordInstance.recordLevel = recordLevel;
    sprintf_s(recordInstance.freeText,logText);

    s += recordInstance.dateTime;
    s += ", ";
    _itoa_s(recordInstance.csciId, buffer,10);
    s += buffer;
    s += ", ";
    _itoa_s(recordInstance.classification, buffer, 10);
    s += buffer;
    s += ", ";
    _itoa_s(recordInstance.recordLevel, buffer, 10);
    s += buffer;
    s += ", ";
    s += recordInstance.freeText;
    socketObj.Send(s.c_str(), strlen(s.c_str()), 0);
}

//****************************************************************************
//* Function Name  : writeLog(const char* logText, int csciId, int classification, int recordLevel, const LogRecordDestEnum& printStatus)
//* Purpose        : Write Logs
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void LogClient::writeLog(const char* logText, int csciId, int classification, int recordLevel, const LogRecordDestEnum& printStatus)
{
    switch (printStatus)
    {
    case WRITE_LOG_RECORD_TO_FILE:
        sendLogRecord(logText, csciId, classification, recordLevel);
        break;
    case WRITE_LOG_RECORD_TO_SHELL:
        writeLogToShell(logText, csciId, classification, recordLevel);
        break;
    case WRITE_LOG_RECORD_TO_FILE_AND_SHELL:
        sendLogRecord(logText, csciId, classification, recordLevel);
        writeLogToShell(logText, csciId, classification, recordLevel);
        break;
    default:
        printf("Record destination is NONE\n");
    }
}

//****************************************************************************
//* Function Name  : writeLogToShell(const char* logText, int csciId, int classification, int recordLevel)
//* Purpose        : Write Logs to Shell
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void LogClient::writeLogToShell(const char* logText, int csciId, int classification, int recordLevel)
{
    printf("%d, ", csciId);
    printf("%d, ", classification);
    printf("%d, ", recordLevel);
    printf("%s", logText);
    printf("\n");
}

//****************************************************************************
//* Function Name  : currentDateTime(char* dateTime)
//* Purpose        : Get current date/time, format is YYYY-MM-DD.HH:mm:ss
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void LogClient::currentDateTime(char* dateTime)
{
    time_t rawtime;
    struct tm ptm;

    time(&rawtime);
    gmtime_s(&ptm , &rawtime);
    strftime(dateTime, 24, "%Y/%m/%d %X", &ptm);
}



//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: CallbackServer.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for CallbackServer
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef CALLBACKSERVER_H
#define CALLBACKSERVER_H

#pragma once
#include <winsock.h>
#include <../Common/gen_type.h>

class CallbackServer
{
public:

    // Default Constructor
    CallbackServer();

    // Default Destructor
    ~CallbackServer();
    
    enum CALLBACK_CONSTANTS
    {
        max_header_size = 20,               // TCP header size 
        endian_flag_little = 0x41424344,    // ABCD
        data_buffer_size = 4096             // TCP data size 
    };

    //****************************************************************************
    //* Function Name  : callbackThreadServer
    //* Purpose        : Callback Server.
    //*                  This is required to catch any Callback responses that are sent from FliteScene.
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    static INT32 callbackThreadServer();

    //****************************************************************************
    //* Function Name  : startCallbackServerThread
    //* Purpose        : Starts the Callback Server thread.
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    static void startCallbackServerThread();

    // Static getters for cursor object info fields
    //****************************************************************************
    //* Function Name  : getCursorLongitude
    //* Purpose        : Returns the Cursor Longitude
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    static FLOAT64 getCursorLongitude(void);

    //****************************************************************************
    //* Function Name  : getCursorLatitude
    //* Purpose        : Returns Cursor Latitude
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    static FLOAT64 getCursorLatitude(void);

    //****************************************************************************
    //* Function Name  : getRouteWaypointIndex
    //* Purpose        : Returns the RouteWaypointIndex
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    static INT32   getRouteWaypointIndex(void);

private:
    //****************************************************************************
    //* Function Name  : processClient
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void   processClient(SOCKET socketIn);

    //****************************************************************************
    //* Function Name  : readBytesTCP
    //* Purpose        : This function reads the TCP data 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static UINT32 readBytesTCP(SOCKET socketIn,
                               CHAR (&pBuffer)[data_buffer_size],
                               INT32 nLength);

    //****************************************************************************
    //* Function Name  : readBytesTCPHeader
    //* Purpose        : This function reads the TCP Header
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static UINT32 readBytesTCPHeader(SOCKET socketIn,
                                     CHAR (&pBuffer)[max_header_size],
                                     INT32 nLength);

    //****************************************************************************
    //* Function Name  : swapBytes
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void   swapBytes(INT32& pValue);

    // Response Parsers
    //****************************************************************************
    //* Function Name  : processGeoResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processGeoResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processSetObjectResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processSetObjectResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processObjectSelectResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processObjectSelectResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processObjectInfoResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processObjectInfoResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processCLOSResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processCLOSResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processPOIResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processPOIResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processTextBoxContentsResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processTextBoxContentsResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processDataframeResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processDataframeResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processMGRSConversionResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processMGRSConversionResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processDMSConversionResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processDMSConversionResponse(CHAR (&pData)[data_buffer_size]);

    //****************************************************************************
    //* Function Name  : processMapStatusResponse
    //* Purpose        : 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : private
    //* Note           :
    //****************************************************************************
    static void processMapStatusResponse(CHAR (&pData)[data_buffer_size]);
};
#endif // !CALLBACKSERVER_H


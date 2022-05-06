/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++ FliteScene Interface Source Code
++ FliteScene License holders are authorized to use this source code file
++ for the purposes of integrating FliteScene with their software applications
++ in accordance with the license agreement.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++
++ Copyright (C) L3Harris Technologies 2007-2020 - All Rights Reserved
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++ FILE:           IF_Callback.h
++
++ CLASSIFICATION:  Unclassified
++
++ DESCRIPTION:     Defines the callback library interface
++
++ LIMITATIONS:     none
++
++ SOFTWARE HISTORY:
++
++     See ClearCase (cleartool lshistory)
++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef _IF_CALLBACK_H
#define _IF_CALLBACK_H 1

/*****************************************************************************
** Error Codes
******************************************************************************/
enum CALLBACK_ERROR_CODES
{
    ERROR_UNKNOWN = 0,
    /* e.g. FliteScene not initialized */
    ERROR_INIT = 1,     
    /* e.g. task, semaphore, or timer error */
    ERROR_OS = 2,       
    /* e.g. memory allocation or bad pointer */
    ERROR_MEMORY = 3,  
    /* e.g. network socket error */
    ERROR_NETWORK = 4,  
    /* e.g. opengl error */
    ERROR_GRAPHICS = 5, 
    /* e.g. message received with invalid parameter */
    ERROR_PARAM = 6,    
    /* e.g. file missing, corrupt, wrong type, parse error, etc */
    ERROR_FILE = 7,     
    /* e.g. XML parse error */
    ERROR_XML = 8,      
    /* e.g. Metadata read failure, metadata write failure. */
    ERROR_METADATA = 9  
};

/*****************************************************************************
** Notification IDs
******************************************************************************/
enum CALL_NOTIFICATIONS
{
    UNDERLAY_LOAD_RESPONSE = 0,
    THREAT_LOAD_RESPONSE   = 1,
    SYMBOL_LOAD_RESPONSE   = 2
};

/*****************************************************************************
** Output Channels
******************************************************************************/
enum CALLBACK_OUTPUT
{
    FS_ALL_MESSAGES = 0,
    FS_SET_NOTIFICATION = 1,
    FS_REPORT_ERROR_MESSAGE = 2,
    CSDM_TRACE = 3,
    CSDM_VERIFY = 4,
    FS_STATUS   = 5
};

enum FILE_LOAD_OBJECT
{
    DATAFRAME = 0
};

enum FILE_LOAD_STATE
{
    FILE_NOT_LOADED          = -1,
    FILE_LOAD_START          = 0,
    FILE_LOAD_COMPLETE       = 1,
    FILE_PROCESSING_START    = 2,
    FILE_PROCESSING_COMPLETE = 3
};

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 ** Initializes the Callback interface
 **
 ** Return:
 **   int - '1' if successful, otherwise '0'
 **
 *****************************************************************************/
int Initialize_Callback(void);

/*****************************************************************************
 ** Shuts down the Callback Interface
 *****************************************************************************/
void Shutdown_Callback(void);

/****************************************************************************
 ** Starts the TCP task at given priority.
 ** If you are not using callback TCP, you do not need to call this function
 **
 ** Input:
 **  nPriority - priority to start the TCP task at
 **
 ** Return:
 **  int - 1 if successful, otherwise 0
 ****************************************************************************/
int Callback_Start_TCP_Task(int nPriority);

/****************************************************************************
 ** Sets the port to use to send FliteScene responses to the map controller
 **
 ** Input:
 **   nPort     - Specifies response port
 **
 ** Return:
 **   int - '1' if successful, otherwise '0'
 ****************************************************************************/
int Set_Callback_FliteScene_Response_Port(int nPort);

/****************************************************************************
 ** Enables/Disables output to the stdout
 **
 ** Input:
 **   nFeature   - Specifies which interface(s) to send to stdout
 **                    0 : All callbacks
 **                    1 : FS_Set_Notification
 **                    2 : FS_Report_Error_Message
 **                    3 : CSDM_Trace
 **                    4 : CSDM_Verify
 **                    5 : FS_Report_Processing_Status
 **   nEnable    - 1 to enable feature to print to stdout, 0 to disable
 **
 ** Return:
 **   int - '1' if successful, otherwise '0'
 ****************************************************************************/
int Set_Callback_Stdout(int nFeature,
                        int nEnable);

/****************************************************************************
 ** Sets up TCP connections for console output. Console output can be echoed
 ** over a TCP socket, which can be accessed with a Telnet client.
 **
 ** Input:
 **   nFeature   - Specifies which interface(s) to set up
 **                    0 : All callbacks
 **                    1 : FS_Set_Notification
 **                    2 : FS_Report_Error_Message
 **                    3 : CSDM_Trace
 **                    4 : CSDM_Verify
 **                    5 : FS_Report_Processing_Status
 **   nPort - Specifies the TCP port to send messages through
 **
 ** Return:
 **   int - '1' if successful, otherwise '0'
 ****************************************************************************/
int Set_Callback_TCP_Console_Output(int nFeature,
                                    int nPort);


/****************************************************************************
 ** Waits for TCP connections to the TCP console to be established.
 ** Every console connection that has been setup with Set_Callback_TCP_Console_Output
 ** must be connected before this function returns.
 **
 ** Usefull for initializing callback prior to starting FliteScene to ensure
 ** all console output is recieved.
 ****************************************************************************/
void Callback_Wait_For_TCP_Console_Connection(void);

/****************************************************************************
 ** Specifies the full filename (including path) to log all callbacks
 ** for the given feature. This function with try to create the file, and
 ** erase the contents of the file.
 **
 ** Input:
 **   nFeature   - Specifies which interface(s) to specify
 **                    0 : All callbacks
 **                    1 : FS_Set_Notification
 **                    2 : FS_Report_Error_Message
 **                    3 : CSDM_Trace
 **                    4 : CSDM_Verify
 **                    5 : FS_Report_Processing_Status
 **   szFilename - filename including full path and null-terminator or 0
 **                NOTE: When this is 0, file output is disabled
 **                      All file output is disabled by default
 **
 ** Return:
 **   int - 1 when a file was created, 0 if the file was disabled or failed
 **
 ****************************************************************************/
int Set_Callback_File_Output(      int   nFeature,
                             const char* szFilename);

/****************************************************************************
 ** Sends response messages to the map controller
 **
 ** This function is called by FliteScene
 **
 ** Inputs:
 **   pHeader - Pointer to a FliteScene header data buffer
 **   pData   - Pointer to a FliteScene message buffer
 **
 ****************************************************************************/
void FS_Set_Response(const void * pHeader,
                     const void * pData);

/****************************************************************************
 ** Calls a response function to process and send the results back to the user.
 ** This function is called by FliteScene
 **
 ** This function is called by FliteScene
 **
 ** Inputs:
 **   nNotificationID - Notification IDs are provided above.
 **
 ****************************************************************************/
void FS_Set_Notification(int nNotificationID);

/****************************************************************************
 ** Processes error messages from FliteScene to user.
 **
 ** This function is called by FliteScene
 **
 ** Inputs:
 **   nCode     - Error code of error message
 **   szMessage - Null terminated text string containing information about
 **               the error being reported
 **
 ****************************************************************************/
void FS_Report_Error_Message(      int   nCode,
                             const char* szMessage);

/****************************************************************************
 ** Outputs the given text string to a debug device (such as a console or log
 ** file). On systems or builds where debug information is not needed, this
 ** function can be conditionally compiled to perform no operation.
 **
 ** This function is called by FliteScene
 **
 ** Inputs:
 **   szMessage - Null terminated text string to pass to debug console
 **
 ****************************************************************************/
void CSDM_Trace(const char* szMessage);

/****************************************************************************
 ** Outputs the given text string to a debug device (such as a console or log
 ** file). On systems or builds where debug information is not needed, this
 ** function can be conditionally compiled to perform no operation.  This
 ** is used verify FliteScene requirements
 **
 ** This function is called by FliteScene
 **
 ** Inputs:
 **   szMessage - Null terminated text string to pass to debug console
 **
 ****************************************************************************/
void FS_Verify(const char* szMessage);

/****************************************************************************
 ** Outputs the symbol type, state and the given text string to a debug device
 ** (such as a console or log file). On systems or builds where debug
 ** information is not needed, this function can be conditionally compiled
 ** to perform no operation.  This is used verify FliteScene requirements
 ** This function is called by FliteScene
 **
 ** Inputs:
 **   nChannel  - Channel processing is occurring on
 **   nObject   - enumeration based on the FliteScene symbol type
 **       0  - DataFrame (currently only one supported)
 **   nState    - state of object.
 **      -1  - File not loaded
 **       0  - File loading start
 **       1  - File loading complete
 **       2  - File processing start
 **       3  - File processing complete
 **   szMessage - Null terminated text string to pass to debug console
 **       Currently only contains filename
 **
 ****************************************************************************/
void FS_Report_Processing_Status(      int   nChannel,
                                       int   nObject,
                                       int   nState,
                                 const char* szMessage);

/****************************************************************************
 ** Starts up callback TCP task and sets port for FliteScene response messages.
 ** This message is provided for backwards compatability and
 ** is the is the same as calling:
 **   Set_Callback_FliteScene_Response_Port(nPort)
 **     and
 **   Callback_Start_TCP(nPriority)
 **
 ** Input:
 **   nPort     - Specifies TCP socket
 **   nPriority - Specifies the TCP thread running priority
 **
 ** Return:
 **   int - '1' if both operations are successful, otherwise '0'
 ****************************************************************************/
int Set_Callback_TCP_Output(int nPort,
                            int nPriority);

#ifdef __cplusplus
/* close extern "C" block */
}
#endif

#endif

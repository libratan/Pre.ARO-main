/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++ FliteScene Interface Source Code
++ FliteScene License holders are authorized to use this source code file 
++ for the purposes of integrating FliteScene with their software applications
++ in accordance with the license agreement.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
++ 
++ Copyright (C) Harris Corporation 2006, 2015-2017 - All Rights Reserved 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
++ FILE:              IF_Command.h
++
++ CLASSIFICATION:    Unclassified++
++
++ DESCRIPTION:
++
++      This file declares the Interface functions called by Main() in order
++      to initialize and shutdown this library.  These functions are 
++      implemented by the Command CSC.
++
++ LIMITATIONS: none
++
++ SOFTWARE HISTORY:
++
++  Refer to ClearCase for software history.
++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef _IF_COMMAND_H
#define _IF_COMMAND_H 1

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
** Starts up command interface.
**
**  Input:
**    UDP_Port_Number - Specifies UDP socket
**    TCP_Port_Number - Specifies TCP socket
**    UDP_Priority    - Specifies the UDP thread running priority
**    TCP_Priority    - Specifies the TCP thread running priority
**
**  Return:
**    int - '1' if successful, otherwise '0'
**
******************************************************************************/
int Initialize_Command(int UDP_Port_Number,
                       int TCP_Port_Number,
                       int UDP_Task_Priority,
                       int TCP_Task_Priority);

/******************************************************************************
** Ends interface tasks.
**
******************************************************************************/
void Shutdown_Command(void);

#ifdef __cplusplus
} //end extern "C"
#endif

#endif

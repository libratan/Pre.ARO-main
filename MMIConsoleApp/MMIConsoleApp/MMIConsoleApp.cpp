//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: MMIConsoleApp.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for MMI display
// This file contains the 'main' function. Program execution begins and ends there.
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../MMIConsoleApp.h>
#include <../PAGE/header/PAGE_pageMgr.h>
#include <../../MSG/header/Deserializer.h>

using namespace Network;
using namespace MMIConsoleFunction;

//****************************************************************************
//* Function Name  : int UDPThreadStarter()
//* Purpose        : Start the UDP thread
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
static INT MMIConsoleFunction::udpthreadstarter()
{
    //JSF Rule 257 exception handling not allowed
    //the try catch block was removed 
    //JSF Rule 142 and Rule51
    //This was not used: WSASession session;

    //JSF rule 51 begin with lower case
    UDPSocket socketobj; //socket instance
    Deserializer deserializerobj; //deserializer instance
    const INT buffsize = 1024; //buffer size
    CHAR buffer[buffsize]; //to hold a buffer string
    const USHORT udpconfigport = 5000; //previous sDisplay_config.UDP_config.port read value is 5000
    const string ipaddress = "224.0.0.51"; //previous sDisplay_config.UDP_config.ip_address value "224.0.0.51"

    //JSF rule disallow passing of array buffer memset original code
    //Instead do a for loop initialiazation instead
    for (INT16 i = 0; i < buffsize; i++)
    {
        buffer[i] = 0;
    }

    socketobj.udpClientBind(CONNECT_TYPE::UDP_MULTICAST, 
        ipaddress, 
        udpconfigport);

    //JSF - no wide strings allowed modify OutputDebugString(L"xxx") to
    OutputDebugStringA("UDP is listening.\n");

    while (1)
    {
        UINT32 msglen = socketobj.Listen(buffer); //receive msg len
        if (msglen > 0)//process if got message
        {
            deserializerobj.processMessage(buffer, msglen);
        }
    }

    return 1;
}

//****************************************************************************
//* Function Name  : StartUDPThread()
//* Purpose        : Creates thread for UDP client
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
static void MMIConsoleFunction::startudphread()
{
    const SIZE_T stacksize = 40960; //stack size
       
    //JSF RULE 175 NULL disallowed
    //So NULLs CreateThread parameters replace by 0s 
    //JSF 185/182 type casting from pointers not allowed
    //C style cast not allowed, change to C++ style of casting 
    HANDLE hUDPThread = 
        CreateThread(0, stacksize, reinterpret_cast<LPTHREAD_START_ROUTINE> (udpthreadstarter), 0, 0, 0);


    if (hUDPThread == 0)
    {
        //JSF - no wide strings allowed modify OutputDebugString(L"xxx") to
        OutputDebugStringA("Unable to start UDP Thread!\n");
        
        //JSF Rule 113 - No multiple exit points
        //Original code to be deleted: return;
    }
    else
    {   //JSF - no wide strings allowed modify OutputDebugString(L"xxx\n") to
        OutputDebugStringA("UDP thread started.\n");
    }
}

//****************************************************************************
//* Function Name  : main()
//* Purpose        : This is the main entry point for execution of the MMI
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
INT main(void)
{
    // Create frame rate timer
    LARGE_INTEGER liDueTime;          //declare for setwaitTimer
    liDueTime.QuadPart = 0;
    const LONG period_30ms = 30;      //30 ms period
    const DWORD waitfail = 0xFFFFFFFF; //single object wait fail constant
    HANDLE hTimer = CreateWaitableTimer(0, FALSE, 0);
    
    DWORD status1 = waitfail; //capture status of waitforsingle object function   
    PAGE::PageMgr* pageMgr = PAGE::PageMgr::getInstance(); //pageMgr as a handle to reference for PageMGR
    
    //JSF 174 - need to check that pointer is not null before using
    if (pageMgr != 0) 
    { 
        pageMgr->doEndInit();
    }

    // Set timer to 33 Hz (30ms frame period)
    INT status = SetWaitableTimer(hTimer, &liDueTime, period_30ms, 0, 0, 0);//capture status of setwaittimer
    
    //TODO: To do a connection class to handle TCP/UDP connection
    // Start UDP client 
    MMIConsoleFunction::startudphread();

    // Render Loop
    while (1)
    {
        status1 = WaitForSingleObject(hTimer, INFINITE); //capture status of wait single object
        // Wait for the timer to signal
        pageMgr->execute();
    }
    
    // collate statuses
    //if setwaittimer fails or waitforsingleobject fails
    //overall status is failed
    if ((status == 0) || (status1 == waitfail))
    { //if there is file read errors or wait errors, overall status is fail
        status = 0;
    }

    return status; //0 - fail, 1 - success
}

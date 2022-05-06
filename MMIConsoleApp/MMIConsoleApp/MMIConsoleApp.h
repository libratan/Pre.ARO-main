//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: MMIConsoleApp.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for MMI display
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef MMICONSOLEAPP_H
#define MMICONSOLEAPP_H

#include <../../DMM/header/Network.h>


//*****************************************************************************
// Class and namespace Definitions
//*****************************************************************************
namespace MMIConsoleFunction
{
 //****************************************************************************
//* Function Name  : StartUDPThread()
//* Purpose        : Creates thread for UDP client
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
    static void startudphread(void);

//****************************************************************************
//* Function Name  : int UDPThreadStarter()
//* Purpose        : Start the UDP thread
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
    static INT udpthreadstarter(void);   
};


#endif
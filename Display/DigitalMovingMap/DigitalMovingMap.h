//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: DigitalMovingMap.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for digital map display
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef DIGITALMOVINGMAP_H
#define DIGITALMOVINGMAP_H

#include <../Resource.h>
#include <../structs.h>

#define MAX_LOADSTRING 100

//*****************************************************************************
// Class Definitions
//*****************************************************************************
namespace DMMControl
{
    void getDisplayConfig();
    int  CreateOpenGL_Context();
    int  initFSCallback();
    void SetFSStartup();
    void StartUDPThread(void);
    int UDPThreadStarter(void);

    /*extern int nInitialized;
    extern int nRendering;
    extern int nFrameWidth;
    extern int nFrameHeight;
    extern HDC hDevice;
    extern HGLRC hContext;

    extern DISPLAY_CONFIG sDisplay_config;
    */
};


//*****************************************************************************
// Global application data
//*****************************************************************************
//extern HINSTANCE hInst;                                // current instance
extern WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
extern WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

extern int nInitialized;
extern int nRendering;
extern int nFrameWidth;
extern int nFrameHeight;
extern HDC hDevice;
extern HGLRC hContext;

extern DISPLAY_CONFIG sDisplay_config;

/*
void getDisplayConfig();

int CreateOpenGL_Context();

int initFSCallback();

void SetFSStartup();

void StartUDPThread(void);
int UDPThreadStarter(void);
*/

#endif
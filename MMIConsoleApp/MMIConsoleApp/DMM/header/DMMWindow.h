//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: DMMWindow.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for DMM Window
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************

#ifndef DMMWINDOW_H
#define DMMWINDOW_H

#pragma once

#include <../DMM/header/FS_Comm.h>
#include <Windows.h>

class DMMWindow {

    DMMWindow()
    {
    }

    ~DMMWindow()
    {
    }

public:
    static int WindowThreadStarter(void* pParam);
    static void StartWindowThread(void);
    static LRESULT WINAPI WindowMessagePump(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#endif // !DMMWINDOW_H
#pragma once

#include "resource.h"

class Window {

    Window()
    {
    }

    ~Window()
    {
    }

public:
    //unsigned long __stdcall 
    static int WindowThreadStarter(void* pParam);
    static void StartWindowThread(void);

    static LONG WINAPI WindowMessagePump(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


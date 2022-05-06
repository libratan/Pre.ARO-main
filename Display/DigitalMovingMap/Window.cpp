// This file creates the Window thread. 

#include "framework.h"
#include "Window.h"
#include "DigitalMovingMap.h"
#include "FS_Comm.h"
#include "FS_Functions.h"
#include <stdio.h>
#include <Windows.h>

#include "Test_Constants.h"

#include "XmlSerializer.h"


#define MAX_LOADSTRING 100

//*********************************************************************************************************************
// This function calls the default window procedure to provide default processing for any window messages 
// that an application does not process.  Also handles keypress inputs.
// Required to create WIN32 Window.
//*********************************************************************************************************************
LONG WINAPI Window::WindowMessagePump(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CHAR:
        switch (wParam)
        {
        case 's':
            // Map Status Request
            FS_Comm::SendMsg_Get_Status(0);
            Sleep(500);
            break;
        case '-':
            // Zoom out
            MapZoom::ZoomOut();
            Sleep(100);
            break;
        case '=':
            // Zoom in
            MapZoom::ZoomIn();
            Sleep(100);
            break;
        case '[':
            // Increase map scale
            MapScale::DecreaseMapScale();
            Sleep(100);
            break;
        case ']':
            // Increase map scale
            MapScale::IncreaseMapScale();
            Sleep(100);
            break;
        default:
            printf("the '%c' key was pressed\n", wParam);
            break;
        }
        break;
    case WM_KEYDOWN:
        // Arrow and Function Keys
        switch (wParam)
        {
        case VK_ESCAPE:
            // Esc key
            // Ends render loop and closes application.
            nRendering = 0;
            break;
        default:
            break;
        }
        break;
    case WM_CLOSE:
        // This sets the global variable which ends the rendering loop
        nInitialized = 0;
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

void Window::StartWindowThread()
{
    HANDLE hThread = 0;

    // Spawn the task that creates the Window
    hThread = CreateThread(NULL, 40960, (LPTHREAD_START_ROUTINE)WindowThreadStarter, 0, 0, NULL);

    if (hThread == 0)
    {
        printf("Unable to start Window Thread!\n");
        return;
    }
}


//*********************************************************************************************************************
// This creates the window and starts the message pump.
//*********************************************************************************************************************
//unsigned long __stdcall 
int Window::WindowThreadStarter(void* pParam)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WCHAR szClassName[MAX_LOADSTRING];            // the main window class name

    LoadStringW(hInstance, IDC_DIGITALMOVINGMAP, szClassName, MAX_LOADSTRING);

    // Define Window
    WNDCLASS wcex;

    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = (WNDPROC)WindowMessagePump;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szClassName;
    
    RegisterClass(&wcex);

    HWND hWnd = CreateWindow( szClassName, 
                              szClassName, 
                              WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                              0, // X Offset
                              0, // Y Offset
                              nFrameWidth, 
                              nFrameHeight,
                              NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return false;
    }

    // Get the device handle
    hDevice = GetDC(hWnd);

    // Set the pixel format (minimum requirements for the app to work)
    int pf = 0;
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize           = sizeof(pfd);
    pfd.nVersion        = 1;
    pfd.dwFlags         = PFD_DRAW_TO_WINDOW |
                          PFD_SUPPORT_OPENGL |
                          PFD_DOUBLEBUFFER;
    pfd.iPixelType      = PFD_TYPE_RGBA;
    pfd.cColorBits      = 32;
    pfd.cRedBits        = 8;
    pfd.cGreenBits      = 8;
    pfd.cBlueBits       = 8;
    pfd.cAlphaBits      = 8;
    pfd.cDepthBits      = 32;
    pfd.cStencilBits    = 8;
    pf = ChoosePixelFormat(hDevice, &pfd);
    SetPixelFormat(hDevice, pf, &pfd);
    DescribePixelFormat(hDevice,
                        pf,
                        sizeof(PIXELFORMATDESCRIPTOR),
                        &pfd);

    // Release the device context so that another thread can use it
    ReleaseDC(hWnd, hDevice);

    // Make the window visible
    ShowWindow(hWnd, SW_SHOWNORMAL);

    // Set the Initialized flag so the main thread know we are done.
    nInitialized = 1;

    // Start the Windows Message Pump
    MSG msg;
    printf("Windows thread complete.\n");

    // Main message loop:
    while (GetMessage(&msg, hWnd, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}



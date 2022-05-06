//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: DMMWindow.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for DMM Window
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************

#include <../DMM/header/DMMWindow.h>

extern HWND DMM_WINDOW;
extern HWND MAIN_WINDOW;

int nInitialized = 0;
int nRendering = 1;
int nFrameWidth = 0;
int nFrameHeight = 0;
HDC hDevice;
HGLRC hContext;
bool mousedown = false;
POINT lastLocation = { 0, 0 };

//****************************************************************************
//* Function Name  : WindowMessagePump()
//* Purpose        : This function calls the default window procedure to provide default processing for any window messages 
//*                  that an application does not process.  Also handles keypress inputs.
//                   Required to create WIN32 Window.
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
LRESULT WINAPI DMMWindow::WindowMessagePump(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_LBUTTONDOWN: {
        mousedown = true;
        GetCursorPos(&lastLocation);

        FS_Comm::SendMsg_OverlaySelect(0, 1, FS_Constants::SLEW_SYMBOL);
        break;
    }
    case WM_LBUTTONUP: {
        mousedown = false;
        break;
    }
    case WM_MOUSEMOVE: 
        if (mousedown) {
            POINT currentpos;
            GetCursorPos(&currentpos);
            int x = currentpos.x - lastLocation.x;
            int y = currentpos.y - lastLocation.y;
            
            //TODO: To recalculate the Modulation factor with actual display
            //Modulate the different by 10, to minimise slew change
            x = x /(-10);
            y = y / 10;

            // Slew up by 10 away in both directions from the center of the screen.
            FS_Comm::SendMsg_Slew(0, // Channel to send to 
                0, // Slew Heading Enable/Disable
                0.0, // Slew Angle relative to ownship/True North depending on if Use North Up is set.
                1, // Slew Position Enable
                0, // Slew Position Type (0: Screen Location, 1: Geo Location)
                x, // Slew in X direction (if Screen Location, distance away from screen center)
                y); // Slew in Y Direction (if Geo Location, coordiantes in lat, lon)
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
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//****************************************************************************
//* Function Name  : StartWindowThread()
//* Purpose        : This spawn a separate thread for DMM Window
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void DMMWindow::StartWindowThread()
{
    const SIZE_T stacksize = 40960; //stack size
    // Spawn the task that creates the Window
    HANDLE hThread = CreateThread(0, stacksize, reinterpret_cast<LPTHREAD_START_ROUTINE> (WindowThreadStarter), 0, 0, 0);

    if (hThread == 0)
    {
        OutputDebugString(L"Unable to start DMM Window Thread!\n");
        return;
    }
}

//****************************************************************************
//* Function Name  : WindowThreadStarter()
//* Purpose        : This creates the window and starts the message pump.
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
int DMMWindow::WindowThreadStarter(void* pParam)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
   
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
    wcex.lpszClassName = L"DMM";

    RegisterClass(&wcex);

    DMM_WINDOW = CreateWindowEx(0,
        L"DMM",
        L"DMM",
        WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS,
        0, // X Offset
        0, // Y Offset
        1280,
        800,
        MAIN_WINDOW, NULL, hInstance, NULL);

    if (!DMM_WINDOW)
    {
        return false;
    }
    
    SetWindowPos(DMM_WINDOW, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    // Get the device handle
    hDevice = GetDC(DMM_WINDOW);

    // Set the pixel format (minimum requirements for the app to work)
    int pf = 0;
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 32;
    pfd.cStencilBits = 8;
    pf = ChoosePixelFormat(hDevice, &pfd);
    SetPixelFormat(hDevice, pf, &pfd);
    DescribePixelFormat(hDevice,
        pf,
        sizeof(PIXELFORMATDESCRIPTOR),
        &pfd);

    // Release the device context so that another thread can use it
    ReleaseDC(DMM_WINDOW, hDevice);

    // Set the Initialized flag so the main thread know we are done.
    nInitialized = 1;

    // Start the Windows Message Pump
    MSG msg;
    OutputDebugString(L"DMM thread complete.\n");

    // Main message loop:
    while (GetMessage(&msg, DMM_WINDOW, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
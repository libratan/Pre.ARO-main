//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved
//
// FILE NAME: PAGE_HSDMapPage.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for HSD Page
//
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              :
//   MODIFIER          :
//   MODIFICATION      :
//
//******************************************************************************
#include <../PAGE/header/PAGE_HSDMapPage.h>
#include <../DMM/header/FliteScene.h>
#include <../DMM/header/IF_Callback.h>
#include <../DMM/header/IF_Command.h>
#include <../DMM/header/FS_Comm.h>
#include <../DMM/header/CallbackServer.h>
#include <../DMM/header/DMMWindow.h>
#include <../DMM/header/MapTactical.h>
#include <../DMM/header/MapZoom.h>
#include <../DMM/header/MapScale.h>
#include <direct.h>

extern HWND MAIN_WINDOW;
extern HWND DMM_WINDOW;
extern HWND BUTTON_TOP[10];
extern HWND BUTTON_LEFT[4];
extern HWND BUTTON_RIGHT[4];
extern HWND BUTTON_BOTTOM[10];
extern HWND MSGBOX;
extern std::vector<HWND> BUTTON_KEYBOARD_NUMBERS;
extern std::vector<HWND> BUTTON_KEYBOARD_ALPHABET;
extern HWND BUTTON_KEYBOARD_BACKSPACE;
extern HWND BUTTON_KEYBOARD_PERIOD;
extern HWND BUTTON_KEYBOARD_SPACE;
extern HWND BUTTON_KEYBOARD_ENTER;
extern DISPLAY_CONFIG sDisplay_config;

namespace PAGE {
    //****************************************************************************
    //* Function Name  : int CreateOpenGL_Context()
    //* Purpose        : Starts Win32 Window and and creates an OpenGL context.
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    int CreateOpenGL_Context()
    {
        nInitialized = 0;
        //JSF disallowed JSF 143
        //HANDLE hThread = 0;
        //unsigned long ulExitCode = 0;
        const DWORD sleep_time1 = 1; //1 ms sleep time

        DMMWindow::StartWindowThread();

        // Sleep while the initialization completes
        while (nInitialized != 1)
        {
            Sleep(sleep_time1);
        }

        // Get the OpenGL context and make it current
        hContext = wglCreateContext(hDevice);
        BOOL status = wglMakeCurrent(hDevice, hContext); //receive status of make current
        return status;
    }

    //****************************************************************************
    //* Function Name  : int initFSCallback()
    //* Purpose        : Initiates Callback server and log files.
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    int initFSCallback()
    {
        INT status = 0;    //variable to hold statuses of call backs
        const INT portno7046 = 7046; //port no 7046
        const INT portno23 = 23;  //port no 23
        const INT feature1 = 1;  //feature 1 for callback
        const INT feature2 = 2;  //feature 2 for callback
        const INT feature3 = 3;  //feature 3 for callback
        const INT feature4 = 4;  //feature 4 for callback
        const INT priority10 = 10; //priority 10 to start task

        // Configure Callback Ethernet port (outgoing)
        status = Initialize_Callback();
        status = Set_Callback_FliteScene_Response_Port(portno7046);
        CallbackServer::startCallbackServerThread();

        // Check if Logs folder exists, if not create one.
        if (_mkdir("./Logs") == -1)
        {
            //JSF Rule 17 discourage the use of errno, the logic below removed
            //if errno EEXIST then  OutputDebugString(L"Logs folder already exists.\n")
            //else OutputDebugString(L"Logs folder already exists.\n")
            //instead just ouput below
            //
            // Error in creating folder
            OutputDebugString(L"Error creating Logs folder.\n");
        }
        else
        {
            // Folder created
            OutputDebugString(L"Logs folder created.\n");
        }

        // Send notification messages to file
        status = Set_Callback_File_Output(feature2, "./Logs/Callback_Notification_Log.txt");

        // Send error messages to file
        status = Set_Callback_File_Output(feature2, "./Logs/Callback_Error_Log.txt");

        // Send trace messages to file
        status = Set_Callback_File_Output(feature3, "./Logs/Callback_Trace_Log.txt");

        // Send verify messages to file
        status = Set_Callback_File_Output(feature4, "./Logs/Callback_Verify_Log.txt");

        // Send Error and Trace messages to TCP port 23
        status = Set_Callback_TCP_Console_Output(feature2, portno23);
        status = Set_Callback_TCP_Console_Output(feature3, portno23);

        // Do not send logged messages to stdout
        // (All other output streams will be sent to stdout by default)
        status = Set_Callback_Stdout(feature1, 0);
        status = Set_Callback_Stdout(feature2, 0);
        status = Set_Callback_Stdout(feature3, 0);
        status = Set_Callback_Stdout(feature4, 0);
        //Set_Callback_Stdout(0, 0);

        // Start the TCP task for the TCP console and FliteScene responses
        status = Callback_Start_TCP_Task(priority10);

        // Wait for a client to connect to the TCP console
        Callback_Wait_For_TCP_Console_Connection();

        return status;
    }

    //****************************************************************************
    //* Function Name  : void SetFSStartup()
    //* Purpose        : Send commands to FliteScene to define display mode.
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void SetFSStartup()
    {
        // This is currently hardcoded to define the startup map display.
        FS_Comm::SendMsg_Mode(0,    // Channel
            0,    // Mode - 0 for 2D, 1 for 3D
            "Q1", // Underlay Product Code defined in CONFIG_DIRECTORY.XML - "Q1" for Geotiff 4km
            0.0); // Range - Distance in nautical miles from top to bottom of the Map Window viewport.  Only applicable in 2D.

        // Define and show ownship startup location.
        // Enable vehicle overlay
        FS_Comm::SendMsg_OverlaySelect(0, 1, FS_Constants::VEHICLE_SYMBOL);

        // Enable vehicle symbol
        FS_Comm::SendMsg_VehicleEnables(0, FS_Constants::VEHICLE_1, FS_Constants::SENSOR_1, 1, FS_Constants::ENABLE_VEHICLE);

        // Set icon/symbol to display for Ownship
        FS_Comm::SendMsg_VehicleIcon(0, FS_Constants::VEHICLE_1, 0, "#DEVICE0/ICON/C130.ico");

        // Turn on overlays for symbols to be displayed
        MapTactical::SetMapTacticalOverlays();
    }

    //****************************************************************************
    //* Function Name  : void HSDMapPage()
    //* Purpose        : Constructor
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    HSDMapPage::HSDMapPage(void)
    {
    }

    //****************************************************************************
    //* Function Name  : void ~HSDMapPage()
    //* Purpose        : Destructor
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    HSDMapPage::~HSDMapPage(void)
    {
    }

    //****************************************************************************
    //* Function Name  : void doEndInit()
    //* Purpose        : Do end of initialzation
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void HSDMapPage::doEndInit(void)
    {
        // Declare Local Variables
        errno_t err;
        FILE* pFile = 0;
        char* pConfigBuffer = new char[100000]; // For Directory Config file

        // Read in the XML Configuration file
        err = fopen_s(&pFile, "CONFIG_DIRECTORY.XML", "r");
        fread(pConfigBuffer, 1, 100000, pFile);
        fclose(pFile);

        // Initialize and configure FS Callback
        initFSCallback();

        // Configure Message Ethernet ports (Incoming)
        Initialize_Command(7044,  // UDP port number
            7042,  // TCP port number
            100,   // UDP priority
            100);  // TCP priority

        // Initialize FliteScene
        FS_Initialize_Map(pConfigBuffer);

        // Wait until FliteScene initialization is complete
        while (FS_Get_Channel_Count() <= 0)
            Sleep(500);

        // Get the viewport dimensions from FliteScene. Only 1 channel (0)
        FS_Get_Viewport_Size(0, &nFrameWidth, &nFrameHeight);

        //Create OpenGL context
        CreateOpenGL_Context();

        // Initialize Video Memory
        FS_Initialize_Graphics(0); // Only 1 channel (0)

        // Notify FliteScene that graphics initialization is complete,
        // finish allocating all dynamic memory, and spawn the FliteScene tasks.
        FS_Finish_Initialization(1);
        OutputDebugString(L"DebugString: FS_Finish_Initialization completed.\n");

        // Setup Flitescene startup messages
        SetFSStartup();

        delete[] pConfigBuffer;
    }

    //****************************************************************************
    //* Function Name  : void managePage()
    //* Purpose        : Manage Page refresh and rendering
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void HSDMapPage::managePage()
    {
        // Render Loop - START
        // Swap buffer
        SwapBuffers(hDevice);
        // Set the device context for a channel.
        wglMakeCurrent(hDevice, hContext);
        // Clear the frame buffer
        FS_Clear_Screen(0);
        // Render scene.
        FS_Render(0);
        // Render Loop - ENDS

        // draw legends, mnenonics and PXLs
        displayStatus();

        // draw symbols
        displaySymbol();
    }

    //****************************************************************************
    //* Function Name  : showRequiredWindows()
    //* Purpose        : Show/Hide required Windows
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void HSDMapPage::showRequiredWindows()
    {
        ShowWindow(DMM_WINDOW, SW_SHOW);

        ShowWindow(BUTTON_TOP[0], SW_SHOW);
        ShowWindow(BUTTON_TOP[1], SW_HIDE);
        ShowWindow(BUTTON_TOP[2], SW_HIDE);
        ShowWindow(BUTTON_TOP[3], SW_HIDE);
        ShowWindow(BUTTON_TOP[4], SW_HIDE);
        ShowWindow(BUTTON_TOP[5], SW_HIDE);
        ShowWindow(BUTTON_TOP[6], SW_HIDE);
        ShowWindow(BUTTON_TOP[7], SW_HIDE);
        ShowWindow(BUTTON_TOP[8], SW_HIDE);
        ShowWindow(BUTTON_TOP[9], SW_SHOW);

        ShowWindow(BUTTON_BOTTOM[0], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[1], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[2], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[3], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[4], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[5], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[6], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[7], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[8], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[9], SW_HIDE);

        ShowWindow(BUTTON_LEFT[0], SW_SHOW);
        ShowWindow(BUTTON_LEFT[1], SW_SHOW);
        ShowWindow(BUTTON_LEFT[2], SW_SHOW);
        ShowWindow(BUTTON_LEFT[3], SW_HIDE);

        ShowWindow(BUTTON_RIGHT[0], SW_SHOW);
        ShowWindow(BUTTON_RIGHT[1], SW_SHOW);
        ShowWindow(BUTTON_RIGHT[2], SW_SHOW);
        ShowWindow(BUTTON_RIGHT[3], SW_HIDE);

        ShowWindow(MSGBOX, SW_HIDE);
        for (HWND handle : BUTTON_KEYBOARD_NUMBERS)
        {
            ShowWindow(handle, SW_HIDE);
        }
        for (HWND handle : BUTTON_KEYBOARD_ALPHABET)
        {
            ShowWindow(handle, SW_HIDE);
        }
        ShowWindow(BUTTON_KEYBOARD_BACKSPACE, SW_HIDE);
        ShowWindow(BUTTON_KEYBOARD_PERIOD, SW_HIDE);
        ShowWindow(BUTTON_KEYBOARD_SPACE, SW_HIDE);
        ShowWindow(BUTTON_KEYBOARD_ENTER, SW_HIDE);
    }

    //****************************************************************************
    //* Function Name  : void displaySymbol()
    //* Purpose        : Redraw of symbols
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void HSDMapPage::displaySymbol()
    {
        PageControlMgr::sendMessageToScreenToDrawSymbols();
    }


    void HSDMapPage::processOsb1Legend()
    {
        ShowWindow(BUTTON_RIGHT[0], SW_SHOW);

        //check states for OSB 1
        //and update outgoing structures
    }

    void HSDMapPage::processOsb2Legend()
    {
        //check states for OSB 2
        //and update outgoing structures
    }

    void HSDMapPage::processOsb3Legend()
    {
    }

    void HSDMapPage::processOsb4Legend()
    {
    }

    void HSDMapPage::processOsb5Legend()
    {
    }

    void HSDMapPage::processOsb6Legend()
    {
    }

    void HSDMapPage::processOsb7Legend()
    {
    }

    void HSDMapPage::processOsb8Legend()
    {
    }

    void HSDMapPage::displayStatus()
    {

        processOsb1Legend();

        processOsb2Legend();

        processOsb3Legend();

        processOsb4Legend();

        processOsb5Legend();

        processOsb6Legend();

        processOsb7Legend();

        processOsb8Legend();

        processAndShowImportantStrings();

        //draw OSB legends
        PageControlMgr::sendMessageToScreenToDrawOsbLegends();

    }

    //****************************************************************************
    //* Function Name  : BOOL handleR1()
    //* Purpose        : Handle OSB R1 functions, override Parent Class
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    BOOL HSDMapPage::handleR1()
    {
        //handle what happens when OSB is pressed
        // Zoom out
        MapZoom::ZoomOut();
        //record / log action
        return FALSE;
    }

    //****************************************************************************
    //* Function Name  : BOOL handleR2()
    //* Purpose        : Handle OSB R2 functions, override Parent Class
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    BOOL HSDMapPage::handleR2()
    {
        //handle what happens when OSB is pressed
        // Map Status Request
        FS_Comm::SendMsg_Get_Status(0);

        //Placeholder only - To be redesign to other button for disabling slew and centre to A/C position
        // Display the Slew Symbol to see where the center of the screen is
        FS_Comm::SendMsg_OverlaySelect(0, 0, FS_Constants::SLEW_SYMBOL);


        // Slew up by 10 away in both directions from the center of the screen.
        FS_Comm::SendMsg_Slew(0, // Channel to send to
            0, // Slew Heading Enable/Disable
            0.0, // Slew Angle relative to ownship/True North depending on if Use North Up is set.
            0, // Slew Position Enable
            0, // Slew Position Type (0: Screen Location, 1: Geo Location)
            0, // Slew in X direction (if Screen Location, distance away from screen center)
            0); // Slew in Y Direction (if Geo Location, coordiantes in lat, lon)

        //record / log action
        return FALSE;
    }

    //****************************************************************************
    //* Function Name  : BOOL handleR3()
    //* Purpose        : Handle OSB R3 functions, override Parent Class
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    BOOL HSDMapPage::handleR3()
    {
        //handle what happens when OSB is pressed
        // Zoom in
        MapZoom::ZoomIn();
        //record / log action
        return FALSE;
    }

    //****************************************************************************
    //* Function Name  : BOOL handleB1()
    //* Purpose        : Handle OSB B1 functions, override Parent Class
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    BOOL HSDMapPage::handleB1()
    {
        //switch to HSD page
        HSDMapPage::setMasterPageIndex(static_cast<unsigned short>(HSDMAP_PAGE));
        //FS_Comm::SendMsg_Mode(0,    // Channel
        //    0,    // Mode - 0 for 2D, 1 for 3D
        //    "Q2", // Underlay Product Code defined in CONFIG_DIRECTORY.XML - "Q1" for Geotiff 4km
        //    0.0); // Range - Distance in nautical miles from top to bottom of the Map Window viewport.  Only applicable in 2D.

            // Move to a scale where we can see the Local Point symbols better
        FS_Comm::SendMsg_Mode(0, FS_Constants::PLAN_VIEW, "JN", 0.0);
        //Enable Range Ring Symbols and Range Ring Labels
        FS_Comm::SendMsg_OverlaySelect(0, 1, FS_Constants::RANGE_RING_SYMBOL);
        FS_Comm::SendMsg_OverlaySelect(0, 1, FS_Constants::RANGE_RING_LABEL);

        //Create Range Ring Symbol
        FS_Comm::SendMsg_SetRangeRingSymbol(-1,     //Create new Range Ring Symbol
            0,      //Key to identify the caller when Set Object Response Message is sent.
            0,      //Range Ring Definition
            0,      //Range Ring Center Point index (2 => Pin to Lat/Lon)
            0,   //Latitude
            0, //Longitude
            0,      //Center Point UID (used if Range Ring Definition = 3)
            0,      // Screen X
            0);     // Screen Y

        //TODO: Due to change of Map Scale - Adjust the Zoom Level to correct size for Range Ring
        FS_Comm::SendMsg_Zoom(0, // Channel to send to
            4); // Zoom scale. (> 1.0: zoom in, < 1.0: zoom out)

        return FALSE;
    }

    //****************************************************************************
    //* Function Name  : BOOL handleB2()
    //* Purpose        : Handle OSB B2 functions, override Parent Class
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    BOOL HSDMapPage::handleB2()
    {
        //switch to MAP page
        HSDMapPage::setButtonPressedData(static_cast<unsigned short>(HSDMAP_PAGE));
        FS_Comm::SendMsg_Mode(0,    // Channel
            0,    // Mode - 0 for 2D, 1 for 3D
            "Q1", // Underlay Product Code defined in CONFIG_DIRECTORY.XML - "Q1" for Geotiff 4km
            0.0); // Range - Distance in nautical miles from top to bottom of the Map Window viewport.  Only applicable in 2D.

        return FALSE;
    }

    //****************************************************************************
    //* Function Name  : BOOL handleL1()
    //* Purpose        : Handle OSB L1 functions, override Parent Class
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    BOOL HSDMapPage::handleL1()
    {
        MapScale::IncreaseMapScale();
        return FALSE;
    }

    //****************************************************************************
    //* Function Name  : BOOL handleL3()
    //* Purpose        : Handle OSB L3 functions, override Parent Class
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    BOOL HSDMapPage::handleL3()
    {
        MapScale::DecreaseMapScale();
        return FALSE;
    }

    void HSDMapPage::processAndShowImportantStrings()
    {
        //implementation to draw special text
    }
}
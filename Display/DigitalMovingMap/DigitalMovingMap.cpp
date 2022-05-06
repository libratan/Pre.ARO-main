//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: DigitalMovingMap.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for digital map display
//
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
//JSF disallowed, change "" to relave paths. JSF rule 33
//JSF Rule 37 - only relevant header files included 
#include <../framework.h>

#include <../DigitalMovingMap.h>
#include <../Network.h>
#include <../Window.h>
#include <../include/FliteScene.h>
#include <../include/IF_Callback.h>
#include <../include/IF_Command.h>

//JSF Rule 37 - only relevant header files included
//Reserved for future  : #include <../include/IF_File_Services.h>

#include <../FS_Comm.h>
#include <../CallbackServer.h>

//JSF: include to resolve JSF type def issues - future use
//JSF Rule 37 - only relevant header files included
//Resreved for future :# include <../Type_Def.h>

//JSF disallowed stdio.h. JSF rule 22
//To be deleted: #include <stdio.h>

#include <sys/stat.h>
#include <direct.h>
#include <string.h>
#include <../structs.h>
#include <../XmlSerializer.h>
#include <../Deserializer.h>
#include <../Vehicle.h>
#include <../MapTactical.h>

#include <../Test_Constants.h>

using namespace Network;

// Global Variables:
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

int nInitialized = 0;
int nRendering = 1;
int nFrameWidth = 0;
int nFrameHeight = 0;
HDC hDevice = 0;
HGLRC hContext = 0;

// Global struct to contain display config info.
DISPLAY_CONFIG sDisplay_config;


//JSF Requirement: JSF Rule 134 
//This is the main entry point for execution of the map
//JSF disallowed. JSF Rule 98 and 97. 
// argv the passing of array argument
//int main(int argc, char* argv[])
//changed to main(int argc, const char* argv[]) with const specifier to argv[]
//JSF Rule 97 - Array not to be used in interfaces, so passed in as void
//Original code: int main(int argc, const char* argv[])
//****************************************************************************
//* Function Name  : main()
//* Purpose        : This is the main entry point for execution of the map
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
//
int main(void)
{  
    
    //JSF 151 remove use of literal constants throughout
    // Declare Local Variables and constants
    FILE* pFile = 0; //file pointer
    const LONG max_buffer_size = 100000; //max buffer size for config file
    LARGE_INTEGER liDueTime;             //declare for setwaitTimer
    liDueTime.QuadPart = 0;
    const LONG period_30ms = 30;      //30 ms period
    const INT32 udp_port_no    = 7044; //udp port no
    const INT32 tcp_port_no    = 7042; //tcp port no
    const INT32 udp_priority   = 100;  //udp priority no
    const INT32 tcp_priority   = 100;  //tcp priority no
    const DWORD sleep_time500  = 500;  //sleep time of 500 seconds 

    //JSF disallowed unused variables. JSF Rule 143.
    //to delete this int i = 0;

    
    //char* pConfigBuffer = new char[max_buffer_size]; // For Directory Config file
    CHAR pConfigBuffer[max_buffer_size];

    // Create frame rate timer
    
    //JSF Rule 175 change NULL to 0
    HANDLE hTimer = CreateWaitableTimer(0, FALSE, 0);

    // Update struct with DMM config information - Display_Config.xml
    DMMControl::getDisplayConfig();
   

    // Set timer to 33 Hz (30ms frame period)
    //JSF Rule 175 change NULL to 0
    INT status = SetWaitableTimer(hTimer, &liDueTime, period_30ms, 0, 0, 0); //success status 

    // Read in the XML Configuration file
    INT filestatus = fopen_s(&pFile, sDisplay_config.FS_config_path.c_str(), "r"); //file status 0 - success
    if (filestatus == 0)
    {
        if (fread(pConfigBuffer, 1, max_buffer_size, pFile) > 0)
        {
            filestatus = 0;
        }
        filestatus = fclose(pFile); //caputure close status
    }
    // Initialize and configure FS Callback
    status = DMMControl::initFSCallback(); //capture statuses of function then return to main, 1 success - success  

    // Configure Message Ethernet ports (Incoming)
    status = Initialize_Command(udp_port_no,   // UDP port number
                       tcp_port_no,   // TCP port number
                       udp_priority,  // UDP priority
                       tcp_priority); // TCP priority

    // Initialize FliteScene
    status = FS_Initialize_Map(pConfigBuffer);
    

    //JSF Rule 59 implement braces
    // Wait until FliteScene initialization is complete
    while (FS_Get_Channel_Count() <= 0)
    {
        Sleep(sleep_time500);
    }
        

    // Get the viewport dimensions from FliteScene. Only 1 channel (0)
    status = FS_Get_Viewport_Size(0, &nFrameWidth, &nFrameHeight);


    //Create OpenGL context
    status = DMMControl::CreateOpenGL_Context();

    // Initialize Video Memory
    status = FS_Initialize_Graphics(0); // Only 1 channel (0)

    // Notify FliteScene that graphics initialization is complete, 
    // finish allocating all dynamic memory, and spawn the FliteScene tasks.
    FS_Finish_Initialization(1);
    OutputDebugString(L"DebugString: FS_Finish_Initialization completed.\n");

    // Start UDP client 
    DMMControl::StartUDPThread();

    // Setup Flitescene startup messages
    DMMControl::SetFSStartup();

    // Render Loop
    DWORD objectstatus = 0;
    while (nRendering == 1)
    {
        // Wait for the timer to signal
        objectstatus = WaitForSingleObject(hTimer, INFINITE); // capture timer signal return status
        // Swap buffer
        status = SwapBuffers(hDevice);
        // Set the device context for a channel.
        status = wglMakeCurrent(hDevice, hContext);
        // Clear the frame buffer
        FS_Clear_Screen(0);
        // Render scene.
        FS_Render(0);
    }

    //collate statuses
    if (filestatus != 0 || objectstatus != 0)
    { //if there is file read errors or wait errors, overall status is fail
        status = 0; 
    }

    //delete[] pConfigBuffer;
    return status;
}

//****************************************************************************
//* Function Name  : int getDisplayConfig()
//* Purpose        : Get startup configuration from XML.
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void DMMControl::getDisplayConfig()
{
    string configfile = "Display_Config.xml";//config file string name

    // Get config info from XML file.    
    sDisplay_config = XmlSerializer::parseDisplayConfigXml(XmlSerializer::readXml(configfile));

    return;
}


//****************************************************************************
//* Function Name  : int CreateOpenGL_Context()
//* Purpose        : Starts Win32 Window and and creates an OpenGL context.
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
int DMMControl::CreateOpenGL_Context()
{
    nInitialized = 0;
    //JSF disallowed JSF 143 
    //HANDLE hThread = 0; 
    //unsigned long ulExitCode = 0;
    const DWORD sleep_time1 = 1; //1 ms sleep time

    Window::StartWindowThread();

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
int DMMControl::initFSCallback()
{
    INT status              = 0;    //variable to hold statuses of call backs
    const INT portno7046    = 7046; //port no 7046
    const INT portno23      = 23;  //port no 23 
    const INT feature1      = 1;  //feature 1 for callback
    const INT feature2      = 2;  //feature 2 for callback
    const INT feature3      = 3;  //feature 3 for callback
    const INT feature4      = 4;  //feature 4 for callback
    const INT priority10    = 10; //priority 10 to start task
    
    // Configure Callback Ethernet port (outgoing)
    status = Initialize_Callback();
    status = Set_Callback_FliteScene_Response_Port(portno7046);
    CallbackServer::StartCallbackServerThread();

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
void DMMControl::SetFSStartup()
{
    // This is currently hardcoded to define the startup map display.
    FS_Comm::SendMsg_Mode(0, // Channel
    0,   // Mode - 0 for 2D, 1 for 3D
    "Q1",// Underlay Product Code defined in CONFIG_DIRECTORY.XML - "Q1" for Geotiff 4km
    0.0);// Range - Distance(nm) from top to bottom of the Map Window viewport. Only applicable in 2D.

    // Define and show ownship startup location.
    Vehicle::SetOwnshipVehicle(Test_Constants::Position().Lat, 
        Test_Constants::Position().Lon, 
        Test_Constants::Position().Heading);
    
    // Turn on overlays for symbols to be displayed
    MapTactical::SetMapTacticalOverlays();
}

//****************************************************************************
//* Function Name  : void StartUDPThread()
//* Purpose        : Creates thread for UDP client
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void DMMControl::StartUDPThread()
{
    const SIZE_T stacksize = 40960; //stack size
  
    //JSF RULE 175 NULL disallowed
    //So NULLs in hUDPThread = CreateThread(NULL, stackSize, 
    //(LPTHREAD_START_ROUTINE)UDPThreadStarter, 0, 0, NULL) replace by 0s
    //receive thread status
    HANDLE hUDPThread = CreateThread(0, stacksize, (LPTHREAD_START_ROUTINE)UDPThreadStarter, 0, 0, 0); 
    
   
    if (hUDPThread == 0)
    {
        OutputDebugString(L"Unable to start UDP Thread!\n");
        //JSF Rule 113 - No multiple exit points
        //Original code to be deleted: return;
    }
    else
    {
        OutputDebugString(L"UDP thread started.\n");
    }
}
//****************************************************************************
//* Function Name  : int UDPThreadStarter()
//* Purpose        : Start the UDB thread
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
int DMMControl::UDPThreadStarter()
{
    //JSF Rule 257 exception handling not allowed
    //the try catch block was removed 
    //JSF Rule 142 and Rule51
    //This was not used: WSASession session;
        
    //JSF rule 51 begin with lower case
    UDPSocket socketobj; //socket instance
    Deserializer deserializerobj; //deserializer instance
    const INT buffsize = 1024; //buffer size

    /*JSF
    use typedef char buffer[buffsize];
    use for loop: memset(buffer, 0, buffsize);
    */
    CHAR buffer[buffsize]; //buffer for holding message
    for (int i = 0; i < buffsize; i++)
    {buffer[i] = 0;}
  
    socketobj.udpClientBind(UDP_TYPE::UDP_MULTICAST, 
        sDisplay_config.UDP_config.ip_address, 
        sDisplay_config.UDP_config.port);
   
    OutputDebugString(L"UDP is listening.\n");
    
    while (1)
    {
       int msglen = socketobj.Listen(buffer); //receive msg len
       //process if got message
       if (msglen > 0)
       {
          deserializerobj.processMessage(buffer, msglen);
       }
    }
    return 1;
}


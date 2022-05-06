#pragma once
#include <winsock.h>
class CallbackServer
{
public:
    CallbackServer()
    {
    }

    ~CallbackServer()
    {
    }


    // Callback Server.
    // This is required to catch any Callback responses that are sent from FliteScene.
    static int CallbackThreadServer();
    static void StartCallbackServerThread();

    // Static getters for cursor object info fields
    static double GetCursorLongitude(void);
    static double GetCursorLatitude(void);
    static int GetRouteWaypointIndex(void);

private:
    static void ProcessClient(SOCKET socketIn);
    static int  ReadBytesTCP(SOCKET socketIn, char * pBuffer, int nLength);
    static void SwapBytes(int * pValue);

    // Response Parsers
    static void ProcessGeoResponse(char * pData);
    static void ProcessSetObjectResponse(char * pData);
    static void ProcessObjectSelectResponse(char * pData);
    static void ProcessObjectInfoResponse(char * pData);
    static void ProcessCLOSResponse(char * pData);
    static void ProcessPOIResponse(char * pData);
    static void ProcessTextBoxContentsResponse(char * pData);
    static void ProcessDataframeResponse(char * pData);
    static void ProcessMGRSConversionResponse(char * pData);
    static void ProcessDMSConversionResponse(char * pData);
    static void ProcessMapStatusResponse(char * pData);

    enum CALLBACK_CONSTANTS
    {
        MAX_HEADER_SIZE = 20,
        ENDIAN_FLAG_LITTLE = 0x41424344 // ABCD
    };

};


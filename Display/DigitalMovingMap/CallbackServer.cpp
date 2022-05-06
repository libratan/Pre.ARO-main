#include "CallbackServer.h"
#include <string.h> // for memcpy
#include <stdio.h>  // for printf
#include "FS_Constants.h" // for Response Message ID Enums
#include "FS_Comm.h"

#include "MapTactical.h"
#include "SymbolDB.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Windows Thread Variables
static int    s_nRunCallbackServerThread = 0;
static HANDLE s_hCallbackThread          = 0;

static double s_dCursorGeoLatitude  = 0.0;
static double s_dCursorGeoLongitude = 0.0;
static int s_nRouteWaypointIndex = -1;

//***********************************************************
//* Getters
//***********************************************************
double CallbackServer::GetCursorLongitude()
{
    return s_dCursorGeoLongitude;
}
double CallbackServer::GetCursorLatitude()
{
    return s_dCursorGeoLatitude;
}
int CallbackServer::GetRouteWaypointIndex()
{
    return s_nRouteWaypointIndex;
}

//***********************************************************
//* ReadBytesTCP
//***********************************************************
int CallbackServer::ReadBytesTCP(SOCKET socketIn, char * pBuffer, int nLength)
{
    unsigned long ulBytesRead = 0;
    int nRemainingLength = nLength;
    int nCurrentBytesRead = 0;

    // Attempt to read bytes from the socket while we have not met our length
    do
    {
        nCurrentBytesRead = recv(socketIn, &pBuffer[ulBytesRead], nRemainingLength, 0);
        if (nCurrentBytesRead <= 0)
        {
            // The Socket has either read 0 bytes or has encountered
            // an error to forcefully terminate (less than 0 bytes)
            ulBytesRead = 0;
            break;
        }

        // Adjust the amount read and the amount left to read from the socket.
        ulBytesRead += nCurrentBytesRead;
        nRemainingLength -= nCurrentBytesRead;

    } while ((ulBytesRead < static_cast<unsigned long>(nLength)));

    return ulBytesRead;
}

//***********************************************************
//* ProcessClient
//***********************************************************
void CallbackServer::ProcessClient(SOCKET socketIn)
{
    int nStatus = 1;
    int nEndian = 0;
    int nChannel = 0;
    int nMessageID = 0;
    int nResponseSize = 0;
    int nVersion = 0;
    int nHeaderBytes = 0;
    int nMessageBytes = 0;

    char pHeader[MAX_HEADER_SIZE] = "";
    char pData[4096] = "";

    while (nStatus == 1)
    {
        // Read Header
        nHeaderBytes = ReadBytesTCP(socketIn, pHeader, MAX_HEADER_SIZE);
        if (nHeaderBytes != MAX_HEADER_SIZE)
        {
            if (nHeaderBytes <= 0)
            {
                // The socket has closed. Stop processing.
                break;
            }
            // Ignore message
            continue;
        }

        // Extract header members
        memcpy(&nEndian, &pHeader[0], 4);
        memcpy(&nResponseSize, &pHeader[4], 4);
        memcpy(&nChannel, &pHeader[8], 4);
        memcpy(&nMessageID, &pHeader[12], 4);
        memcpy(&nVersion, &pHeader[16], 4);

        if (nEndian != ENDIAN_FLAG_LITTLE)
        {
            // Swap Bytes
            SwapBytes(&nResponseSize);
            SwapBytes(&nChannel);
            SwapBytes(&nMessageID);
            SwapBytes(&nVersion);

        }

        // Here, one would check for the message number, size, and version,
        // to ensure that one has read the desired message.

        // For this SDK, there will be a switch to distinguish the responses
        // One case will read out the response to give an example on how to parse a response.
        if (nResponseSize > 0)
        {
            // Clear out Data buffer.
            memset(pData, 0, (4096 * sizeof(char)));

            // Read Message
            nMessageBytes = ReadBytesTCP(socketIn, pData, nResponseSize);

            // Ensure the amount read is correct
            if (nMessageBytes != nResponseSize)
            {
                // Check for a closed socket
                if (nMessageBytes <= 0)
                {
                    // closed connection. Cease processing.
                    break;
                }

                // Ignore Message
                continue;
            }

            // Switch on which response was recieved.
            switch (nMessageID)
            {
            case FS_Constants::MSG_VERSION_ID:
                // Version ID Response
                printf("VERSION ID MESSAGE\n");
                break;
            case FS_Constants::MSG_SCREEN_CAPTURE_RESULTS:
                // Screen Capture Response
                printf("SCREEN CAPTURE RESPONSE\n");
                break;
            case FS_Constants::MSG_CURSOR_OBJECT_INFO:
                // Cursor Object Information Response
                ProcessObjectInfoResponse(pData);
                break;
            case FS_Constants::MSG_CURSOR_SELECTED_OBJECTS:
                // Cursor Selected Objects Response
                ProcessObjectSelectResponse(pData);
                break;
            case FS_Constants::MSG_SET_OBJECT_RESPONSE:
                // Set Object Response
                // This is the message that is returned whenever an Object that uses a FSUID is created.
                ProcessSetObjectResponse(pData);
                break;
            case FS_Constants::MSG_DATAFRAME_RESPONSE:
                // Dataframe Response
                ProcessDataframeResponse(pData);
                break;
            case FS_Constants::MSG_TEXTBOX_RESPONSE:
                // Textbox Contents Response
                // This is called when the Get Text Box Response Contents Message is sent.
                ProcessTextBoxContentsResponse(pData);
                break;
            case FS_Constants::FLITESCENE_UID_RESPONSE:
                // FliteScene UID Response
                printf("FLITESCENE UID RESPONSE\n");
                break;
            case FS_Constants::MSG_CLOS_RESULTS:
                // Line of Sight Response
                ProcessCLOSResponse(pData);
                break;
            case FS_Constants::MSG_POI_RESULTS:
                // Point of Intercept Response
                ProcessPOIResponse(pData);
                break;
            case FS_Constants::MSG_RANGE_BEARING_RESULTS:
                // Range and Bearing Results
                printf("RANGE AND BEARING RESULTS MESSAGE\n");
                break;
            case FS_Constants::MSG_GEO_RESPONSE:
                // Geo Response Message
                ProcessGeoResponse(pData);
                break;
            case FS_Constants::MSG_GRID_CONVERSION:
                // MGRS Grid Conversion Response
                ProcessMGRSConversionResponse(pData);
                break;
            case FS_Constants::MSG_DMS_CONVERSION:
                // DMS Conversion response
                ProcessDMSConversionResponse(pData);
                break;
            case FS_Constants::MSG_MAP_STATUS:
                // Added for testing
                // Map Status response
                ProcessMapStatusResponse(pData);
                break;
            default:
                printf("Message ID \"%d\" was sent by FliteScene\n", nMessageID);
                break;
            }
        }
    }

    // close client connection
    closesocket(socketIn);
}

//***********************************************************
//* CallbackThreadServer
//***********************************************************
int CallbackServer::CallbackThreadServer()
{
    // local variables
    int nResult = 0;
    SOCKADDR_IN struct_addr;
    WSADATA _wsda;
    SOCKET socketServer;

    nResult = WSAStartup(MAKEWORD(2, 2), &_wsda);
    if (nResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", nResult);
        return nResult;
    }

    // Init and connect socket.
    socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (socketServer == -1)
    {
        WSACleanup();
        printf("Socket failed with error: %d\n", WSAGetLastError());
        return -1;
    }

    memset(&struct_addr, 0, sizeof(struct_addr));
    struct_addr.sin_family = AF_INET;
    struct_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    struct_addr.sin_port = htons(7046);

    nResult = bind(socketServer, (SOCKADDR*)&struct_addr, sizeof(struct_addr));
    if (nResult == -1)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(socketServer);
        WSACleanup();
        return nResult;
    }

    nResult = listen(socketServer, SOMAXCONN);
    if (nResult == -1)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(socketServer);
        WSACleanup();
        return nResult;
    }

    s_nRunCallbackServerThread = 1;

    printf("Callback Server initiated\n");

    while (s_nRunCallbackServerThread == 1)
    {
        // accept a client connection
        SOCKET client_socket;
        while (s_nRunCallbackServerThread == 1 &&
            (client_socket = accept(socketServer, NULL, NULL)))
        {
            // process client connection.
            ProcessClient(client_socket);
        }
    }

    WSACleanup();
    return nResult;
}

//***********************************************************
//* StartCallbackServerThread
//***********************************************************
void CallbackServer::StartCallbackServerThread()
{

    s_hCallbackThread = CreateThread(NULL,
                                     32768,
                                     (LPTHREAD_START_ROUTINE)CallbackThreadServer,
                                     NULL,
                                     0,
                                     NULL);
    if (s_hCallbackThread == 0)
    {
        printf("Unable to start Callback Server Thread! BAILING OUT\n");
        return;
    }


}

//***********************************************************
//* RESPONSE PROCESSING FUNCTIONS.
//***********************************************************

//***********************************************************
//* ProcessGeoResponse
//***********************************************************
void CallbackServer::ProcessGeoResponse(char * pData)
{
    // Local variables
    int nKey = 0;
    int nInputData = 0;
    int nOutputData = 0;
    int nRequestStatus = 0;
    double dScreenX = 0.0;
    double dScreenY = 0.0;
    double dLat = 0.0;
    double dLon = 0.0;
    double dElevationDepth = 0.0;

    // Read the incoming data
    memcpy(&nKey,            &pData[0],  sizeof(int));
    memcpy(&nInputData,      &pData[4],  sizeof(int));
    memcpy(&nOutputData,     &pData[8],  sizeof(int));
    memcpy(&nRequestStatus,  &pData[12], sizeof(int));
    memcpy(&dScreenX,        &pData[16], sizeof(double));
    memcpy(&dScreenY,        &pData[24], sizeof(double));
    memcpy(&dLat,            &pData[32], sizeof(double));
    memcpy(&dLon,            &pData[40], sizeof(double));
    memcpy(&dElevationDepth, &pData[48], sizeof(double));

    // REQUEST STATUS
    // The following are the possible statuses that can come from FliteScene in this response.
    // -3: The request is still being processed. Try again later.
    // -2: the requested position is out of range.
    // -1: Elevation or depth data at requested position is invalid or missing.
    //  0: valid location OR valid elevation data - Source DTED Level 0 or RDTED 750m
    //  1: valid elevation data - Source DTED Level 1 or RDTED 150m
    //  2: valid elevation data - Source DTED Level 2 or RDTED 37.5m
    //  3: valid elevation data - Source Level 2 Arc Minutes
    //  4: valid elevation data - Source Level 1 Arc Minutes
    //  5: valid elevation data - Source Level 0.5 Arc Minutes
    //  6: valid elevation data - Source Level 0.1 Arc Minutes
    //  7: valid elevation data - Source Level 0.05 Arc Minutes
    //  8: Cached vertical data (value interpolated from elevation and depth data)
    //  9: valid elevation data - Source HRTE 3
    // 10: valid elevation data - Source HRTE 4
    // 11: valid elevation data - Source HRTE 5

    // Print out response data
    printf("*********************************\n");
    printf("GEO RESPONSE DATA\n");
    printf("Key: %d\n", nKey);
    printf("Input Data Type: %d\n", nInputData);
    printf("Output Data Type: %d\n", nOutputData);
    printf("Request Status: %d\n", nRequestStatus);
    printf("Screen X: %lf\n", dScreenX);
    printf("Screen Y: %lf\n", dScreenY);
    printf("Latitude: %lf\n", dLat);
    printf("Longitude: %lf\n", dLon);
    printf("Elevation / Depth Data: %lf\n", dElevationDepth);
    printf("*********************************\n");

}

//***********************************************************
//* ProcessSetObjectResponse
//***********************************************************
void CallbackServer::ProcessSetObjectResponse(char * pData)
{
    // Local variables
    int nType = 0; // Type
    int nSubtype = 0; // Subtype
    int nKey = 0; // Key
    int nFSUID = 0; // FliteScene UID
    int nObjectStatus = 0; // Status of Object Set

    // Read the data.
    memcpy(&nType,         &pData[0],  sizeof(int));
    memcpy(&nSubtype,      &pData[4],  sizeof(int));
    memcpy(&nKey,          &pData[8],  sizeof(int));
    memcpy(&nFSUID,        &pData[12], sizeof(int));
    memcpy(&nObjectStatus, &pData[16], sizeof(int));

    // Print out response data
    printf("*********************************\n");
    printf("SET OBJECT RESPONSE DATA\n");
    printf("Type: %d\n", nType);
    printf("SubType: %d\n", nSubtype);
    printf("Key: %d\n", nKey);
    printf("FliteScene UID: %d\n", nFSUID);
    printf("Status: %d\n", nObjectStatus);
    printf("*********************************\n");

    switch (nType)
    {
        // Tactical Symbols
        // Tactical Symbols set via the Set Tactical Graphics Message will return a FliteScene UID
        // In order to see it enabled, you must enable the Tactical Symbol via the Enable by UID message
    case 5:
        FS_Comm::SendMsg_EnableByUID(
            0, // the channel to send it to. For this kit, assume only 1 channel is configured
            1, // Enable Flag: 1 for enable, 0 for disable
            nFSUID); // FliteScene UID for the Symbol
        SymbolDB::update_SymbolUID(nKey, nFSUID);
        break;
    // StormScope Symbol
    // Sample_StormScope.cpp creates a stormscope symbol
    // In order to see it enabled, you must enable the Stormscope Symbol via the Enable by UID message
    case 19:
        FS_Comm::SendMsg_EnableByUID(
            0, // the channel to send it to. For this kit, assume only 1 channel is configured
            1, // Enable Flag: 1 for enable, 0 for disable
            nFSUID); // FliteScene UID for the Symbol
        break;
    default:
        break;
    }

    switch (nKey)
    {
        // GeoSymbolOffscreenIndicator.cpp creates a geosymbol with key 111
        // This returns here with a FSUID, which is used to create the offscreen indicator
    case 111:
        FS_Comm::SendMsg_SetGeoSymbolOffscreenIdicator(
            nFSUID,  // FSUID
            0,  // Action, 0 : Associate symbol with Offscreen Indicator
            1); // Off-screen Indicator Sprite Index

    }

}

//***********************************************************
//* ProcessObjectSelectResponse
//***********************************************************
void CallbackServer::ProcessObjectSelectResponse(char * pData)
{
    int nSelectedObjectCount = 0;
    int * arSelectedObjectIDs = 0;
    int * arSelectedObjectTypes = 0;

    // Read data
    memcpy(&nSelectedObjectCount, &pData[0], sizeof(int));

    if (nSelectedObjectCount > 0)
    {
        // Allocate temporary memory.
        arSelectedObjectIDs = new int[nSelectedObjectCount];
        arSelectedObjectTypes = new int[nSelectedObjectCount];
    }

    int iIndex = 0;
    for (int i = 0; i < nSelectedObjectCount; i++)
    {
        memcpy(&arSelectedObjectIDs[i], &pData[4 + (iIndex * sizeof(int))], sizeof(int));
        memcpy(&arSelectedObjectTypes[i], &pData[4 + (iIndex * sizeof(int) + sizeof(int))], sizeof(int));
        iIndex += 2;
    }

    // Print data
    printf("*********************************\n");
    printf("CURSOR SELECTED OBJECTS DATA\n");
    printf("Number of Selected Objects: %d\n", nSelectedObjectCount);
    if (nSelectedObjectCount > 0)
    {
        for (int i = 0; i < nSelectedObjectCount; i++)
        {
            printf("Object ID: %d\n", arSelectedObjectIDs[i]);
            printf("Object Type: %d\n\n", arSelectedObjectTypes[i]);
        }
    }
    printf("*********************************\n");

    //if (nSelectedObjectCount > 0)
    //{
    //    // set the objects for the Cursor Library
    //    Sample_CursorLibrary::SetFSIDs(nSelectedObjectCount, arSelectedObjectIDs);

    //    // free memory
    //    delete [] arSelectedObjectIDs;
    //    delete [] arSelectedObjectTypes;
    //}
}

//***********************************************************
//* ProcessObjectInfoResponse
//***********************************************************
void CallbackServer::ProcessObjectInfoResponse(char * pData)
{
    // Local Variables
    int nObjectID = 0;
    int nObjectType = 0;
    double dLat = 0.0;
    double dLon = 0.0;
    int nElevation = 0;
    int nMetadataLen = 0; // The metadata length is something that is configured in the FliteScene Config
    char szObjectMetadata[1024]; // For this SDK, we will configure this to 1KB
    int nObjectInfoLen = 0;

    // Memset Metadata
    memset(szObjectMetadata, 0, 1024);

    // Object Information
    // Pop up threats and predefined threats
    int nThreatIndex = 0;
    int nThreatType = 0;
    double dDetectionRange = 0.0;
    double dEngageRange = 0.0;
    int nThreatHeight = 0;

    // Route Objects
    int nRouteObjectIndex = 0;
    int nRouteObjectType = 0;

    // Parse Response Info
    memcpy(&nObjectID,       &pData[0], sizeof(int));
    memcpy(&nObjectType,     &pData[4], sizeof(int));
    memcpy(&dLat,            &pData[8], sizeof(double));
    memcpy(&dLon,            &pData[16], sizeof(double));
    memcpy(&nElevation,      &pData[24], sizeof(int));
    memcpy(&nMetadataLen,    &pData[28], sizeof(int));
    memcpy(szObjectMetadata, &pData[32], nMetadataLen);
    szObjectMetadata[32 + nMetadataLen] = 0; // NULL TERMNIATE STRING
    memcpy(&nObjectInfoLen,  &pData[32 + nMetadataLen], sizeof(int));

    // Store the geo location of the cursor
    s_dCursorGeoLatitude = dLat;
    s_dCursorGeoLongitude = dLon;

    // Parse Object Info Length
    switch (nObjectType)
    {
    case 1: // Intended Fall through
    case 2:
        // Threats
        memcpy(&nThreatIndex,    &pData[32 + nMetadataLen + nObjectInfoLen], sizeof(int));
        memcpy(&nThreatType,     &pData[32 + nMetadataLen + nObjectInfoLen + 4], sizeof(int));
        memcpy(&dDetectionRange, &pData[32 + nMetadataLen + nObjectInfoLen + 8], sizeof(double));
        memcpy(&dEngageRange,    &pData[32 + nMetadataLen + nObjectInfoLen + 16], sizeof(double));
        memcpy(&nThreatHeight,   &pData[32 + nMetadataLen + nObjectInfoLen + 24], sizeof(int));
        break;
    case 13:
        // Route Objects
        memcpy(&nRouteObjectIndex, &pData[32 + nMetadataLen + nObjectInfoLen], sizeof(int));
        memcpy(&nRouteObjectType,  &pData[32 + nMetadataLen + nObjectInfoLen + 4], sizeof(int));

        // Store the Route Waypoint index only if the route type is a Point (0)
        if (nRouteObjectType == 0)
        {
            s_nRouteWaypointIndex = nRouteObjectIndex;
        }
        break;
    default:
        break;
    }

    // Print out response data
    printf("*********************************\n");
    printf("OBJECT INFO RESPONSE DATA\n");
    printf("Object ID: %d\n", nObjectID);
    printf("Object Type: %d\n", nObjectType);
    printf("Object Lat: %lf\n", dLat);
    printf("Object Lon: %lf\n", dLon);
    printf("Object Elevation: %d\n", nElevation);
    printf("Object Metadata Length: %d\n", nMetadataLen);
    printf("Object Metadata: %s\n", szObjectMetadata);
    printf("Object Information Length: %d\n", nObjectInfoLen);
    switch (nObjectType)
    {
    case 1:
    case 2:
        // Threats
        printf("Object Threat Index: %d\n", nThreatIndex);
        printf("Object Threat Type: %d\n", nThreatType);
        printf("Object Detection Range: %lf\n", dDetectionRange);
        printf("Object Engage Range: %lf\n", dEngageRange);
        printf("Object Threat Height: %d\n", nThreatHeight);
    case 13:
        // Route Objects
        printf("Object Route Index: %d\n", nRouteObjectIndex);
        printf("Object Route Object Type: %d\n", nRouteObjectType);
    default:
        break;
    }
    printf("*********************************\n");

}

//***********************************************************
//* ProcessCLOSResponse
//***********************************************************
void CallbackServer::ProcessCLOSResponse(char * pData)
{
    // Local Variables
    double dLat1 = 0.0;
    double dLon1 = 0.0;
    int nElevation1 = 0;
    double dLat2 = 0.0;
    double dLon2 = 0.0;
    int nElevation2 = 0;

    // Note: Request Status can be one of the following.
    // -3: One or more requests parameters are out of range.
    // -2: One or both end points are outside of scene memory.
    // -1: Elevation data along the line of sight is invalid/missing.
    //  0: Clear Line of Sight EXISTS between two points.
    //  1: Clear Line of Sight DOES NOT EXIST for the two requested points.
    int nRequestStatus = 0;

    double dObstructionLat = 0.0;
    double dObstructionLon = 0.0;
    int nObstructionElevation = 0;

    // Parse response message
    memcpy(&dLat1,                 &pData[0], sizeof(double));
    memcpy(&dLon1,                 &pData[8], sizeof(double));
    memcpy(&nElevation1,           &pData[16], sizeof(int));
    memcpy(&dLat2,                 &pData[20], sizeof(double));
    memcpy(&dLon2,                 &pData[28], sizeof(double));
    memcpy(&nElevation2,           &pData[36], sizeof(int));
    memcpy(&nRequestStatus,        &pData[40], sizeof(int));
    memcpy(&dObstructionLat,       &pData[44], sizeof(double));
    memcpy(&dObstructionLon,       &pData[52], sizeof(double));
    memcpy(&nObstructionElevation, &pData[60], sizeof(int));


    // Print out response data
    printf("*********************************\n");
    printf("LINE OF SIGHT RESPONSE \n");
    printf("Latitude Point 1: %lf\n", dLat1);
    printf("Longitude Point 1: %lf\n", dLon2);
    printf("Elevation 1: %d\n", nElevation1);
    printf("Latitude Point 2: %lf\n", dLat2);
    printf("Longitude Point 2: %lf\n", dLon2);
    printf("Elevation 2: %d\n", nElevation2);
    printf("Request Status: %d\n", nRequestStatus);
    printf("Obstruction Latitude: %lf\n", dObstructionLat);
    printf("Obstruction Longitude: %lf\n", dObstructionLon);
    printf("Obstruction Elevation: %d\n", nObstructionElevation);
    printf("*********************************\n");
}

//***********************************************************
//* ProcessPOIResponse
//***********************************************************
void CallbackServer::ProcessPOIResponse(char * pData)
{
    // Local Variables
    double dLat = 0.0;
    double dLon = 0.0;
    int nElevation = 0;
    double dBearing = 0.0;
    double dPitch = 0.0;

    // Note: Request Status can be one of the following.
    // -3: One or more requests parameters are out of range.
    // -2: The line start is outside of the current scene.
    // -1: Elevation data along the line is invalid/missing.
    //  0: There is NO intercept for the line within the current scene.
    //  1: There EXISTS an intercept for the line.
    int nRequestStatus = 0;

    double dInterceptLat = 0.0;
    double dInterceptLon = 0.0;
    int nInterceptElevation = 0;

    // Parse response
    memcpy(&dLat,                &pData[0], sizeof(double));
    memcpy(&dLon,                &pData[8], sizeof(double));
    memcpy(&nElevation,          &pData[16], sizeof(int));
    memcpy(&dBearing,            &pData[20], sizeof(double));
    memcpy(&dPitch,              &pData[28], sizeof(double));
    memcpy(&nRequestStatus,      &pData[36], sizeof(int));
    memcpy(&dInterceptLat,       &pData[40], sizeof(double));
    memcpy(&dInterceptLon,       &pData[48], sizeof(double));
    memcpy(&nInterceptElevation, &pData[56], sizeof(int));

    // Print out response data
    printf("*********************************\n");
    printf("POINT OF INTERCEPT RESPONSE \n");
    printf("Latitude: %lf\n", dLat);
    printf("Longitude: %lf\n", dLon);
    printf("Elevation: %d\n", nElevation);
    printf("Bearing: %lf\n", dBearing);
    printf("Pitch: %lf\n", dPitch);
    printf("Request Status: %d\n", nRequestStatus);
    printf("Intercept Latitude: %lf\n", dInterceptLat);
    printf("Intercept Longitude: %lf\n", dInterceptLon);
    printf("Intercept Elevation: %d\n", nInterceptElevation);
    printf("*********************************\n");
}

//***********************************************************
//* ProcessTextBoxContentsResponse
//***********************************************************
void CallbackServer::ProcessTextBoxContentsResponse(char * pData)
{
    // Local Variables
    int nTextBoxIndex = 0;

    // The length of the contents is capped at a value in the FliteScene Config file
    // under the TEXT_BUFFER_LENGTH value
    char szTextBoxContents[1024];

    // Parse Response Message
    memcpy(&nTextBoxIndex,    &pData[0], sizeof(int));
    memcpy(szTextBoxContents, &pData[4], 1024);

    // Null Terminate String
    szTextBoxContents[1023] = 0;

    // Print out response data
    printf("*********************************\n");
    printf("TEXT BOX CONTENTS RESPONSE \n");
    printf("Text Box Number: %d\n", nTextBoxIndex);
    printf("Text Box Contents: %s\n", szTextBoxContents);
    printf("*********************************\n");
}

//***********************************************************
//* ProcessDataframeResponse
//***********************************************************
void CallbackServer::ProcessDataframeResponse(char * pData)
{
    // Local variables
    char szDataFrameFile[256]; // Filepath is capped at 256 bytes
    int nImageType = 0;
    int nPages = 0;
    int nImageWidth = 0;
    int nImageHeight = 0;

    // Parse Message
    memcpy(szDataFrameFile, &pData[0],   256);
    memcpy(&nImageType,     &pData[256], sizeof(int));
    memcpy(&nPages,         &pData[260], sizeof(int));
    memcpy(&nImageWidth,    &pData[264], sizeof(int));
    memcpy(&nImageHeight,   &pData[268], sizeof(int));

    // Null Terminate string
    szDataFrameFile[255] = 0;

    // Print out response data
    printf("*********************************\n");
    printf("DATAFRAME RESPONSE \n");
    printf("Dataframe Filename: %s\n", szDataFrameFile);
    // Switch on Type
    switch (nImageType)
    {
    case 0:
        // Error
        printf("Error in Image Type\n");
        break;
    case 1:
        // Bitmap
        printf("Image Type: Bitmap\n");
        break;
    case 2:
        // Icon
        printf("Image Type: Icon\n");
        break;
    case 3:
        // JPEG
        printf("Image Type: JPEG\n");
        break;
    case 4:
        // JPEG 2000 (.j2k)
        printf("Image Type: JPEG 2000 .j2k file\n");
        break;
    case 5:
        // JPEG 2000 (.jp2)
        printf("Image Type: JPEG 2000 .j2p file\n");
        break;
    case 6:
        // PDF
        printf("Image Type: PDF\n");
        break;
    case 7:
        // TIFF
        printf("Image Type: TIFF\n");
        break;
    case 8:
        // PNG
        printf("Image Type: PNG\n");
        break;
    default:
        printf("Unsupported Image Type: %d\n", nImageType);
        break;
    }
    printf("Number of Pages: %d\n", nPages);
    printf("Image Width: %d\n", nImageWidth);
    printf("Image Height: %d\n", nImageHeight);
    printf("*********************************\n");
}

//***********************************************************
//* ProcessMGRSConversionResponse
//***********************************************************
void CallbackServer::ProcessMGRSConversionResponse(char * pData)
{
    // Local Variables
    int nConversionResponse = 0;
    double dLonOrScreenX = 0.0;
    double dLatOrScreenY = 0.0;
    char szMGRSCode[32];

    // Clear buffer
    memset(szMGRSCode, 0, 32);

    // Parse incoming data
    memcpy(&nConversionResponse, &pData[0],  sizeof(int));
    memcpy(&dLonOrScreenX,       &pData[4],  sizeof(double));
    memcpy(&dLatOrScreenY,       &pData[12], sizeof(double));
    memcpy(szMGRSCode,           &pData[20], 32);

    // Null terminate string
    szMGRSCode[31] = 0;

    // CONVERSION RESPONSE CODE:
    // 10: Invalid Request made. This will echo back the parameters that came from the invalid request.
    // 11: Valid MGRS Code Conversion from X,Y or Lat,Lon pair.
    // 12: Valid Lat, Lon Conversion from MGRS Code.

    // Print out response data
    printf("*********************************\n");
    printf("MGRS CONVERSION RESPONSE \n");
    printf("Conversion Response Code: %d\n", nConversionResponse);
    printf("X coordinate or Longitude: %lf\n", dLonOrScreenX);
    printf("Y coordinate or Latitude: %lf\n", dLatOrScreenY);
    printf("MGRS Code: %s\n", szMGRSCode);
    printf("*********************************\n");

    // Give the recieved MGRS code to the Sample_Request to do a MGRS to Geo conversion.
    //Sample_Request::SetMGRSCode(szMGRSCode);
}

//***********************************************************
//* ProcessDMSConversionResponse
//***********************************************************
void CallbackServer::ProcessDMSConversionResponse(char* pData)
{
    // Local Variables
    int nConversionResponse = 0;
    double dLonOrScreenX = 0.0;
    double dLatOrScreenY = 0.0;
    int nDegreesLatitude = 0;
    int nMinutesLatitude = 0;
    double dSecondsLatitude = 0;
    int nDegreesLongitude = 0;
    int nMinutesLongitude = 0;
    double dSecondsLongitude = 0;
    int nOutputFormat = 0;
    char szDMSCode[32];

    // Clear buffer
    memset(szDMSCode, 0, 32);

    // Parse incoming data
    memcpy(&nConversionResponse, &pData[0], sizeof(int));
    memcpy(&dLonOrScreenX, &pData[4], sizeof(double));
    memcpy(&dLatOrScreenY, &pData[12], sizeof(double));
    memcpy(&nDegreesLatitude, &pData[20], sizeof(int));
    memcpy(&nMinutesLatitude, &pData[24], sizeof(int));
    memcpy(&dSecondsLatitude, &pData[28], sizeof(double));
    memcpy(&nDegreesLongitude, &pData[36], sizeof(int));
    memcpy(&nMinutesLongitude, &pData[40], sizeof(int));
    memcpy(&dSecondsLongitude, &pData[44], sizeof(double));
    memcpy(&nOutputFormat, &pData[52], sizeof(int));
    memcpy(szDMSCode, &pData[56], 32);

    // Null terminate string
    szDMSCode[31] = 0;

    // CONVERSION RESPONSE CODE:
    // 10: Invalid Request made. This will echo back the parameters that came from the invalid request.
    // 11: Valid MGRS Code Conversion from X,Y or Lat,Lon pair.
    // 12: Valid Lat, Lon Conversion from MGRS Code.

    // Print out response data
    printf("*********************************\n");
    printf("Decimal degrees to DMS conversion  \n");
    printf("Conversion Response Code: %d\n", nConversionResponse);
    printf("Degrees Latitude: %i\n", nDegreesLatitude);
    printf("Minutes Latitude: %i\n", nMinutesLatitude);
    printf("Seconds Latitude: %i\n", dSecondsLatitude);
    printf("Degrees Longitude: %i\n", nDegreesLongitude);
    printf("Minutes Longitude: %i\n", nMinutesLongitude);
    printf("Seconds Longitude: %i\n", dSecondsLongitude);
    printf("DMS Code: %s\n", szDMSCode);
    printf("*********************************\n");

    // Give the recieved MGRS code to the Sample_Request to do a MGRS to Geo conversion.
    //Sample_Request::SetMGRSCode(szDMSCode);
}

//***********************************************************
//* ProcessMapStatusResponse
//***********************************************************
void CallbackServer::ProcessMapStatusResponse(char* pData)
{
    // Local Variables
    int nUnderlayTilesAvail = 0;
    int nUnderlayTileStatus = 0;
    int nElevationTileAvail = 0;
    int nElevationTileStatus = 0;
    int nPerspectiveTilesAvail = 0;
    int nPerspectiveTilesStatus = 0;
    int nThreatPenetrated = 0;
    int nFrameCount = 0;
    int nElapsedTime = 0;
    int nPredefinedThreatCount = 0;
    int nThreatMaskCount = 0;
    int nThreatRingCount = 0;
    int nThreatSymbolCount = 0;
    int nAFDSymbolCount = 0;
    int nKeyholeSymbolCount = 0;
    int nTacticalSymbolCount = 0;
    int nUserGeoSymbolCount = 0;
    int nVOSymbolCount = 0;
    int nDrawingSymbolCount = 0;
    int nMCHUMSymbolCount = 0;
    int nLocalPtSymbolCount = 0;
    int nARINCSymbolCount = 0;
    int nDAFIFSymbolCount = 0;
    int nAirspaceSymbolCount = 0;
    int nVehicleObjCount = 0;
    int nRouteObjCount = 0;
    int nShapefileObjCount = 0;
    int nStormscopeObjCount = 0;


    //// Clear buffer
    //memset(szDMSCode, 0, 32);

    // Parse incoming data
    memcpy(&nUnderlayTilesAvail, &pData[0], sizeof(int));
    memcpy(&nUnderlayTileStatus, &pData[4], sizeof(int));
    memcpy(&nElevationTileAvail, &pData[8], sizeof(int));
    memcpy(&nElevationTileStatus, &pData[12], sizeof(int));
    memcpy(&nPerspectiveTilesAvail, &pData[16], sizeof(int));
    memcpy(&nPerspectiveTilesStatus, &pData[20], sizeof(int));
    memcpy(&nThreatPenetrated, &pData[24], sizeof(int));
    memcpy(&nFrameCount, &pData[28], sizeof(int));
    memcpy(&nElapsedTime, &pData[32], sizeof(int));
    memcpy(&nPredefinedThreatCount, &pData[36], sizeof(int));
    memcpy(&nThreatMaskCount, &pData[40], sizeof(int));
    memcpy(&nThreatRingCount, &pData[44], sizeof(int));
    memcpy(&nThreatSymbolCount, &pData[48], sizeof(int));
    memcpy(&nAFDSymbolCount, &pData[52], sizeof(int));
    memcpy(&nKeyholeSymbolCount, &pData[56], sizeof(int));
    memcpy(&nTacticalSymbolCount, &pData[60], sizeof(int));
    memcpy(&nUserGeoSymbolCount, &pData[64], sizeof(int));
    memcpy(&nVOSymbolCount, &pData[68], sizeof(int));
    memcpy(&nDrawingSymbolCount, &pData[72], sizeof(int));
    memcpy(&nMCHUMSymbolCount, &pData[76], sizeof(int));
    memcpy(&nLocalPtSymbolCount, &pData[80], sizeof(int));
    memcpy(&nARINCSymbolCount, &pData[84], sizeof(int));
    memcpy(&nDAFIFSymbolCount, &pData[88], sizeof(int));
    memcpy(&nAirspaceSymbolCount, &pData[92], sizeof(int));
    memcpy(&nVehicleObjCount, &pData[96], sizeof(int));
    memcpy(&nRouteObjCount, &pData[100], sizeof(int));
    memcpy(&nShapefileObjCount, &pData[104], sizeof(int));
    memcpy(&nStormscopeObjCount, &pData[108], sizeof(int));



    //// Null terminate string
    //szDMSCode[31] = 0;

    // CONVERSION RESPONSE CODE:
    // 10: Invalid Request made. This will echo back the parameters that came from the invalid request.
    // 11: Valid MGRS Code Conversion from X,Y or Lat,Lon pair.
    // 12: Valid Lat, Lon Conversion from MGRS Code.

    // Print out response data
    printf("*********************************\n");
    printf("Map Status  \n");
    printf("Underlay Tiles Available: %d\n", nUnderlayTilesAvail);
    printf("Underlay Tile Status: %d\n", nUnderlayTileStatus);
    printf("Elevation Tiles Available: %d\n", nElevationTileAvail);
    printf("Elevation Tile Status: %d\n", nElevationTileAvail);
    printf("Perspective Tiles Available: %d\n", nPerspectiveTilesAvail);
    printf("Perspective Tile Status: %d\n", nPerspectiveTilesStatus);
    printf("Threat Penetrated: %d\n", nThreatPenetrated);
    printf("Frame Count: %d\n", nFrameCount);
    printf("Elapsed Time: %d\n", nElapsedTime);
    printf("Predefined Threat Count: %d\n", nPredefinedThreatCount);
    printf("Threat Mask Count: %d\n", nThreatMaskCount);
    printf("Threat Ring Count: %d\n", nThreatRingCount);
    printf("Threat Symbol Count: %d\n", nThreatSymbolCount);
    printf("AFD Symbol Count: %d\n", nAFDSymbolCount);
    printf("Keyhole Symbol Count: %d\n", nKeyholeSymbolCount);
    printf("Tactical Symbol Count: %d\n", nTacticalSymbolCount);
    printf("User Geo Symbol Count: %d\n", nUserGeoSymbolCount);
    printf("VO Symbol Count: %d\n", nVOSymbolCount);
    printf("Drawing Symbol Count: %d\n", nDrawingSymbolCount);
    printf("MCHUM Symbol Count: %d\n", nMCHUMSymbolCount);
    printf("Local Point Symbol Count: %d\n", nLocalPtSymbolCount);
    printf("ARINC Symbol Count: %d\n", nARINCSymbolCount);
    printf("DAFIF Symbol Count: %d\n", nAirspaceSymbolCount);
    printf("Vehicle Object Count: %d\n", nVehicleObjCount);
    printf("Route Object Count: %d\n", nRouteObjCount);
    printf("Shapefile Object Count: %d\n", nShapefileObjCount);
    printf("Stormscope Object Count: %d\n", nStormscopeObjCount);
    printf("*********************************\n");

    // Give the recieved MGRS code to the Sample_Request to do a MGRS to Geo conversion.
    //Sample_Request::SetMGRSCode(szDMSCode);
}

//***********************************************************
//* END RESPONSE PROCESSING FUNCTIONS.
//***********************************************************

//***********************************************************
//* SwapBytes
//***********************************************************
void CallbackServer::SwapBytes(int * pValue)
{
    *(long*)pValue = ((*(long*)pValue & 0x000000FFU) << 24) +
        ((*(long*)pValue & 0x0000FF00U) << 8) +
        ((*(long*)pValue & 0x00FF0000U) >> 8) +
        ((*(long*)pValue & 0xFF000000U) >> 24);
}
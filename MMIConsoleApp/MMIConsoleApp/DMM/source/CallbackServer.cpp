//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: CallbackServer.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// This is a callback server
//
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************

#include <../DMM/header/CallbackServer.h>
#include <string.h> // for memcpy
#include <stdio.h>  // for printf
#include <../DMM/header/FS_Constants.h> // for Response Message ID Enums
#include <../DMM/header/FS_Comm.h>

#include <../DMM/header/MapTactical.h>
#include <../DMM/header/SymbolDB.h>
//JSF add namespace to prevent global clash
using namespace SYMDB;
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Windows Thread Variables
static INT32  s_nRunCallbackServerThread = 0;   // Run callback server thread
static HANDLE s_hCallbackThread          = 0;   // Handler for Callback thread

static FLOAT64 s_dCursorGeoLatitude  = 0.0;     // Cursor for GeoLatitude
static FLOAT64 s_dCursorGeoLongitude = 0.0;     // Cursor for GeoLongitude
static INT32   s_nRouteWaypointIndex = -1;      // Route Way Point Index

// For temp fix of JSF violations related to unused function return values.
// Consider to waive off these violations instead.
//  - [JSF-115-3], [JSF-115_a-4] : Unused function's "printf" return value
//  - [JSF-115_a-4] : Unused function's 'memcpy' return value
//  - [JSF-115_a-4] : Unused function's 'memset' return value
static INT32 s_nTmpRet = 0;         // temp return variable for printf
static void* s_vTmpRet = 0;         // temp return varaible for memcpy, memset            

//***********************************************************
//* Getters
//***********************************************************
FLOAT64 CallbackServer::getCursorLongitude()
{
    return s_dCursorGeoLongitude;
}
FLOAT64 CallbackServer::getCursorLatitude()
{
    return s_dCursorGeoLatitude;
}
INT32 CallbackServer::getRouteWaypointIndex()
{
    return s_nRouteWaypointIndex;
}

//***********************************************************
//* ReadBytesTCP
//***********************************************************
UINT32 CallbackServer::readBytesTCP(SOCKET socketIn, 
                                    CHAR(&pBuffer)[data_buffer_size],
                                    INT32 nLength)
{
    UINT32 ulBytesRead = 0; // Bytes Read
    INT32 nRemainingLength = nLength; // Remaining Length
    INT32 nCurrentBytesRead = 0; // Current Bytes Read

    // Attempt to read bytes from the socket while we have not met our length
    do
    {       
        if (ulBytesRead < data_buffer_size)
        {
            nCurrentBytesRead = recv(socketIn, &pBuffer[ulBytesRead], nRemainingLength, 0);
        }

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
    } 
    while ((ulBytesRead < (static_cast<UINT32>(nLength))));

    return ulBytesRead;
}

//***********************************************************
//* ReadBytesTCPHeader
//***********************************************************
UINT32 CallbackServer::readBytesTCPHeader(SOCKET socketIn,
                                          CHAR(&pBuffer)[max_header_size],
                                          INT32 nLength)
{
    UINT32 ulBytesRead = 0; // Bytes Read
    INT32 nRemainingLength = nLength; // Remaining Length
    INT32 nCurrentBytesRead = 0; // Current Bytes Read

    // Attempt to read bytes from the socket while we have not met our length
    do
    {
        if (ulBytesRead < max_header_size)
        {
            nCurrentBytesRead = recv(socketIn, &pBuffer[ulBytesRead], nRemainingLength, 0);
        }

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
    }
    while ((ulBytesRead < (static_cast<UINT32>(nLength))));

    return ulBytesRead;
}

//***********************************************************
//* ProcessClient
//***********************************************************
void CallbackServer::processClient(SOCKET socketIn)
{
    UINT8 nStatus = 1;              // Status
    INT32 nEndian = 0;              // endian
    INT32 nChannel = 0;             // channel
    INT32 nMessageID = 0;           // msg id
    INT32 nResponseSize = 0;        // response size
    INT32 nVersion = 0;             // version
    INT32 nHeaderBytes = 0;         // header bytes
    INT32 nMessageBytes = 0;        // msg bytes

    CHAR pHeader[max_header_size] = "";     // tcp msg header
    CHAR pData[data_buffer_size] = "";      // tcp msg data

    while (nStatus == 1)
    {
        // Read Header
        nHeaderBytes = readBytesTCPHeader(socketIn, pHeader, max_header_size);
        if (nHeaderBytes != max_header_size)
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
        s_vTmpRet = memcpy(&nEndian, &pHeader[0], 4);
        s_vTmpRet = memcpy(&nResponseSize, &pHeader[4], 4);
        s_vTmpRet = memcpy(&nChannel, &pHeader[8], 4);
        s_vTmpRet = memcpy(&nMessageID, &pHeader[12], 4);
        s_vTmpRet = memcpy(&nVersion, &pHeader[16], 4);

        if (nEndian != endian_flag_little)
        {
            // Swap Bytes
            swapBytes(nResponseSize);
            swapBytes(nChannel);
            swapBytes(nMessageID);
            swapBytes(nVersion);
        }

        // Here, one would check for the message number, size, and version,
        // to ensure that one has read the desired message.

        // For this SDK, there will be a switch to distinguish the responses
        // One case will read out the response to give an example on how to parse a response.
        if (nResponseSize > 0)
        {
            // Clear out Data buffer.
            s_vTmpRet = memset(&pData, 0, (data_buffer_size * sizeof(CHAR)));

            // Read Message
            nMessageBytes = readBytesTCP(socketIn, pData, nResponseSize);

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
                s_nTmpRet = printf("VERSION ID MESSAGE\n");
                break;
            case FS_Constants::MSG_SCREEN_CAPTURE_RESULTS:
                // Screen Capture Response
                s_nTmpRet = printf("SCREEN CAPTURE RESPONSE\n");
                break;
            case FS_Constants::MSG_CURSOR_OBJECT_INFO:
                // Cursor Object Information Response
                processObjectInfoResponse(pData);
                break;
            case FS_Constants::MSG_CURSOR_SELECTED_OBJECTS:
                // Cursor Selected Objects Response
                processObjectSelectResponse(pData);
                break;
            case FS_Constants::MSG_SET_OBJECT_RESPONSE:
                // Set Object Response
                // This is the message that is returned whenever an Object that uses a FSUID is created.
                processSetObjectResponse(pData);
                break;
            case FS_Constants::MSG_DATAFRAME_RESPONSE:
                // Dataframe Response
                processDataframeResponse(pData);
                break;
            case FS_Constants::MSG_TEXTBOX_RESPONSE:
                // Textbox Contents Response
                // This is called when the Get Text Box Response Contents Message is sent.
                processTextBoxContentsResponse(pData);
                break;
            case FS_Constants::FLITESCENE_UID_RESPONSE:
                // FliteScene UID Response
                s_nTmpRet = printf("FLITESCENE UID RESPONSE\n");
                break;
            case FS_Constants::MSG_CLOS_RESULTS:
                // Line of Sight Response
                processCLOSResponse(pData);
                break;
            case FS_Constants::MSG_POI_RESULTS:
                // Point of Intercept Response
                processPOIResponse(pData);
                break;
            case FS_Constants::MSG_RANGE_BEARING_RESULTS:
                // Range and Bearing Results
                s_nTmpRet = printf("RANGE AND BEARING RESULTS MESSAGE\n");
                break;
            case FS_Constants::MSG_GEO_RESPONSE:
                // Geo Response Message
                processGeoResponse(pData);
                break;
            case FS_Constants::MSG_GRID_CONVERSION:
                // MGRS Grid Conversion Response
                processMGRSConversionResponse(pData);
                break;
            case FS_Constants::MSG_DMS_CONVERSION:
                // DMS Conversion response
                processDMSConversionResponse(pData);
                break;
            case FS_Constants::MSG_MAP_STATUS:
                // Added for testing
                // Map Status response
                processMapStatusResponse(pData);
                break;
            default:
                s_nTmpRet = printf("Message ID \"%d\" was sent by FliteScene\n", nMessageID);
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
INT32 CallbackServer::callbackThreadServer()
{
    // local variables
    SOCKADDR_IN struct_addr;    // socket address
    WSADATA wsda;               // wsdata

    INT32 nResult = WSAStartup(MAKEWORD(2, 2), &wsda);
    if (nResult != 0)
    {
        s_nTmpRet = printf("WSAStartup failed with error: %d\n", nResult);
        return nResult;
    }

    // Init and connect socket.
    SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (socketServer == -1)
    {
        WSACleanup();
        s_nTmpRet = printf("Socket failed with error: %d\n", WSAGetLastError());
        return -1;
    }

    s_vTmpRet = memset(&struct_addr, 0, sizeof(struct_addr));
    struct_addr.sin_family = AF_INET;
    struct_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    struct_addr.sin_port = htons(7046);

    nResult = bind(socketServer, (SOCKADDR*)&struct_addr, sizeof(struct_addr));
    if (nResult == -1)
    {
        s_nTmpRet = printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(socketServer);
        WSACleanup();
        return nResult;
    }

    nResult = listen(socketServer, SOMAXCONN);
    if (nResult == -1)
    {
        s_nTmpRet = printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(socketServer);
        WSACleanup();
        return nResult;
    }

    s_nRunCallbackServerThread = 1;

    s_nTmpRet = printf("Callback Server initiated\n");

    while (s_nRunCallbackServerThread == 1)
    {
        // accept a client connection
        SOCKET client_socket;
        while ((s_nRunCallbackServerThread == 1) &&
            (client_socket = accept(socketServer, 0, 0)))
        {
            // process client connection.
            processClient(client_socket);
        }
    }

    WSACleanup();
    return nResult;
}

//***********************************************************
//* StartCallbackServerThread
//***********************************************************
void CallbackServer::startCallbackServerThread()
{
    s_hCallbackThread = CreateThread(0,
                                     32768,
                                     (LPTHREAD_START_ROUTINE)callbackThreadServer,
                                     0,
                                     0,
                                     0);
    if (s_hCallbackThread == 0)
    {
        s_nTmpRet = printf("Unable to start Callback Server Thread! BAILING OUT\n");
        return;
    }
}

//***********************************************************
//* RESPONSE PROCESSING FUNCTIONS.
//***********************************************************

//***********************************************************
//* ProcessGeoResponse
//***********************************************************
void CallbackServer::processGeoResponse(CHAR (&pData)[data_buffer_size])
{
    // Local variables
    INT32 nKey = 0;             // key
    INT32 nInputData = 0;       // input data
    INT32 nOutputData = 0;      // output data
    INT32 nRequestStatus = 0;   // request status
    FLOAT64 dScreenX = 0.0;     // x
    FLOAT64 dScreenY = 0.0;     // y
    FLOAT64 dLat = 0.0;         // lat
    FLOAT64 dLon = 0.0;         // lon
    FLOAT64 dElevationDepth = 0.0;      // elevation depth

    // Read the incoming data
    s_vTmpRet = memcpy(&nKey,            &pData[0],  sizeof(INT32));
    s_vTmpRet = memcpy(&nInputData,      &pData[4],  sizeof(INT32));
    s_vTmpRet = memcpy(&nOutputData,     &pData[8],  sizeof(INT32));
    s_vTmpRet = memcpy(&nRequestStatus,  &pData[12], sizeof(INT32));
    s_vTmpRet = memcpy(&dScreenX,        &pData[16], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dScreenY,        &pData[24], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dLat,            &pData[32], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dLon,            &pData[40], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dElevationDepth, &pData[48], sizeof(FLOAT64));

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
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("GEO RESPONSE DATA\n");
    s_nTmpRet = printf("Key: %d\n", nKey);
    s_nTmpRet = printf("Input Data Type: %d\n", nInputData);
    s_nTmpRet = printf("Output Data Type: %d\n", nOutputData);
    s_nTmpRet = printf("Request Status: %d\n", nRequestStatus);
    s_nTmpRet = printf("Screen X: %lf\n", dScreenX);
    s_nTmpRet = printf("Screen Y: %lf\n", dScreenY);
    s_nTmpRet = printf("Latitude: %lf\n", dLat);
    s_nTmpRet = printf("Longitude: %lf\n", dLon);
    s_nTmpRet = printf("Elevation / Depth Data: %lf\n", dElevationDepth);
    s_nTmpRet = printf("*********************************\n");
}

//***********************************************************
//* ProcessSetObjectResponse
//***********************************************************
void CallbackServer::processSetObjectResponse(CHAR (&pData)[data_buffer_size])
{
    // Local variables
    INT32 nType = 0; // Type
    INT32 nSubtype = 0; // Subtype
    INT32 nKey = 0; // Key
    INT32 nFSUID = 0; // FliteScene UID
    INT32 nObjectStatus = 0; // Status of Object Set

    // Read the data.
    s_vTmpRet = memcpy(&nType,         &pData[0],  sizeof(INT32));
    s_vTmpRet = memcpy(&nSubtype,      &pData[4],  sizeof(INT32));
    s_vTmpRet = memcpy(&nKey,          &pData[8],  sizeof(INT32));
    s_vTmpRet = memcpy(&nFSUID,        &pData[12], sizeof(INT32));
    s_vTmpRet = memcpy(&nObjectStatus, &pData[16], sizeof(INT32));

    // Print out response data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("SET OBJECT RESPONSE DATA\n");
    s_nTmpRet = printf("Type: %d\n", nType);
    s_nTmpRet = printf("SubType: %d\n", nSubtype);
    s_nTmpRet = printf("Key: %d\n", nKey);
    s_nTmpRet = printf("FliteScene UID: %d\n", nFSUID);
    s_nTmpRet = printf("Status: %d\n", nObjectStatus);
    s_nTmpRet = printf("*********************************\n");

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
        //JSF add namespace scope
        SYMDB::SymbolDB::update_SymbolUID(nKey, nFSUID);
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
        break;
    default:
        break;
    }
}

//***********************************************************
//* ProcessObjectSelectResponse
//***********************************************************
void CallbackServer::processObjectSelectResponse(CHAR (&pData)[data_buffer_size])
{
    INT32 nSelectedObjectCount = 0;     // SelectedObjectCount
    INT32* arSelectedObjectIDs = 0;     // ptr to array SelectedObjectIDs
    INT32* arSelectedObjectTypes = 0;   // ptr to array SelectedObjectTypes

    // Read data
    s_vTmpRet = memcpy(&nSelectedObjectCount, &pData[0], sizeof(INT32));

    if (nSelectedObjectCount > 0)
    {
        // Allocate temporary memory.
        arSelectedObjectIDs = new INT32[nSelectedObjectCount];
        arSelectedObjectTypes = new INT32[nSelectedObjectCount];
    }

    INT32 iIndex = 0;
    for (INT32 i = 0; i < nSelectedObjectCount; i++)
    {
        s_vTmpRet = memcpy(&arSelectedObjectIDs[i], &pData[4 + (iIndex * sizeof(INT32))], sizeof(INT32));
        s_vTmpRet = memcpy(&arSelectedObjectTypes[i], &pData[4 + (iIndex * sizeof(INT32) + sizeof(INT32))], sizeof(INT32));
        iIndex += 2;
    }

    // Print data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("CURSOR SELECTED OBJECTS DATA\n");
    s_nTmpRet = printf("Number of Selected Objects: %d\n", nSelectedObjectCount);
    if (nSelectedObjectCount > 0)
    {
        for (INT32 i = 0; i < nSelectedObjectCount; i++)
        {
            s_nTmpRet = printf("Object ID: %d\n", arSelectedObjectIDs[i]);
            s_nTmpRet = printf("Object Type: %d\n\n", arSelectedObjectTypes[i]);
        }
    }
    s_nTmpRet = printf("*********************************\n");

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
void CallbackServer::processObjectInfoResponse(CHAR (&pData)[data_buffer_size])
{
    // Local Variables
    INT32 nObjectID = 0;            // ObjectID
    INT32 nObjectType = 0;          // ObjectType
    FLOAT64 dLat = 0.0;             // Lat
    FLOAT64 dLon = 0.0;             // Lon
    INT32 nElevation = 0;           // Elevation
    INT32 nMetadataLen = 0; // The metadata length is something that is configured in the FliteScene Config
    CHAR szObjectMetadata[1024]; // For this SDK, we will configure this to 1KB
    INT32 nObjectInfoLen = 0;       // ObjectInfoLen

    // Memset Metadata
    s_vTmpRet = memset(&szObjectMetadata, 0, 1024);

    // Object Information
    // Pop up threats and predefined threats
    INT32 nThreatIndex = 0;         // ThreatIndex
    INT32 nThreatType = 0;          // ThreatType
    FLOAT64 dDetectionRange = 0.0;  // DetectionRange
    FLOAT64 dEngageRange = 0.0;     // EngageRange
    INT32 nThreatHeight = 0;        // ThreatHeight

    // Route Objects
    INT32 nRouteObjectIndex = 0;    // RouteObjectIndex
    INT32 nRouteObjectType = 0;     // RouteObjectType

    // Parse Response Info
    s_vTmpRet = memcpy(&nObjectID,       &pData[0], sizeof(INT32));
    s_vTmpRet = memcpy(&nObjectType,     &pData[4], sizeof(INT32));
    s_vTmpRet = memcpy(&dLat,            &pData[8], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dLon,            &pData[16], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nElevation,      &pData[24], sizeof(INT32));
    s_vTmpRet = memcpy(&nMetadataLen,    &pData[28], sizeof(INT32));
    s_vTmpRet = memcpy(&szObjectMetadata, &pData[32], nMetadataLen);
    szObjectMetadata[32 + nMetadataLen] = 0; // NULL TERMNIATE STRING
    s_vTmpRet = memcpy(&nObjectInfoLen,  &pData[32 + nMetadataLen], sizeof(INT32));

    // Store the geo location of the cursor
    s_dCursorGeoLatitude = dLat;
    s_dCursorGeoLongitude = dLon;

    // Parse Object Info Length
    switch (nObjectType)
    {
    case 1: // Intended Fall through
    case 2:
        // Threats
        s_vTmpRet = memcpy(&nThreatIndex,    &pData[32 + nMetadataLen + nObjectInfoLen], sizeof(INT32));
        s_vTmpRet = memcpy(&nThreatType,     &pData[32 + nMetadataLen + nObjectInfoLen + 4], sizeof(INT32));
        s_vTmpRet = memcpy(&dDetectionRange, &pData[32 + nMetadataLen + nObjectInfoLen + 8], sizeof(FLOAT64));
        s_vTmpRet = memcpy(&dEngageRange,    &pData[32 + nMetadataLen + nObjectInfoLen + 16], sizeof(FLOAT64));
        s_vTmpRet = memcpy(&nThreatHeight,   &pData[32 + nMetadataLen + nObjectInfoLen + 24], sizeof(INT32));
        break;
    case 13:
        // Route Objects
        s_vTmpRet = memcpy(&nRouteObjectIndex, &pData[32 + nMetadataLen + nObjectInfoLen], sizeof(INT32));
        s_vTmpRet = memcpy(&nRouteObjectType,  &pData[32 + nMetadataLen + nObjectInfoLen + 4], sizeof(INT32));

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
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("OBJECT INFO RESPONSE DATA\n");
    s_nTmpRet = printf("Object ID: %d\n", nObjectID);
    s_nTmpRet = printf("Object Type: %d\n", nObjectType);
    s_nTmpRet = printf("Object Lat: %lf\n", dLat);
    s_nTmpRet = printf("Object Lon: %lf\n", dLon);
    s_nTmpRet = printf("Object Elevation: %d\n", nElevation);
    s_nTmpRet = printf("Object Metadata Length: %d\n", nMetadataLen);
    s_nTmpRet = printf("Object Metadata: %s\n", szObjectMetadata);
    s_nTmpRet = printf("Object Information Length: %d\n", nObjectInfoLen);
    switch (nObjectType)
    {
    case 1:
    case 2:
        // Threats
        s_nTmpRet = printf("Object Threat Index: %d\n", nThreatIndex);
        s_nTmpRet = printf("Object Threat Type: %d\n", nThreatType);
        s_nTmpRet = printf("Object Detection Range: %lf\n", dDetectionRange);
        s_nTmpRet = printf("Object Engage Range: %lf\n", dEngageRange);
        s_nTmpRet = printf("Object Threat Height: %d\n", nThreatHeight);
    case 13:
        // Route Objects
        s_nTmpRet = printf("Object Route Index: %d\n", nRouteObjectIndex);
        s_nTmpRet = printf("Object Route Object Type: %d\n", nRouteObjectType);
    default:
        break;
    }
    s_nTmpRet = printf("*********************************\n");

}

//***********************************************************
//* ProcessCLOSResponse
//***********************************************************
void CallbackServer::processCLOSResponse(CHAR (&pData)[data_buffer_size])
{
    // Local Variables
    FLOAT64 dLat1 = 0.0;        // Lat1
    FLOAT64 dLon1 = 0.0;        // Lon1
    INT32 nElevation1 = 0;      // Elevation1
    FLOAT64 dLat2 = 0.0;        // Lat2
    FLOAT64 dLon2 = 0.0;        // Lon2
    INT32 nElevation2 = 0;      // Elevation2

    // Note: Request Status can be one of the following.
    // -3: One or more requests parameters are out of range.
    // -2: One or both end points are outside of scene memory.
    // -1: Elevation data along the line of sight is invalid/missing.
    //  0: Clear Line of Sight EXISTS between two points.
    //  1: Clear Line of Sight DOES NOT EXIST for the two requested points.
    INT32 nRequestStatus = 0;           // RequestStatus

    FLOAT64 dObstructionLat = 0.0;      // ObstructionLat
    FLOAT64 dObstructionLon = 0.0;      // ObstructionLon
    INT32 nObstructionElevation = 0;    // ObstructionElevation

    // Parse response message
    s_vTmpRet = memcpy(&dLat1,                 &pData[0], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dLon1,                 &pData[8], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nElevation1,           &pData[16], sizeof(INT32));
    s_vTmpRet = memcpy(&dLat2,                 &pData[20], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dLon2,                 &pData[28], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nElevation2,           &pData[36], sizeof(INT32));
    s_vTmpRet = memcpy(&nRequestStatus,        &pData[40], sizeof(INT32));
    s_vTmpRet = memcpy(&dObstructionLat,       &pData[44], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dObstructionLon,       &pData[52], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nObstructionElevation, &pData[60], sizeof(INT32));


    // Print out response data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("LINE OF SIGHT RESPONSE \n");
    s_nTmpRet = printf("Latitude Point 1: %lf\n", dLat1);
    s_nTmpRet = printf("Longitude Point 1: %lf\n", dLon2);
    s_nTmpRet = printf("Elevation 1: %d\n", nElevation1);
    s_nTmpRet = printf("Latitude Point 2: %lf\n", dLat2);
    s_nTmpRet = printf("Longitude Point 2: %lf\n", dLon2);
    s_nTmpRet = printf("Elevation 2: %d\n", nElevation2);
    s_nTmpRet = printf("Request Status: %d\n", nRequestStatus);
    s_nTmpRet = printf("Obstruction Latitude: %lf\n", dObstructionLat);
    s_nTmpRet = printf("Obstruction Longitude: %lf\n", dObstructionLon);
    s_nTmpRet = printf("Obstruction Elevation: %d\n", nObstructionElevation);
    s_nTmpRet = printf("*********************************\n");
}

//***********************************************************
//* ProcessPOIResponse
//***********************************************************
void CallbackServer::processPOIResponse(CHAR (&pData)[data_buffer_size])
{
    // Local Variables
    FLOAT64 dLat = 0.0;         // lat
    FLOAT64 dLon = 0.0;         // lon
    INT32 nElevation = 0;       // elevation
    FLOAT64 dBearing = 0.0;     // bearing
    FLOAT64 dPitch = 0.0;       // pitch

    // Note: Request Status can be one of the following.
    // -3: One or more requests parameters are out of range.
    // -2: The line start is outside of the current scene.
    // -1: Elevation data along the line is invalid/missing.
    //  0: There is NO intercept for the line within the current scene.
    //  1: There EXISTS an intercept for the line.
    INT32 nRequestStatus = 0;

    FLOAT64 dInterceptLat = 0.0;
    FLOAT64 dInterceptLon = 0.0;
    INT32 nInterceptElevation = 0;

    // Parse response
    s_vTmpRet = memcpy(&dLat,                &pData[0], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dLon,                &pData[8], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nElevation,          &pData[16], sizeof(INT32));
    s_vTmpRet = memcpy(&dBearing,            &pData[20], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dPitch,              &pData[28], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nRequestStatus,      &pData[36], sizeof(INT32));
    s_vTmpRet = memcpy(&dInterceptLat,       &pData[40], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dInterceptLon,       &pData[48], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nInterceptElevation, &pData[56], sizeof(INT32));

    // Print out response data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("POINT OF INTERCEPT RESPONSE \n");
    s_nTmpRet = printf("Latitude: %lf\n", dLat);
    s_nTmpRet = printf("Longitude: %lf\n", dLon);
    s_nTmpRet = printf("Elevation: %d\n", nElevation);
    s_nTmpRet = printf("Bearing: %lf\n", dBearing);
    s_nTmpRet = printf("Pitch: %lf\n", dPitch);
    s_nTmpRet = printf("Request Status: %d\n", nRequestStatus);
    s_nTmpRet = printf("Intercept Latitude: %lf\n", dInterceptLat);
    s_nTmpRet = printf("Intercept Longitude: %lf\n", dInterceptLon);
    s_nTmpRet = printf("Intercept Elevation: %d\n", nInterceptElevation);
    s_nTmpRet = printf("*********************************\n");
}

//***********************************************************
//* ProcessTextBoxContentsResponse
//***********************************************************
void CallbackServer::processTextBoxContentsResponse(CHAR (&pData)[data_buffer_size])
{
    // Local Variables
    INT32 nTextBoxIndex = 0;        // TextBoxIndex

    // The length of the contents is capped at a value in the FliteScene Config file
    // under the TEXT_BUFFER_LENGTH value
    CHAR szTextBoxContents[1024];   // TextBoxContents

    // Parse Response Message
    s_vTmpRet = memcpy(&nTextBoxIndex,    &pData[0], sizeof(INT32));
    s_vTmpRet = memcpy(&szTextBoxContents, &pData[4], 1024);

    // Null Terminate String
    szTextBoxContents[1023] = 0;

    // Print out response data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("TEXT BOX CONTENTS RESPONSE \n");
    s_nTmpRet = printf("Text Box Number: %d\n", nTextBoxIndex);
    s_nTmpRet = printf("Text Box Contents: %s\n", szTextBoxContents);
    s_nTmpRet = printf("*********************************\n");
}

//***********************************************************
//* ProcessDataframeResponse
//***********************************************************
void CallbackServer::processDataframeResponse(CHAR (&pData)[data_buffer_size])
{
    // Local variables
    CHAR szDataFrameFile[256]; // Filepath is capped at 256 bytes
    INT32 nImageType = 0;       // ImageType
    INT32 nPages = 0;           // Pages
    INT32 nImageWidth = 0;      // ImageWidth
    INT32 nImageHeight = 0;     // ImageHeight

    // Parse Message
    s_vTmpRet = memcpy(&szDataFrameFile, &pData[0],   256);
    s_vTmpRet = memcpy(&nImageType,     &pData[256], sizeof(INT32));
    s_vTmpRet = memcpy(&nPages,         &pData[260], sizeof(INT32));
    s_vTmpRet = memcpy(&nImageWidth,    &pData[264], sizeof(INT32));
    s_vTmpRet = memcpy(&nImageHeight,   &pData[268], sizeof(INT32));

    // Null Terminate string
    szDataFrameFile[255] = 0;

    // Print out response data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("DATAFRAME RESPONSE \n");
    s_nTmpRet = printf("Dataframe Filename: %s\n", szDataFrameFile);
    // Switch on Type
    switch (nImageType)
    {
    case 0:
        // Error
        s_nTmpRet = printf("Error in Image Type\n");
        break;
    case 1:
        // Bitmap
        s_nTmpRet = printf("Image Type: Bitmap\n");
        break;
    case 2:
        // Icon
        s_nTmpRet = printf("Image Type: Icon\n");
        break;
    case 3:
        // JPEG
        s_nTmpRet = printf("Image Type: JPEG\n");
        break;
    case 4:
        // JPEG 2000 (.j2k)
        s_nTmpRet = printf("Image Type: JPEG 2000 .j2k file\n");
        break;
    case 5:
        // JPEG 2000 (.jp2)
        s_nTmpRet = printf("Image Type: JPEG 2000 .j2p file\n");
        break;
    case 6:
        // PDF
        s_nTmpRet = printf("Image Type: PDF\n");
        break;
    case 7:
        // TIFF
        s_nTmpRet = printf("Image Type: TIFF\n");
        break;
    case 8:
        // PNG
        s_nTmpRet = printf("Image Type: PNG\n");
        break;
    default:
        s_nTmpRet = printf("Unsupported Image Type: %d\n", nImageType);
        break;
    }
    s_nTmpRet = printf("Number of Pages: %d\n", nPages);
    s_nTmpRet = printf("Image Width: %d\n", nImageWidth);
    s_nTmpRet = printf("Image Height: %d\n", nImageHeight);
    s_nTmpRet = printf("*********************************\n");
}

//***********************************************************
//* ProcessMGRSConversionResponse
//***********************************************************
void CallbackServer::processMGRSConversionResponse(CHAR (&pData)[data_buffer_size])
{
    // Local Variables
    INT32 nConversionResponse = 0;      // ConversionResponse
    FLOAT64 dLonOrScreenX = 0.0;        // LonOrScreenX
    FLOAT64 dLatOrScreenY = 0.0;        // LatOrScreenY
    CHAR szMGRSCode[32];                // MGRSCode

    // Clear buffer
    s_vTmpRet = memset(&szMGRSCode, 0, 32);

    // Parse incoming data
    s_vTmpRet = memcpy(&nConversionResponse, &pData[0],  sizeof(INT32));
    s_vTmpRet = memcpy(&dLonOrScreenX,       &pData[4],  sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dLatOrScreenY,       &pData[12], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&szMGRSCode,           &pData[20], 32);

    // Null terminate string
    szMGRSCode[31] = 0;

    // CONVERSION RESPONSE CODE:
    // 10: Invalid Request made. This will echo back the parameters that came from the invalid request.
    // 11: Valid MGRS Code Conversion from X,Y or Lat,Lon pair.
    // 12: Valid Lat, Lon Conversion from MGRS Code.

    // Print out response data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("MGRS CONVERSION RESPONSE \n");
    s_nTmpRet = printf("Conversion Response Code: %d\n", nConversionResponse);
    s_nTmpRet = printf("X coordinate or Longitude: %lf\n", dLonOrScreenX);
    s_nTmpRet = printf("Y coordinate or Latitude: %lf\n", dLatOrScreenY);
    s_nTmpRet = printf("MGRS Code: %s\n", szMGRSCode);
    s_nTmpRet = printf("*********************************\n");

    // Give the recieved MGRS code to the Sample_Request to do a MGRS to Geo conversion.
    //Sample_Request::SetMGRSCode(szMGRSCode);
}

//***********************************************************
//* ProcessDMSConversionResponse
//***********************************************************
void CallbackServer::processDMSConversionResponse(CHAR (&pData)[data_buffer_size])
{
    // Local Variables
    INT32 nConversionResponse = 0;          // ConversionResponse
    FLOAT64 dLonOrScreenX = 0.0;            // LonOrScreenX
    FLOAT64 dLatOrScreenY = 0.0;            // LatOrScreenY
    INT32 nDegreesLatitude = 0;             // DegreesLatitude
    INT32 nMinutesLatitude = 0;             // MinutesLatitude
    FLOAT64 dSecondsLatitude = 0;           // SecondsLatitude
    INT32 nDegreesLongitude = 0;            // DegreesLongitude
    INT32 nMinutesLongitude = 0;            // MinutesLongitude
    FLOAT64 dSecondsLongitude = 0;          // SecondsLongitude
    INT32 nOutputFormat = 0;                // OutputFormat
    CHAR szDMSCode[32];                     // DMSCode

    // Clear buffer
    s_vTmpRet = memset(&szDMSCode, 0, 32);

    // Parse incoming data
    s_vTmpRet = memcpy(&nConversionResponse, &pData[0], sizeof(INT32));
    s_vTmpRet = memcpy(&dLonOrScreenX, &pData[4], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&dLatOrScreenY, &pData[12], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nDegreesLatitude, &pData[20], sizeof(INT32));
    s_vTmpRet = memcpy(&nMinutesLatitude, &pData[24], sizeof(INT32));
    s_vTmpRet = memcpy(&dSecondsLatitude, &pData[28], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nDegreesLongitude, &pData[36], sizeof(INT32));
    s_vTmpRet = memcpy(&nMinutesLongitude, &pData[40], sizeof(INT32));
    s_vTmpRet = memcpy(&dSecondsLongitude, &pData[44], sizeof(FLOAT64));
    s_vTmpRet = memcpy(&nOutputFormat, &pData[52], sizeof(INT32));
    s_vTmpRet = memcpy(&szDMSCode, &pData[56], 32);

    // Null terminate string
    szDMSCode[31] = 0;

    // CONVERSION RESPONSE CODE:
    // 10: Invalid Request made. This will echo back the parameters that came from the invalid request.
    // 11: Valid MGRS Code Conversion from X,Y or Lat,Lon pair.
    // 12: Valid Lat, Lon Conversion from MGRS Code.

    // Print out response data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("Decimal degrees to DMS conversion  \n");
    s_nTmpRet = printf("Conversion Response Code: %d\n", nConversionResponse);
    s_nTmpRet = printf("Degrees Latitude: %i\n", nDegreesLatitude);
    s_nTmpRet = printf("Minutes Latitude: %i\n", nMinutesLatitude);
    s_nTmpRet = printf("Seconds Latitude: %i\n", dSecondsLatitude);
    s_nTmpRet = printf("Degrees Longitude: %i\n", nDegreesLongitude);
    s_nTmpRet = printf("Minutes Longitude: %i\n", nMinutesLongitude);
    s_nTmpRet = printf("Seconds Longitude: %i\n", dSecondsLongitude);
    s_nTmpRet = printf("DMS Code: %s\n", szDMSCode);
    s_nTmpRet = printf("*********************************\n");

    // Give the recieved MGRS code to the Sample_Request to do a MGRS to Geo conversion.
    //Sample_Request::SetMGRSCode(szDMSCode);
}

//***********************************************************
//* ProcessMapStatusResponse
//***********************************************************
void CallbackServer::processMapStatusResponse(CHAR (&pData)[data_buffer_size])
{
    // Local Variables
    INT32 nUnderlayTilesAvail = 0;          // UnderlayTilesAvail
    INT32 nUnderlayTileStatus = 0;          // UnderlayTileStatus
    INT32 nElevationTileAvail = 0;          // ElevationTileAvail
    INT32 nElevationTileStatus = 0;         // ElevationTileStatus
    INT32 nPerspectiveTilesAvail = 0;       // PerspectiveTilesAvail
    INT32 nPerspectiveTilesStatus = 0;      // PerspectiveTilesStatus
    INT32 nThreatPenetrated = 0;            // ThreatPenetrated
    INT32 nFrameCount = 0;                  // FrameCount
    INT32 nElapsedTime = 0;                 // ElapsedTime
    INT32 nPredefinedThreatCount = 0;       // PredefinedThreatCount
    INT32 nThreatMaskCount = 0;             // ThreatMaskCount
    INT32 nThreatRingCount = 0;             // ThreatRingCount
    INT32 nThreatSymbolCount = 0;           // ThreatSymbolCount
    INT32 nAFDSymbolCount = 0;              // AFDSymbolCount
    INT32 nKeyholeSymbolCount = 0;          // KeyholeSymbolCount
    INT32 nTacticalSymbolCount = 0;         // TacticalSymbolCount
    INT32 nUserGeoSymbolCount = 0;          // UserGeoSymbolCount
    INT32 nVOSymbolCount = 0;               // VOSymbolCount
    INT32 nDrawingSymbolCount = 0;          // DrawingSymbolCount
    INT32 nMCHUMSymbolCount = 0;            // MCHUMSymbolCount
    INT32 nLocalPtSymbolCount = 0;          // LocalPtSymbolCount
    INT32 nARINCSymbolCount = 0;            // ARINCSymbolCount
    INT32 nDAFIFSymbolCount = 0;            // DAFIFSymbolCount
    INT32 nAirspaceSymbolCount = 0;         // AirspaceSymbolCount
    INT32 nVehicleObjCount = 0;             // VehicleObjCount
    INT32 nRouteObjCount = 0;               // RouteObjCount
    INT32 nShapefileObjCount = 0;           // ShapefileObjCount
    INT32 nStormscopeObjCount = 0;          // StormscopeObjCount


    //// Clear buffer
    //memset(&szDMSCode, 0, 32);

    // Parse incoming data
    s_vTmpRet = memcpy(&nUnderlayTilesAvail, &pData[0], sizeof(INT32));
    s_vTmpRet = memcpy(&nUnderlayTileStatus, &pData[4], sizeof(INT32));
    s_vTmpRet = memcpy(&nElevationTileAvail, &pData[8], sizeof(INT32));
    s_vTmpRet = memcpy(&nElevationTileStatus, &pData[12], sizeof(INT32));
    s_vTmpRet = memcpy(&nPerspectiveTilesAvail, &pData[16], sizeof(INT32));
    s_vTmpRet = memcpy(&nPerspectiveTilesStatus, &pData[20], sizeof(INT32));
    s_vTmpRet = memcpy(&nThreatPenetrated, &pData[24], sizeof(INT32));
    s_vTmpRet = memcpy(&nFrameCount, &pData[28], sizeof(INT32));
    s_vTmpRet = memcpy(&nElapsedTime, &pData[32], sizeof(INT32));
    s_vTmpRet = memcpy(&nPredefinedThreatCount, &pData[36], sizeof(INT32));
    s_vTmpRet = memcpy(&nThreatMaskCount, &pData[40], sizeof(INT32));
    s_vTmpRet = memcpy(&nThreatRingCount, &pData[44], sizeof(INT32));
    s_vTmpRet = memcpy(&nThreatSymbolCount, &pData[48], sizeof(INT32));
    s_vTmpRet = memcpy(&nAFDSymbolCount, &pData[52], sizeof(INT32));
    s_vTmpRet = memcpy(&nKeyholeSymbolCount, &pData[56], sizeof(INT32));
    s_vTmpRet = memcpy(&nTacticalSymbolCount, &pData[60], sizeof(INT32));
    s_vTmpRet = memcpy(&nUserGeoSymbolCount, &pData[64], sizeof(INT32));
    s_vTmpRet = memcpy(&nVOSymbolCount, &pData[68], sizeof(INT32));
    s_vTmpRet = memcpy(&nDrawingSymbolCount, &pData[72], sizeof(INT32));
    s_vTmpRet = memcpy(&nMCHUMSymbolCount, &pData[76], sizeof(INT32));
    s_vTmpRet = memcpy(&nLocalPtSymbolCount, &pData[80], sizeof(INT32));
    s_vTmpRet = memcpy(&nARINCSymbolCount, &pData[84], sizeof(INT32));
    s_vTmpRet = memcpy(&nDAFIFSymbolCount, &pData[88], sizeof(INT32));
    s_vTmpRet = memcpy(&nAirspaceSymbolCount, &pData[92], sizeof(INT32));
    s_vTmpRet = memcpy(&nVehicleObjCount, &pData[96], sizeof(INT32));
    s_vTmpRet = memcpy(&nRouteObjCount, &pData[100], sizeof(INT32));
    s_vTmpRet = memcpy(&nShapefileObjCount, &pData[104], sizeof(INT32));
    s_vTmpRet = memcpy(&nStormscopeObjCount, &pData[108], sizeof(INT32));



    //// Null terminate string
    //szDMSCode[31] = 0;

    // CONVERSION RESPONSE CODE:
    // 10: Invalid Request made. This will echo back the parameters that came from the invalid request.
    // 11: Valid MGRS Code Conversion from X,Y or Lat,Lon pair.
    // 12: Valid Lat, Lon Conversion from MGRS Code.

    // Print out response data
    s_nTmpRet = printf("*********************************\n");
    s_nTmpRet = printf("Map Status  \n");
    s_nTmpRet = printf("Underlay Tiles Available: %d\n", nUnderlayTilesAvail);
    s_nTmpRet = printf("Underlay Tile Status: %d\n", nUnderlayTileStatus);
    s_nTmpRet = printf("Elevation Tiles Available: %d\n", nElevationTileAvail);
    s_nTmpRet = printf("Elevation Tile Status: %d\n", nElevationTileAvail);
    s_nTmpRet = printf("Perspective Tiles Available: %d\n", nPerspectiveTilesAvail);
    s_nTmpRet = printf("Perspective Tile Status: %d\n", nPerspectiveTilesStatus);
    s_nTmpRet = printf("Threat Penetrated: %d\n", nThreatPenetrated);
    s_nTmpRet = printf("Frame Count: %d\n", nFrameCount);
    s_nTmpRet = printf("Elapsed Time: %d\n", nElapsedTime);
    s_nTmpRet = printf("Predefined Threat Count: %d\n", nPredefinedThreatCount);
    s_nTmpRet = printf("Threat Mask Count: %d\n", nThreatMaskCount);
    s_nTmpRet = printf("Threat Ring Count: %d\n", nThreatRingCount);
    s_nTmpRet = printf("Threat Symbol Count: %d\n", nThreatSymbolCount);
    s_nTmpRet = printf("AFD Symbol Count: %d\n", nAFDSymbolCount);
    s_nTmpRet = printf("Keyhole Symbol Count: %d\n", nKeyholeSymbolCount);
    s_nTmpRet = printf("Tactical Symbol Count: %d\n", nTacticalSymbolCount);
    s_nTmpRet = printf("User Geo Symbol Count: %d\n", nUserGeoSymbolCount);
    s_nTmpRet = printf("VO Symbol Count: %d\n", nVOSymbolCount);
    s_nTmpRet = printf("Drawing Symbol Count: %d\n", nDrawingSymbolCount);
    s_nTmpRet = printf("MCHUM Symbol Count: %d\n", nMCHUMSymbolCount);
    s_nTmpRet = printf("Local Point Symbol Count: %d\n", nLocalPtSymbolCount);
    s_nTmpRet = printf("ARINC Symbol Count: %d\n", nARINCSymbolCount);
    s_nTmpRet = printf("DAFIF Symbol Count: %d\n", nAirspaceSymbolCount);
    s_nTmpRet = printf("Vehicle Object Count: %d\n", nVehicleObjCount);
    s_nTmpRet = printf("Route Object Count: %d\n", nRouteObjCount);
    s_nTmpRet = printf("Shapefile Object Count: %d\n", nShapefileObjCount);
    s_nTmpRet = printf("Stormscope Object Count: %d\n", nStormscopeObjCount);
    s_nTmpRet = printf("*********************************\n");

    // Give the recieved MGRS code to the Sample_Request to do a MGRS to Geo conversion.
    //Sample_Request::SetMGRSCode(szDMSCode);
}

//***********************************************************
//* END RESPONSE PROCESSING FUNCTIONS.
//***********************************************************

//***********************************************************
//* SwapBytes
//***********************************************************
void CallbackServer::swapBytes(INT32& pValue)
{
    *(long*)pValue = ((*(long*)pValue & 0x000000FFU) << 24) +
        ((*(long*)pValue & 0x0000FF00U) << 8) +
        ((*(long*)pValue & 0x00FF0000U) >> 8) +
        ((*(long*)pValue & 0xFF000000U) >> 24);
}
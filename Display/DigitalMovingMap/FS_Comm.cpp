//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Commercial Computer Software - Non-deliverable Source Code
// See FAR 52.227-19(c)
// The rights of the Government regarding use, reproduction and disclosure are
// as set forth in the applicable FliteScene contract.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Copyright (C) Harris Corporation 2017 - All Rights Reserved
//*****************************************************************************
// FILE:            FS_Comm.cpp
//
// CLASSIFICATION:  Unclassified
//
// DESCRIPTION:     Refer to FS_Comm.h
//
// LIMITATIONS:     none
//
// SOFTWARE HISTORY:
//
//     See ClearCase (cleartool lshistory)
//
//*****************************************************************************

#define _CRT_SECURE_NO_WARNINGS // temp - for strncpy deprecation errors

#include <stdarg.h>                 // For va_list.
#include <string.h>                 // For memset.
#include "FS_Comm.h"
#include "FS_Constants.h"           // For ICD Constants.
#include "FliteScene.h"


//*****************************************************************************
// FliteScene Message Header Constants.
//*****************************************************************************
static const int ENDIAN_FLAG  = 0x41424344;
static const int RESERVED     = 0;

//*****************************************************************************
// FS_Comm::SwapEndianess_32
//*****************************************************************************
void FS_Comm::SwapEndianess_32(void * pValue)
{
        *(FS_uint32*)pValue = ((*(FS_uint32*)pValue & 0x000000FFU) << 24) +
                          ((*(FS_uint32*)pValue & 0x0000FF00U) <<  8) +
                          ((*(FS_uint32*)pValue & 0x00FF0000U) >>  8) +
                          ((*(FS_uint32*)pValue & 0xFF000000U) >> 24);
}

//*****************************************************************************
// FS_Comm::SwapEndianess_64
//*****************************************************************************
void FS_Comm::SwapEndianess_64(void * pValue)
{
    FS_uint32* arValue = static_cast<FS_uint32*>(pValue);
    FS_uint32  nValue0 = arValue[0];
    FS_uint32  nValue1 = arValue[1];
    SwapEndianess_32(&nValue0);
    SwapEndianess_32(&nValue1);
    arValue[0] = nValue1;
    arValue[1] = nValue0;
}

//*****************************************************************************
// FS_Comm::PackHeader
//*****************************************************************************
void FS_Comm::PackHeader(void* pBuffer, int nSize, int nChannel, int nId, int nVersion)
{
    char* pHeader = reinterpret_cast<char*>(pBuffer);
    memcpy(&pHeader[0],  &ENDIAN_FLAG, SIZEOFINT);
    memcpy(&pHeader[4],  &nSize,       SIZEOFINT);
    memcpy(&pHeader[8],  &nChannel,    SIZEOFINT);
    memcpy(&pHeader[12], &nId,         SIZEOFINT);
    memcpy(&pHeader[16], &nVersion,    SIZEOFINT);
}

//*****************************************************************************
// FS_Comm::SendMsg
//*****************************************************************************
void FS_Comm::SendMsg(int nChannel, int nId, void * pHeader, void * pMessage)
{
    FS_Set_Message(nChannel, nId, pHeader, pMessage);
}

//*****************************************************************************
// FS_Comm::GetMessageEndian
//*****************************************************************************
int FS_Comm::GetMessageEndian(const void* pMessage)
{
    int nValue = 0;
    const char* pHeader = reinterpret_cast<const char*>(pMessage);
    memcpy(&nValue, &pHeader[0], 4);
    return nValue;
}

//*****************************************************************************
// FS_Comm::GetMessageChannel
//*****************************************************************************
int FS_Comm::GetMessageChannel(const void* pMessage)
{
    int nEndian = 0;
    int nChannel = 0;
    const char* pHeader = reinterpret_cast<const char*>(pMessage);

    memcpy(&nEndian, &pHeader[0], 4);
    memcpy(&nChannel, &pHeader[8], 4);

    if (nEndian != ENDIAN_FLAG)
    {
        SwapEndianess_32(&nChannel);
    }

    return nChannel;
}

//*****************************************************************************
// FS_Comm::GetMessageId
//*****************************************************************************
int FS_Comm::GetMessageId(const void* pMessage)
{
    int nEndian = 0;
    int nMsgId = 0;
    const char* pHeader = reinterpret_cast<const char*>(pMessage);

    memcpy(&nEndian, &pHeader[0], 4);
    memcpy(&nMsgId, &pHeader[12], 4);

    if (nEndian != ENDIAN_FLAG)
    {
        SwapEndianess_32(&nMsgId);
    }

    return nMsgId;
}

//*****************************************************************************
// SendMsg_Viewport
//*****************************************************************************
void FS_Comm::SendMsg_Viewport(int nChannel,
                               int nViewportIndex,
                               int nEnableFlag,
                               int nViewportLowerLeftX,
                               int nViewportLowerLeftY,
                               int nViewportWidth,
                               int nViewportHeight)
{
    const int MSG_SIZE = 24;
    const int MSG_ID   =  3;
    const int MSG_VER  =  2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nViewportIndex, SIZEOFINT);
    memcpy(&pMessage[ 4], &nEnableFlag, SIZEOFINT);
    memcpy(&pMessage[ 8], &nViewportLowerLeftX, SIZEOFINT);
    memcpy(&pMessage[12], &nViewportLowerLeftY, SIZEOFINT);
    memcpy(&pMessage[16], &nViewportWidth, SIZEOFINT);
    memcpy(&pMessage[20], &nViewportHeight, SIZEOFINT);

    // Send the message
    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TIVAltitudeTable
//*****************************************************************************
void FS_Comm::SendMsg_TIVAltitudeTable(int nChannel, const void* pTable)
{
    const int MSG_SIZE = 1020;
    const int MSG_ID   =    4;
    const int MSG_VER  =    1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], pTable, MSG_SIZE);

    // Send the message
    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_EBAltitudeTable
//*****************************************************************************
void FS_Comm::SendMsg_EBAltitudeTable(int nChannel, const void* pTable)
{
    const int MSG_SIZE = 1020;
    const int MSG_ID   =    5;
    const int MSG_VER  =    1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], pTable, MSG_SIZE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Mode
//*****************************************************************************
void FS_Comm::SendMsg_Mode(int         nChannel,
                           int         nMode,
                           const char* szProductCode,
                           double      dRange)
{
    const int MSG_SIZE = 16;
    const int MSG_ID   =  6;
    const int MSG_VER  =  2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nMode, SIZEOFINT);
    memcpy(&pMessage[4], &szProductCode[0], SIZEOFINT);
    memcpy(&pMessage[8], &dRange, SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_FlightDynamics
//*****************************************************************************
void FS_Comm::SendMsg_FlightDynamics(int nVehicle, int nCount, ...)
{
    int nMsgSize       = 0;
    const int MSG_ID   = 7;
    const int MSG_VER  = 4;
    const int MAX_SIZE = 1024;
    char pHeader[HDR_SIZE];
    unsigned char pMessage[MAX_SIZE];

    int    nIndex = 0;
    int    nParameterCode = 0;
    int    nParameterValue = 0;
    double dParameterValue = 0;

    // Prime the Variable Argument List
    va_list hParamList;
    va_start(hParamList, nCount);

    memcpy(&pMessage[nMsgSize], &nVehicle, SIZEOFINT);
    nMsgSize += 4;

    for (nIndex = 0; nIndex < nCount; ++nIndex)
    {
        nParameterCode = va_arg(hParamList, int);
        memcpy(&pMessage[nMsgSize], &nParameterCode, SIZEOFINT);
        nMsgSize += 4;

        switch (nParameterCode)
        {
        case FS_Constants::LATITUDE:  // Intentional Fall
        case FS_Constants::LONGITUDE: // Intentional Fall
        case FS_Constants::HEADING:   // Intentional Fall
        case FS_Constants::PITCH:     // Intentional Fall
        case FS_Constants::ROLL:      // Intentional Fall
        case FS_Constants::VELOCITY:  // Intentional Fall
        case FS_Constants::TURN_RATE: // Intentional Fall
        case FS_Constants::ALTITUDE_F: // Parameter is double.
            dParameterValue = va_arg(hParamList, double);
            memcpy(&pMessage[nMsgSize], &dParameterValue, SIZEOFDOUBLE);
            nMsgSize += 8;
            break;

        case FS_Constants::ALTITUDE:  // Parameter is integer.
            nParameterValue = va_arg(hParamList, int);
            memcpy(&pMessage[nMsgSize], &nParameterValue, SIZEOFINT);
            nMsgSize += 4;
            break;

        default:
            // No appropriate action to take!
            break;
        }
    }
    va_end(hParamList);

    // Populate the message header
    PackHeader(pHeader, nMsgSize, RESERVED, MSG_ID, MSG_VER);

    // Send the Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Zoom
//*****************************************************************************
void FS_Comm::SendMsg_Zoom(int nChannel, double dZoom)
{
    const int MSG_SIZE = 8;
    const int MSG_ID   = 8;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &dZoom, SIZEOFDOUBLE);

    // Send the message
    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Decenter
//*****************************************************************************
void FS_Comm::SendMsg_Decenter(int nChannel, double dX, double dY)
{
    const int MSG_SIZE = 16;
    const int MSG_ID   =  9;
    const int MSG_VER  =  1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &dX, SIZEOFDOUBLE);
    memcpy(&pMessage[8], &dY, SIZEOFDOUBLE);

    // Send the message
    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_DataFrameControl
//*****************************************************************************
void FS_Comm::SendMsg_DataFrameControl(int         nChannel,
                                       int         nScreenPositionX,
                                       int         nScreenPositionY,
                                       double      dOrientation,
                                       double      dZoom,
                                       const char* szFilename)
{
    const int MSG_SIZE = 280;
    const int MSG_ID   =  10;
    const int MSG_VER  =   1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nScreenPositionX, SIZEOFINT);
    memcpy(&pMessage[ 4], &nScreenPositionY, SIZEOFINT);
    memcpy(&pMessage[ 8], &dOrientation, SIZEOFDOUBLE);
    memcpy(&pMessage[16], &dZoom, SIZEOFDOUBLE);
    strncpy(&pMessage[24], szFilename, 255);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_OverlaySelect
//*****************************************************************************
void FS_Comm::SendMsg_OverlaySelect(int nChannel, int nEnable, int nOverlay)
{
    const int MSG_SIZE =  8;
    const int MSG_ID   = 11;
    const int MSG_VER  =  2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nEnable, SIZEOFINT);
    memcpy(&pMessage[4], &nOverlay, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_OverlayColors
//*****************************************************************************
void FS_Comm::SendMsg_OverlayColors(int nChannel,
                                    int nColorID,
                                    int nRedValue,
                                    int nGreenValue,
                                    int nBlueValue,
                                    int nAlphaValue)
{
    const int MSG_SIZE = 20;
    const int MSG_ID   = 12;
    const int MSG_VER  =  1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nColorID, SIZEOFINT);
    memcpy(&pMessage[ 4], &nRedValue, SIZEOFINT);
    memcpy(&pMessage[ 8], &nGreenValue, SIZEOFINT);
    memcpy(&pMessage[12], &nBlueValue, SIZEOFINT);
    memcpy(&pMessage[16], &nAlphaValue, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SlopeShadingControl
//*****************************************************************************
void FS_Comm::SendMsg_SlopeShadingControl(int nChannel, int nSelect, double dAzimuth)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 13;
    const int MSG_VER  =  1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nSelect, SIZEOFINT);
    memcpy(&pMessage[ 4], &dAzimuth, SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_ContourLineControl
//*****************************************************************************
void FS_Comm::SendMsg_ContourLineControl(int nChannel, double dBase, double dSpacing)
{
    const int MSG_SIZE =  16;
    const int MSG_ID   = 14;
    const int MSG_VER  =  2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &dBase, SIZEOFDOUBLE);
    memcpy(&pMessage[ 8], &dSpacing, SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_ElevationBandsControl
//*****************************************************************************
void FS_Comm::SendMsg_ElevationBandsControl(int nChannel,
                                            int nDeltaHeight1,
                                            int nDeltaHeight2,
                                            int nDeltaHeight3,
                                            int nDeltaHeight4,
                                            int nDeltaHeight5,
                                            int nDeltaHeight6,
                                            int nDeltaHeight7)
{
    const int MSG_SIZE = 28;
    const int MSG_ID   = 15;
    const int MSG_VER  =  1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nDeltaHeight1, SIZEOFINT);
    memcpy(&pMessage[ 4], &nDeltaHeight2, SIZEOFINT);
    memcpy(&pMessage[ 8], &nDeltaHeight3, SIZEOFINT);
    memcpy(&pMessage[12], &nDeltaHeight4, SIZEOFINT);
    memcpy(&pMessage[16], &nDeltaHeight5, SIZEOFINT);
    memcpy(&pMessage[20], &nDeltaHeight6, SIZEOFINT);
    memcpy(&pMessage[24], &nDeltaHeight7, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Threat
//*****************************************************************************
void FS_Comm::SendMsg_Threat(const int nAction,
                             const int nIndex,
                             const int nTIVSelect,
                             const double dLat,
                             const double dLon,
                             const double dRectangleWidth,
                             const double dRectangleLat1,
                             const double dRectangleLon1,
                             const double dRectangleLat2,
                             const double dRectangleLon2,
                             const int nTIVColorFlag,
                             const int nRed,
                             const int nGreen,
                             const int nBlue,
                             const int nAlpha,
                             const char * szLabel,
                             const int nType,
                             const double dMagnification,
                             const int nUseOtherParams,
                             const double dDetectRange,
                             const double dEngageRange,
                             const int nHeight,
                             const char * szIconFilename,
                             const char * szMIL_STD2525_Code)
{
    const int MSG_SIZE = 332;
    const int MSG_ID   =  16;
    const int MSG_VER  =   5;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nAction, SIZEOFINT);
    memcpy(&pMessage[  4], &nIndex, SIZEOFINT);
    memcpy(&pMessage[  8], &nTIVSelect, SIZEOFINT);
    memcpy(&pMessage[ 12], &dLat, SIZEOFDOUBLE);
    memcpy(&pMessage[ 20], &dLon, SIZEOFDOUBLE);
    memcpy(&pMessage[ 28], &dRectangleWidth, SIZEOFDOUBLE);
    memcpy(&pMessage[ 36], &dRectangleLat1, SIZEOFDOUBLE);
    memcpy(&pMessage[ 44], &dRectangleLon1, SIZEOFDOUBLE);
    memcpy(&pMessage[ 52], &dRectangleLat2, SIZEOFDOUBLE);
    memcpy(&pMessage[ 60], &dRectangleLon2, SIZEOFDOUBLE);
    memcpy(&pMessage[ 68], &nTIVColorFlag, SIZEOFINT);
    memcpy(&pMessage[ 72], &nRed, SIZEOFINT);
    memcpy(&pMessage[ 76], &nGreen, SIZEOFINT);
    memcpy(&pMessage[ 80], &nBlue, SIZEOFINT);
    memcpy(&pMessage[ 84], &nAlpha, SIZEOFINT);
    strncpy(&pMessage[88], szLabel, 64);
    pMessage[88 + 64 - 1] = 0; // Null-Terminated.
    memcpy(&pMessage[152], &nType, SIZEOFINT);
    memcpy(&pMessage[156], &dMagnification, SIZEOFDOUBLE);
    memcpy(&pMessage[164], &nUseOtherParams, SIZEOFINT);
    memcpy(&pMessage[168], &dDetectRange, SIZEOFDOUBLE);
    memcpy(&pMessage[176], &dEngageRange, SIZEOFDOUBLE);
    memcpy(&pMessage[184], &nHeight, SIZEOFINT);
    strncpy(&pMessage[188], szIconFilename, 128);
    pMessage[188 + 128 - 1] = 0; // Null-Terminated.
    strncpy(&pMessage[316], szMIL_STD2525_Code, 16);
    pMessage[316 + 16 - 1] = 0; // Null-Terminated.



    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_GeoChip
//*****************************************************************************
void FS_Comm::SendMsg_GeoChip(int         nChannel,
                              int         nActionType,
                              int         nGeoChipID,
                              double      dGeoChipLatitude1,
                              double      dGeoChipLongitude1,
                              double      dGeoChipLatitude2,
                              double      dGeoChipLongitude2,
                              double      dDiscernableFactor,
                              const char* szFilename)
{
    const int MSG_SIZE = 304;
    const int MSG_ID   =  17;
    const int MSG_VER  =   1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nActionType, SIZEOFINT);
    memcpy(&pMessage[  4], &nGeoChipID, SIZEOFINT);
    memcpy(&pMessage[  8], &dGeoChipLatitude1, SIZEOFDOUBLE);
    memcpy(&pMessage[ 16], &dGeoChipLongitude1, SIZEOFDOUBLE);
    memcpy(&pMessage[ 24], &dGeoChipLatitude2, SIZEOFDOUBLE);
    memcpy(&pMessage[ 32], &dGeoChipLongitude2, SIZEOFDOUBLE);
    memcpy(&pMessage[ 40], &dDiscernableFactor, SIZEOFDOUBLE);
    strncpy(&pMessage[ 48], szFilename, 256);
    pMessage[48 + 256 - 1] = 0; // Null-Terminated.

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_GeoQuery
//*****************************************************************************
void FS_Comm::SendMsg_GeoQuery(int    nChannel,
                               int    nKey,
                               int    nInputData,
                               int    nOutputData,
                               double dScreenX,
                               double dScreenY,
                               double dLatitude,
                               double dLongitude)
{
    const int MSG_SIZE = 44;
    const int MSG_ID   = 18;
    const int MSG_VER  =  2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nKey,        SIZEOFINT);
    memcpy(&pMessage[  4], &nInputData,  SIZEOFINT);
    memcpy(&pMessage[  8], &nOutputData, SIZEOFINT);
    memcpy(&pMessage[ 12], &dScreenX,    SIZEOFDOUBLE);
    memcpy(&pMessage[ 20], &dScreenY,    SIZEOFDOUBLE);
    memcpy(&pMessage[ 28], &dLatitude,   SIZEOFDOUBLE);
    memcpy(&pMessage[ 36], &dLongitude,  SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Get_Status
//*****************************************************************************
void FS_Comm::SendMsg_Get_Status(int nChannel)
{
    const int MSG_SIZE = 0;
    const int MSG_ID   = 20;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[4] = { 0, 0, 0, };

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Send the Message
    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Get_Version_ID
//*****************************************************************************
void FS_Comm::SendMsg_Get_Version_ID()
{
    const int MSG_SIZE = 0;
    const int MSG_ID   = 22;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[4] = { 0, 0, 0, };

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Send the Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TestData
//*****************************************************************************
void FS_Comm::SendMsg_TestData(int nChannel, int nType, const char* szTestData)
{
    const int MSG_SIZE = 260;
    const int MSG_ID   =  24;
    const int MSG_VER  =   1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nType, SIZEOFINT);
    strncpy(&pMessage[4], szTestData, 256);
    pMessage[4 + 256 - 1] = 0; // Null-Terminated.

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_RefreshCache
//*****************************************************************************
void FS_Comm::SendMsg_RefreshCache(int nUnderlay, int nElevation, int nGeoChip)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 26;
    const int MSG_VER  =  1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header1
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nUnderlay, SIZEOFINT);
    memcpy(&pMessage[4], &nElevation, SIZEOFINT);
    memcpy(&pMessage[8], &nGeoChip, SIZEOFINT);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Shutdown
//*****************************************************************************
void FS_Comm::SendMsg_Shutdown()
{
    const int MSG_SIZE =  0;
    const int MSG_ID   = 27;
    const int MSG_VER  =  1;
    char pHeader[HDR_SIZE];
    char pMessage[4] = { 0, 0, 0, };

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetTacticalSymbol
// Msg will be deprecated in future FliteScene release, 
// so use SendMsg_SetTacticalGraphic instead
//*****************************************************************************
void FS_Comm::SendMsg_SetTacticalSymbol(int         nSymbolIndex,
                                        double      dLatitude,
                                        double      dLongitude,
                                        int         nAltitude,
                                        double      dMagnification,
                                        double      dOrientation,
                                        int         nDirectionOfMovementEnable,
                                        double      dDirectionOfMovementAngle,
                                        const char* szCharacterCode,
                                        const char* szTextLabel)
{
    const int MSG_SIZE = 132;
    const int MSG_ID   =  30;
    const int MSG_VER  =   4;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nSymbolIndex, SIZEOFINT);
    memcpy(&pMessage[  4], &dLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[ 12], &dLongitude, SIZEOFDOUBLE);
    memcpy(&pMessage[ 20], &nAltitude, SIZEOFINT);
    memcpy(&pMessage[ 24], &dMagnification, SIZEOFDOUBLE);
    memcpy(&pMessage[ 32], &dOrientation, SIZEOFDOUBLE);
    memcpy(&pMessage[ 40], &nDirectionOfMovementEnable, SIZEOFINT);
    memcpy(&pMessage[ 44], &dDirectionOfMovementAngle, SIZEOFDOUBLE);
    strncpy(&pMessage[52], szCharacterCode, 16);
    pMessage[52 + 16 - 1] = 0; // Null-Terminated.

    strncpy(&pMessage[68], szTextLabel, 64);
    pMessage[68 + 64 - 1] = 0; // Null-Terminated.

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetTacticalGraphic     
//*****************************************************************************
void FS_Comm::SendMsg_SetTacticalGraphic(
    int         nFSUID,
    int         nKey,
    const char* szSIDC,
    int         nModifierCount,
    char*       pModifierList,
    int         nPointCount,
    char*       pPointList,
    double      dMagnification,
    double      dOrentation,
    int         nDirectionOfMovementEnable,
    double      dDirectionOfMovementAngle)
{
    const int MSG_ID = 145;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];

    // This is the size of the message without including any of the points or modifiers
    const int BASE_MESSAGE_SIZE = 60;

    // 4 bytes for the code, 36 bytes for the text
    const int MODIFIER_BLOCK_SIZE = 40;

    // 8 bytes each for latitude, longitude, and altitude.
    const int POINT_BLOCK_SIZE = 24;

    // Calculate the size of the message
    int nMessageSize = BASE_MESSAGE_SIZE + (nModifierCount*MODIFIER_BLOCK_SIZE) + (nPointCount*POINT_BLOCK_SIZE);

    // Index variables
    int nMessageBufferIndex = 0;
    int nListIndex = 0;
    int i = 0;

    // Dynamically allocate memory variable message
    char* pMessage = new char[nMessageSize];

    // Check for a null pointer
    if (pMessage != 0)
    {
        // Pack the message header
        PackHeader(pHeader, nMessageSize, RESERVED, MSG_ID, MSG_VER);

        // Pack the Tactical Graphics Message
        // First read the FS UID, Key, and SIDC code
        memcpy(&pMessage[nMessageBufferIndex], &nFSUID, 4);
        nMessageBufferIndex += 4;
        memcpy(&pMessage[nMessageBufferIndex], &nKey, 4);
        nMessageBufferIndex += 4;
        memcpy(&pMessage[nMessageBufferIndex], &szSIDC[0], 16);
        nMessageBufferIndex += 16;

        // Read the Modifier count
        memcpy(&pMessage[nMessageBufferIndex], &nModifierCount, 4);
        nMessageBufferIndex += 4;

        // Loop through all the modifiers
        for (i = 0; i < nModifierCount; ++i)
        {
            // Copy the Modifier code from the list
            memcpy(&pMessage[nMessageBufferIndex], &pModifierList[nListIndex], 4);
            nListIndex += 4;
            nMessageBufferIndex += 4;

            // Copy the Modifier text from the list
            memcpy(&pMessage[nMessageBufferIndex], &pModifierList[nListIndex], 36);
            nListIndex += 36;
            nMessageBufferIndex += 36;
        }

        // Reset the list index to reuse the variable for the point list
        nListIndex = 0;

        // Read the Point count
        memcpy(&pMessage[nMessageBufferIndex], &nPointCount, 4);
        nMessageBufferIndex += 4;

        // Loop through all the points
        for (i = 0; i < nPointCount; ++i)
        {
            // Copy the latitude from the list
            memcpy(&pMessage[nMessageBufferIndex], &pPointList[nListIndex], 8);
            nListIndex += 8;
            nMessageBufferIndex += 8;

            // Copy the longitude from the list
            memcpy(&pMessage[nMessageBufferIndex], &pPointList[nListIndex], 8);
            nListIndex += 8;
            nMessageBufferIndex += 8;

            // Copy the altitude from the list
            memcpy(&pMessage[nMessageBufferIndex], &pPointList[nListIndex], 8);
            nListIndex += 8;
            nMessageBufferIndex += 8;
        }

        // Copy the Magnification, Orientation, Direction of Movement Enable, and Direction of Movement Angle.
        memcpy(&pMessage[nMessageBufferIndex], &dMagnification, 8);
        nMessageBufferIndex += 8;
        memcpy(&pMessage[nMessageBufferIndex], &dOrentation, 8);
        nMessageBufferIndex += 8;
        memcpy(&pMessage[nMessageBufferIndex], &nDirectionOfMovementEnable, 4);
        nMessageBufferIndex += 4;
        memcpy(&pMessage[nMessageBufferIndex], &dDirectionOfMovementAngle, 8);
        nMessageBufferIndex += 8;

        // Send the message
        SendMsg(RESERVED, MSG_ID, pHeader, pMessage);

        // Free valid memory allocation after using the message buffer
        delete[] pMessage;
    }

}

//*****************************************************************************
// SendMsg_SetVOParameters
//*****************************************************************************
void FS_Comm::SendMsg_SetVOParameters(int nChannel, int nHeight, int nSelect)
{
    const int MSG_SIZE =  8;
    const int MSG_ID   = 31;
    const int MSG_VER  =  1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nHeight, SIZEOFINT);
    memcpy(&pMessage[ 4], &nSelect, SIZEOFINT);

    // Send the Message
    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_LineofSightQuery
//*****************************************************************************
void FS_Comm::SendMsg_LineofSightQuery(int    nChannel,
                                       int    nKey,
                                       int    nInputDataType,
                                       double dX1,
                                       double dY1,
                                       double dElevation1,
                                       double dX2,
                                       double dY2,
                                       double dElevation2)
{
    const int MSG_SIZE = 48;
    const int MSG_ID   = 32;
    const int MSG_VER  =  3;
    const int nElevation1 = static_cast<int>(dElevation1);
    const int nElevation2 = static_cast<int>(dElevation2);
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nKey, SIZEOFINT);
    memcpy(&pMessage[ 4], &nInputDataType, SIZEOFINT);
    memcpy(&pMessage[ 8], &dX1, SIZEOFDOUBLE);
    memcpy(&pMessage[16], &dY1, SIZEOFDOUBLE);
    memcpy(&pMessage[24], &nElevation1, SIZEOFINT);
    memcpy(&pMessage[28], &dX2, SIZEOFDOUBLE);
    memcpy(&pMessage[36], &dY2, SIZEOFDOUBLE);
    memcpy(&pMessage[44], &nElevation2, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_PointofInterceptQuery
//*****************************************************************************
void FS_Comm::SendMsg_PointofInterceptQuery(int    nChannel,
                                            double dLatitude,
                                            double dLongitude,
                                            int    nElevation,
                                            double dBearing,
                                            double dPitch)
{
    const int MSG_SIZE = 36;
    const int MSG_ID   = 34;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &dLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[  8], &dLongitude, SIZEOFDOUBLE);
    memcpy(&pMessage[ 16], &nElevation, SIZEOFINT);
    memcpy(&pMessage[ 20], &dBearing, SIZEOFDOUBLE);
    memcpy(&pMessage[ 28], &dPitch, SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TrendDot
//*****************************************************************************
void FS_Comm::SendMsg_TrendDot(int nChannel,
                               int nVehicleID,
                               int nDot1_Time,
                               int nDot2_Time,
                               int nDot3_Time,
                               int nDot4_Time)
{
    const int MSG_SIZE = 20;
    const int MSG_ID   = 36;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nVehicleID, SIZEOFINT);
    memcpy(&pMessage[  4], &nDot1_Time, SIZEOFINT);
    memcpy(&pMessage[  8], &nDot2_Time, SIZEOFINT);
    memcpy(&pMessage[ 12], &nDot3_Time, SIZEOFINT);
    memcpy(&pMessage[ 16], &nDot4_Time, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Slew
//*****************************************************************************
void FS_Comm::SendMsg_Slew(int    nChannel,
                           int    nSlewHeadingEnabled,
                           double dSlewAngle,
                           int    nSlewPositionEnabled,
                           int    nSlewPositionType,
                           double dSlewX,
                           double dSlewY)
{
    const int MSG_SIZE = 36;
    const int MSG_ID   = 37;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nSlewHeadingEnabled, SIZEOFINT);
    memcpy(&pMessage[4], &dSlewAngle, SIZEOFDOUBLE);
    memcpy(&pMessage[12], &nSlewPositionEnabled, SIZEOFINT);
    memcpy(&pMessage[16], &nSlewPositionType, SIZEOFINT);
    memcpy(&pMessage[20], &dSlewX, SIZEOFDOUBLE);
    memcpy(&pMessage[28], &dSlewY, SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_CursorPosition
//*****************************************************************************
void FS_Comm::SendMsg_CursorAction(int    nChannel,
                                   int    nAction,
                                   int    nSelectType,
                                   double dX,
                                   double dY,
                                   int    nPositionUpdate,
                                   int    nVerticalRange,
                                   int    nHorizontalRange,
                                   int    nObjectID)
{
    const int MSG_SIZE = 40;
    const int MSG_ID   = 38;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nAction, SIZEOFINT);
    memcpy(&pMessage[  4], &nSelectType, SIZEOFINT);
    memcpy(&pMessage[  8], &dX, SIZEOFDOUBLE);
    memcpy(&pMessage[ 16], &dY, SIZEOFDOUBLE);
    memcpy(&pMessage[ 24], &nPositionUpdate, SIZEOFINT);
    memcpy(&pMessage[ 28], &nVerticalRange, SIZEOFINT);
    memcpy(&pMessage[ 32], &nHorizontalRange, SIZEOFINT);
    memcpy(&pMessage[ 36], &nObjectID, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_ScreenCapture
//*****************************************************************************
void FS_Comm::SendMsg_ScreenCapture(int nChannel,
                                    int nViewportIndex,
                                    int nViewportLowerLeftX,
                                    int nViewportLowerLeftY,
                                    int nViewportWidth,
                                    int nViewportHeight)
{
    const int MSG_SIZE = 20;
    const int MSG_ID   = 42;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nViewportIndex, SIZEOFINT);
    memcpy(&pMessage[  4], &nViewportLowerLeftX, SIZEOFINT);
    memcpy(&pMessage[  8], &nViewportLowerLeftY, SIZEOFINT);
    memcpy(&pMessage[ 12], &nViewportWidth, SIZEOFINT);
    memcpy(&pMessage[ 16], &nViewportHeight, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SensorControl
//*****************************************************************************
void FS_Comm::SendMsg_SensorControl(int    nVehicleIndex,
                                    int    nSensorIndex,
                                    double dPitch,
                                    double dBearing,
                                    double dFieldOfView,
                                    double dAspectRatio)
{
    const int MSG_SIZE = 40;
    const int MSG_ID   = 45;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nVehicleIndex, SIZEOFINT);
    memcpy(&pMessage[  4], &nSensorIndex, SIZEOFINT);
    memcpy(&pMessage[  8], &dPitch, SIZEOFDOUBLE);
    memcpy(&pMessage[ 16], &dBearing, SIZEOFDOUBLE);
    memcpy(&pMessage[ 24], &dFieldOfView, SIZEOFDOUBLE);
    memcpy(&pMessage[ 32], &dAspectRatio, SIZEOFDOUBLE);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_RasterControl
//*****************************************************************************
void FS_Comm::SendMsg_RasterControl(int    nChannel,
                                    double dOffsetX,
                                    double dOffsetY,
                                    double dZoom,
                                    int    nPageNumber)
{
    const int MSG_SIZE = 28;
    const int MSG_ID   = 46;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &dOffsetX, SIZEOFDOUBLE);
    memcpy(&pMessage[  8], &dOffsetY, SIZEOFDOUBLE);
    memcpy(&pMessage[ 16], &dZoom, SIZEOFDOUBLE);
    memcpy(&pMessage[ 24], &nPageNumber, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_UnderlayLevelProduct
//*****************************************************************************
void FS_Comm::SendMsg_UnderlayLevelProduct(int nChannel, int nLevel, const char* szCode)
{
    const int MSG_SIZE = 8;
    const int MSG_ID   = 47;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nLevel, SIZEOFINT);
    strncpy(&pMessage[4], szCode, 3);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_UnderlaySelect
//*****************************************************************************
void FS_Comm::SendMsg_UnderlaySelect(int nChannel, int nFlag, int nType, int nLevel)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 48;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nFlag, SIZEOFINT);
    memcpy(&pMessage[  4], &nType, SIZEOFINT);
    memcpy(&pMessage[  8], &nLevel, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_ThreatSelect
//*****************************************************************************
void FS_Comm::SendMsg_ThreatSelect(int nChannel, int nEnable, int nType, int nIndex)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 49;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nEnable, SIZEOFINT);
    memcpy(&pMessage[  4], &nType,   SIZEOFINT);
    memcpy(&pMessage[  8], &nIndex,  SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_GeochipSelect
//*****************************************************************************
void FS_Comm::SendMsg_GeochipSelect(int nEnable, int nType, int nIndex)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 50;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nEnable, SIZEOFINT);
    memcpy(&pMessage[  4], &nType,   SIZEOFINT);
    memcpy(&pMessage[  8], &nIndex,  SIZEOFINT);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetGeoUserGeneralSymbol
//*****************************************************************************
void FS_Comm::SendMsg_SetGeoUserGeneralSymbol(int           nSymbolIndex,
                                              int           nSymbolType,
                                              double        nLineWidth,
                                              int           nLineStyle,
                                              int           nFillPattern,
                                              int           nOutlineEnableFlag,
                                              unsigned char arColor[4],
                                              unsigned char arOutlineColor[4],
                                              unsigned char arFillColor[4],
                                              int           nArcClosedFlag,
                                              double        dArcRadiusX,
                                              double        dArcRadiusY,
                                              double        dArcStartAngle,
                                              double        dArcSweep,
                                              double        dStringOffsetX,
                                              double        dStringOffsetY,
                                              const char*   szStringText,
                                              int           nStringFontIndex,
                                              int           nRotateWithMapEnableFlag,
                                              double        dOrientation,
                                              double        dMagnification,
                                              int           nSkinIndex,
                                              int           nMetadataSize,
                                              int           nNumberOfPoints,
                                              const char*   szMetadata,
                                              const double* ppLocationArray)
{
    const int MSG_SIZE = 192 + (nMetadataSize) + (3 * 8 * nNumberOfPoints);
    const int MSG_ID   = 52;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MAX_MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nSymbolIndex, SIZEOFINT);
    memcpy(&pMessage[  4], &nSymbolType, SIZEOFINT);
    memcpy(&pMessage[  8], &nLineWidth, SIZEOFDOUBLE);
    memcpy(&pMessage[ 16], &nLineStyle, SIZEOFINT);
    memcpy(&pMessage[ 20], &nFillPattern, SIZEOFINT);
    memcpy(&pMessage[ 24], &nOutlineEnableFlag, SIZEOFINT);
    memcpy(&pMessage[ 28], &arColor[0], SIZEOFINT);
    memcpy(&pMessage[ 32], &arOutlineColor[0], SIZEOFINT);
    memcpy(&pMessage[ 36], &arFillColor[0], SIZEOFINT);
    memcpy(&pMessage[ 40], &nArcClosedFlag, SIZEOFINT);
    memcpy(&pMessage[ 44], &dArcRadiusX, SIZEOFDOUBLE);
    memcpy(&pMessage[ 52], &dArcRadiusY, SIZEOFDOUBLE);
    memcpy(&pMessage[ 60], &dArcStartAngle, SIZEOFDOUBLE);
    memcpy(&pMessage[ 68], &dArcSweep, SIZEOFDOUBLE);
    memcpy(&pMessage[ 76], &dStringOffsetX, SIZEOFDOUBLE);
    memcpy(&pMessage[ 84], &dStringOffsetY, SIZEOFDOUBLE);

    strncpy(&pMessage[ 92], szStringText, 64);
    pMessage[92 + 64 - 1] = 0; // Null-Terminated.

    memcpy(&pMessage[156], &nStringFontIndex, SIZEOFINT);
    memcpy(&pMessage[160], &nRotateWithMapEnableFlag, SIZEOFINT);
    memcpy(&pMessage[164], &dOrientation, SIZEOFDOUBLE);
    memcpy(&pMessage[172], &dMagnification, SIZEOFDOUBLE);
    memcpy(&pMessage[180], &nSkinIndex, SIZEOFINT);
    memcpy(&pMessage[184], &nMetadataSize, SIZEOFINT);
    memcpy(&pMessage[188], &nNumberOfPoints, SIZEOFINT);
    memcpy(&pMessage[192], szMetadata, nMetadataSize);
    memcpy(&pMessage[192 + nMetadataSize], ppLocationArray, 3 * static_cast<int>(SIZEOFDOUBLE) * nNumberOfPoints);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetScreenUserGeneralSymbol
//*****************************************************************************
void FS_Comm::SendMsg_SetScreenUserGeneralSymbol(int           nChannel,
                                                 int           nSymbolIndex,
                                                 int           nRenderPriority,
                                                 int           nSymbolType,
                                                 double        nLineWidth,
                                                 int           nLineStyle,
                                                 int           nFillPattern,
                                                 int           nOutlineEnableFlag,
                                                 unsigned char arColor[4],
                                                 unsigned char arOutlineColor[4],
                                                 unsigned char arFillColor[4],
                                                 int           nArcClosedFlag,
                                                 double        dArcRadiusX,
                                                 double        dArcRadiusY,
                                                 double        dArcStartAngle,
                                                 double        dArcSweep,
                                                 int           nLabelAnchor,
                                                 double        dStringOffsetX,
                                                 double        dStringOffsetY,
                                                 const char*   szStringText,
                                                 int           nStringFontIndex,
                                                 double        dOrientation,
                                                 double        dMagnification,
                                                 int           nSkinIndex,
                                                 double        dOffsetX,
                                                 double        dOffsetY,
                                                 int           nNumberOfPoints,
                                                 const double* ppLocationArray)
{
    const int MSG_SIZE = 208 + (2 * 8 * nNumberOfPoints);
    const int MSG_ID   = 53;
    const int MSG_VER  = 3;
    char pHeader[HDR_SIZE];
    char pMessage[MAX_MSG_SIZE];

    if (MSG_SIZE <= static_cast<int>(MAX_MSG_SIZE))
    {
        // Populate the message header
        PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

        // Populate the message body
        memcpy(&pMessage[  0], &nSymbolIndex, SIZEOFINT);
        memcpy(&pMessage[4], &nRenderPriority, SIZEOFINT);
        memcpy(&pMessage[  8], &nSymbolType, SIZEOFINT);
        memcpy(&pMessage[  12], &nLineWidth, SIZEOFDOUBLE);
        memcpy(&pMessage[ 20], &nLineStyle, SIZEOFINT);
        memcpy(&pMessage[ 24], &nFillPattern, SIZEOFINT);
        memcpy(&pMessage[ 28], &nOutlineEnableFlag, SIZEOFINT);
        memcpy(&pMessage[ 32], &arColor[0], SIZEOFINT);
        memcpy(&pMessage[ 36], &arOutlineColor[0], SIZEOFINT);
        memcpy(&pMessage[ 40], &arFillColor[0], SIZEOFINT);
        memcpy(&pMessage[ 44], &nArcClosedFlag, SIZEOFINT);
        memcpy(&pMessage[ 48], &dArcRadiusX, SIZEOFDOUBLE);
        memcpy(&pMessage[ 56], &dArcRadiusY, SIZEOFDOUBLE);
        memcpy(&pMessage[ 64], &dArcStartAngle, SIZEOFDOUBLE);
        memcpy(&pMessage[ 72], &dArcSweep, SIZEOFDOUBLE);
        memcpy(&pMessage[80], &nLabelAnchor, SIZEOFINT);
        memcpy(&pMessage[ 84], &dStringOffsetX, SIZEOFDOUBLE);
        memcpy(&pMessage[ 92], &dStringOffsetY, SIZEOFDOUBLE);

        strncpy(&pMessage[ 100], szStringText, 64);
        pMessage[100 + 64 - 1] = 0; // Null-Terminated.

        memcpy(&pMessage[164], &nStringFontIndex, SIZEOFINT);
        memcpy(&pMessage[168], &dOrientation, SIZEOFDOUBLE);
        memcpy(&pMessage[176], &dMagnification, SIZEOFDOUBLE);
        memcpy(&pMessage[184], &nSkinIndex, SIZEOFINT);
        memcpy(&pMessage[188], &dOffsetX, SIZEOFDOUBLE);
        memcpy(&pMessage[196], &dOffsetY, SIZEOFDOUBLE);
        memcpy(&pMessage[204], &nNumberOfPoints, SIZEOFINT);
        memcpy(&pMessage[208], ppLocationArray, 2 * static_cast<int>(SIZEOFDOUBLE) * nNumberOfPoints);

        SendMsg(nChannel, MSG_ID, pHeader, pMessage);
    }
}

//*****************************************************************************
// SendMsg_SetGeoUserSymbolSkin (static)
//*****************************************************************************
void FS_Comm::SendMsg_SetGeoUserSymbolSkin(int nIndex, int nType, const char* szFilename)
{
    const int MSG_SIZE = 264;
    const int MSG_ID   = 54;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nIndex, SIZEOFINT);
    memcpy(&pMessage[4], &nType,  SIZEOFINT);
    strncpy(&pMessage[8], szFilename, 256);
    pMessage[8 + 256 - 1] = 0; // Null-Terminated.

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetScreenUserSymbolSkin (static)
//*****************************************************************************
void FS_Comm::SendMsg_SetScreenUserSymbolSkin(int nChannel,
                                              int nIndex,
                                              int nType,
                                              const char* szFilename)
{
    const int MSG_SIZE = 264;
    const int MSG_ID   = 55;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nIndex, SIZEOFINT);
    memcpy(&pMessage[4], &nType, SIZEOFINT);
    strncpy(&pMessage[8], szFilename, 256);
    pMessage[MSG_SIZE - 1] = 0; // Null-Terminated.

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_EnableGeoSymbol
//*****************************************************************************
void FS_Comm::SendMsg_EnableGeoSymbol(int nChannel,
                                      int nEnableType,
                                      int nEnableFlag,
                                      int nSymbolType,
                                      int nSymbolIndex)
{
    const int MSG_SIZE = 16;
    const int MSG_ID   = 56;
    const int MSG_VER  = 3;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nEnableType, SIZEOFINT);
    memcpy(&pMessage[  4], &nEnableFlag, SIZEOFINT);
    memcpy(&pMessage[  8], &nSymbolType, SIZEOFINT);
    memcpy(&pMessage[ 12], &nSymbolIndex, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_EnableScreenSymbol
//*****************************************************************************
void FS_Comm::SendMsg_EnableScreenSymbol(int nChannel,
                                         int nEnableFlag,
                                         int nSymbolType,
                                         int nSymbolIndex)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 57;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nEnableFlag, SIZEOFINT);
    memcpy(&pMessage[  4], &nSymbolType, SIZEOFINT);
    memcpy(&pMessage[  8], &nSymbolIndex, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_VerticalBandsControl (static)
//*****************************************************************************
void FS_Comm::SendMsg_VerticalBandsControl(int nChannel, const void* pData)
{
    const int MSG_SIZE = 1024; // 64 bands, 2 bytes each == 128 bytes
    const int MSG_ID   = 118;
    const int MSG_VER  =  1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    memcpy(pMessage, pData, FS_Constants::NUMBER_OF_VERTICALBANDS * FS_Constants::NUMBER_BYTES_PER_BAND);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);

    // SendMsg_OverlaySelect(nChannel, FS_Constants::ENABLE, FS_Constants::VERTICAL_BANDS);
}

//*****************************************************************************
// SendMsg_ElevationControl
//*****************************************************************************
void FS_Comm::SendMsg_ElevationControl(int nChannel,
                                       int nDefinitionFlag,
                                       int nParameterCode,
                                       int nParameterValue)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 58;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nDefinitionFlag, SIZEOFINT);
    memcpy(&pMessage[  4], &nParameterCode, SIZEOFINT);
    memcpy(&pMessage[  8], &nParameterValue, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage); // technically this isn't
}

//*****************************************************************************
// SendMsg_VehicleEnables
//*****************************************************************************
void FS_Comm::SendMsg_VehicleEnables(int nChannel,
                                     int nVehicleIndex,
                                     int nSensorIndex,
                                     int nEnableFlag,
                                     int nFeatureType)
{
    const int MSG_SIZE = 16;
    const int MSG_ID   = 59;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nVehicleIndex, SIZEOFINT);
    memcpy(&pMessage[  4], &nSensorIndex, SIZEOFINT);
    memcpy(&pMessage[  8], &nEnableFlag, SIZEOFINT);
    memcpy(&pMessage[ 12], &nFeatureType, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_OwnshipControl
//*****************************************************************************
void FS_Comm::SendMsg_OwnshipControl(int nChannel, int nVehicleIndex)
{
    const int MSG_SIZE = 4;
    const int MSG_ID   = 61;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nVehicleIndex, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetRangeandBearing
//*****************************************************************************
void FS_Comm::SendMsg_SetRangeandBearing(int    nChannel,
                                         int    nSourceCoordinateType,
                                         double dSourceX,
                                         double dSourceY,
                                         int    nDestinationCoordinateType,
                                         double dDestinationX,
                                         double dDestinationY)
{
    const int MSG_SIZE = 40;
    const int MSG_ID   = 64;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nSourceCoordinateType, SIZEOFINT);
    memcpy(&pMessage[  4], &dSourceX, SIZEOFDOUBLE);
    memcpy(&pMessage[ 12], &dSourceY, SIZEOFDOUBLE);
    memcpy(&pMessage[ 20], &nDestinationCoordinateType, SIZEOFINT);
    memcpy(&pMessage[ 24], &dDestinationX, SIZEOFDOUBLE);
    memcpy(&pMessage[ 32], &dDestinationY, SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_MGRSConversion (static)
//*****************************************************************************
void FS_Comm::SendMsg_MGRSConversion(int nChannel, int nType, double dX, double dY, const char* szCode)
{
    const int MSG_SIZE = 52;
    const int MSG_ID   = 66;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nType, SIZEOFINT);
    memcpy(&pMessage[4], &dX, SIZEOFDOUBLE);
    memcpy(&pMessage[12], &dY, SIZEOFDOUBLE);
    strncpy(&pMessage[20], szCode, 31);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_RouteWaypoint
//*****************************************************************************
void FS_Comm::SendMsg_RouteWaypoint(int         nWaypointIndex,
                                    double      dLatitude,
                                    double      dLongitude,
                                    double      dElevation,
                                    double      dOrientation,
                                    int         nRotateWithMap,
                                    int         nSpriteType,
                                    int         nRenderState,
                                    const char* szLabel)
{
    const int MSG_SIZE = 112;
    const int MSG_ID   = 68;
    const int MSG_VER  = 3;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nWaypointIndex, SIZEOFINT);
    memcpy(&pMessage[4], &dLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[12], &dLongitude, SIZEOFDOUBLE);
    memcpy(&pMessage[20], &dElevation, SIZEOFDOUBLE);
    memcpy(&pMessage[28], &dOrientation, SIZEOFDOUBLE);
    memcpy(&pMessage[36], &nRotateWithMap, SIZEOFINT);
    memcpy(&pMessage[40], &nSpriteType, SIZEOFINT);
    memcpy(&pMessage[44], &nRenderState, SIZEOFINT);
    strncpy(&pMessage[48], szLabel, 64);
    pMessage[48 + 64 - 1] = 0; // Null-Terminated.

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_RouteLeg (static)
//*****************************************************************************
void FS_Comm::SendMsg_RouteLeg(int nRouteLegIndex,
                               int nStartWaypointIndex,
                               int nEndWaypointIndex,
                               int nCorridorWidth,
                               int nLegType,
                               int nLineType,
                               int nTurnDirection,
                               int nSubSegmentCount,
                               const double** ppdSubSegmentLatLongElevArray)
{
    const int MSG_SIZE = 32 + 24 * nSubSegmentCount;
    const int MSG_ID   = 69;
    const int MSG_VER  = 3;
    char pHeader[HDR_SIZE];
    unsigned char pMessage[MAX_MSG_SIZE];

    if (MSG_SIZE <= static_cast<int>(MAX_MSG_SIZE))
    {
        // Populate the message header
        PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

        // Populate the message body
        memcpy(&pMessage[ 0], &nRouteLegIndex, SIZEOFINT);
        memcpy(&pMessage[ 4], &nStartWaypointIndex, SIZEOFINT);
        memcpy(&pMessage[ 8], &nEndWaypointIndex, SIZEOFINT);
        memcpy(&pMessage[12], &nCorridorWidth, SIZEOFINT);
        memcpy(&pMessage[16], &nLegType, SIZEOFINT);
        memcpy(&pMessage[20], &nLineType, SIZEOFINT);
        memcpy(&pMessage[24], &nTurnDirection, SIZEOFINT);
        memcpy(&pMessage[28], &nSubSegmentCount, SIZEOFINT);
        memcpy(
            &pMessage[32],
            ppdSubSegmentLatLongElevArray,
            24 * nSubSegmentCount);

        SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
    }
}

//*****************************************************************************
// SendMsg_RouteLegParameters
//*****************************************************************************
void FS_Comm::SendMsg_RouteLegParameters(int nLeg, int nColor, int nStyle)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 70;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nLeg, SIZEOFINT);
    memcpy(&pMessage[4], &nColor, SIZEOFINT);
    memcpy(&pMessage[8], &nStyle, SIZEOFINT);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_RouteLegPercentComplete
//*****************************************************************************
void FS_Comm::SendMsg_RouteLegPercentComplete(int nIndex, double dPercent)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 71;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nIndex,   SIZEOFINT);
    memcpy(&pMessage[4], &dPercent, SIZEOFDOUBLE);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_RouteGroup
//*****************************************************************************
void FS_Comm::SendMsg_RouteGroup(int nGroup, int nType, int nIndex, int nFlag)
{
    const int MSG_SIZE = 16;
    const int MSG_ID   = 72;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nGroup, SIZEOFINT);
    memcpy(&pMessage[  4], &nType, SIZEOFINT);
    memcpy(&pMessage[  8], &nIndex, SIZEOFINT);
    memcpy(&pMessage[ 12], &nFlag, SIZEOFINT);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_RouteGroupEnable
//*****************************************************************************
void FS_Comm::SendMsg_RouteGroupEnable(int nChannel, int nGroup, int nIndex, int nFlag)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 73;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nGroup, SIZEOFINT);
    memcpy(&pMessage[  4], &nIndex, SIZEOFINT);
    memcpy(&pMessage[  8], &nFlag, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetFlightPlan
//*****************************************************************************
void FS_Comm::SendMsg_SetFlightPlan(int nIndex, int nLegs, const int* pLegs)
{
    const int MSG_SIZE = 8 + (4 * nLegs);
    const int MSG_ID   = 75;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    unsigned char pMessage[MAX_MSG_SIZE];

    if (MSG_SIZE <= static_cast<int>(MAX_MSG_SIZE))
    {
        // Populate the message header
        PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

        // Populate the message body
        memcpy(&pMessage[  0], &nIndex, SIZEOFINT);
        memcpy(&pMessage[  4], &nLegs,  SIZEOFINT);
        memcpy(&pMessage[  8], pLegs,   (4 * nLegs));

        SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
    }
}
//*****************************************************************************
// SendMsg_RouteFlightPlanEnable
//*****************************************************************************
void FS_Comm::SendMsg_RouteFlightPlanEnable(const int nChannel, const int nFlightPlanIndex, const int nOverlayCode,const int nEnableFlag)
{
    const int MSG_SIZE = 12;
    const int MSG_ID = 101;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    unsigned char pMessage[MAX_MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    memcpy(&pMessage[0], &nFlightPlanIndex, SIZEOFINT);
    memcpy(&pMessage[4], &nOverlayCode, SIZEOFINT);
    memcpy(&pMessage[8], &nEnableFlag, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_ElevationProfileControl
//*****************************************************************************
void FS_Comm::SendMsg_ElevationProfileControl(int nChannel, double dScale, double dStart)
{
    const int MSG_SIZE = 16;
    const int MSG_ID   = 82;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &dScale, SIZEOFDOUBLE);
    memcpy(&pMessage[8], &dStart, SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_VehicleIcon
//*****************************************************************************
void FS_Comm::SendMsg_VehicleIcon(int nChannel, int nVehicle, int nFlag, const char* szPath)
{
    const int MSG_SIZE = 264;
    const int MSG_ID   = 83;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nVehicle, SIZEOFINT);
    memcpy(&pMessage[4], &nFlag, SIZEOFINT);
    strncpy(&pMessage[8], szPath, 256);
    pMessage[8 + 256 - 1] = 0; // Null-Terminated.

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

void FS_Comm::SendMsg_VehicleHistoryProperties(const int nVehicle,
                                               const int nRedValue,
                                               const int nGreenValue,
                                               const int nBlueValue,
                                               const int nAlphaValue)
{
    const int MSG_SIZE = 20;
    const int MSG_ID = 138;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nVehicle, SIZEOFINT);
    memcpy(&pMessage[4], &nRedValue, SIZEOFINT);
    memcpy(&pMessage[8], &nGreenValue, SIZEOFINT);
    memcpy(&pMessage[12], &nBlueValue, SIZEOFINT);
    memcpy(&pMessage[16], &nAlphaValue, SIZEOFINT);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_RouteLegGate
//*****************************************************************************
void FS_Comm::SendMsg_RouteLegGate(int nLeg,
                                   int nGate,
                                   int nFlag,
                                   int nDistance,
                                   const char* szLabel)
{
    const int MSG_SIZE = 48;
    const int MSG_ID   = 84;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nLeg, SIZEOFINT);
    memcpy(&pMessage[4], &nGate, SIZEOFINT);
    memcpy(&pMessage[8], &nFlag, SIZEOFINT);
    memcpy(&pMessage[12], &nDistance, SIZEOFINT);
    strncpy(&pMessage[16], szLabel, 31);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_Racetrack
//*****************************************************************************
void FS_Comm::SendMsg_Racetrack(int    nRouteLegIndex,
                                int    nWidthMeters,
                                int    nLengthMeters,
                                double dBearingDegrees,
                                int    nLineType,
                                double dAltitude,
                                int    nRacetrackDefinition,
                                double dCenterLatitude,
                                double dCenterLongitude,
                                double dLatitude1,
                                double dLongitude1,
                                double dLatitude2,
                                double dLongitude2,
                                double dLatitude3,
                                double dLongitude3,
                                double dLatitude4,
                                double dLongitude4)
{
    const int MSG_SIZE = 116;
    const int MSG_ID   = 85;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nRouteLegIndex, SIZEOFINT);
    memcpy(&pMessage[  4], &nWidthMeters, SIZEOFINT);
    memcpy(&pMessage[  8], &nLengthMeters, SIZEOFINT);
    memcpy(&pMessage[ 12], &dBearingDegrees, SIZEOFDOUBLE);
    memcpy(&pMessage[ 20], &nLineType, SIZEOFINT);
    memcpy(&pMessage[ 24], &dAltitude, SIZEOFDOUBLE);
    memcpy(&pMessage[ 32], &nRacetrackDefinition, SIZEOFINT);
    memcpy(&pMessage[ 36], &dCenterLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[ 44], &dCenterLongitude, SIZEOFDOUBLE);
    memcpy(&pMessage[ 52], &dLatitude1, SIZEOFDOUBLE);
    memcpy(&pMessage[ 60], &dLongitude1, SIZEOFDOUBLE);
    memcpy(&pMessage[ 68], &dLatitude2, SIZEOFDOUBLE);
    memcpy(&pMessage[ 76], &dLongitude2, SIZEOFDOUBLE);
    memcpy(&pMessage[ 84], &dLatitude3, SIZEOFDOUBLE);
    memcpy(&pMessage[ 92], &dLongitude3, SIZEOFDOUBLE);
    memcpy(&pMessage[100], &dLatitude4, SIZEOFDOUBLE);
    memcpy(&pMessage[108], &dLongitude4, SIZEOFDOUBLE);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TextBoxEnable
//*****************************************************************************
void FS_Comm::SendMsg_TextBoxEnable(int nChannel, int nIndex, int nFlag)
{
    const int MSG_SIZE = 12;
    const int MSG_ID   = 88;
    const int MSG_VER  = 1;
    const int nUnused  = 0;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nIndex, SIZEOFINT);
    memcpy(&pMessage[4], &nFlag, SIZEOFINT);
    memcpy(&pMessage[8], &nUnused, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TextBoxSetText
//*****************************************************************************
void FS_Comm::SendMsg_TextBoxSetText(int         nChannel,
                                     int         nTextBoxIndex,
                                     int         nClearFirstFlag,
                                     int         nCharacterStartIndex,
                                     const char* szText,
                                     int         nLength)
{
    const int MSG_SIZE = 12 + nLength;
    const int MSG_ID   = 89;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    unsigned char pMessage[MAX_MSG_SIZE];

    if (MSG_SIZE <= static_cast<int>(MAX_MSG_SIZE))
    {
        // Populate the message header
        PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

        // Populate the message body
        memcpy(&pMessage[0], &nTextBoxIndex, SIZEOFINT);
        memcpy(&pMessage[4], &nClearFirstFlag, SIZEOFINT);
        memcpy(&pMessage[8], &nCharacterStartIndex, SIZEOFINT);
        memcpy(&pMessage[ 12], szText, nLength);

        SendMsg(nChannel, MSG_ID, pHeader, pMessage);
    }
}

//*****************************************************************************
// SendMsg_TextBoxInsertText
//*****************************************************************************
void FS_Comm::SendMsg_TextBoxInsertText(int         nChannel,
                                        int         nTextBoxIndex,
                                        int         nClearFirstFlag,
                                        const char* szText,
                                        int         nLength)
{
    const int MSG_SIZE = 8 + nLength;
    const int MSG_ID   = 90;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    unsigned char pMessage[MAX_MSG_SIZE];

    if (MSG_SIZE <= static_cast<int>(MAX_MSG_SIZE))
    {
        // Populate the message header
        PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

        // Populate the message body
        memcpy(&pMessage[0], &nTextBoxIndex, SIZEOFINT);
        memcpy(&pMessage[4], &nClearFirstFlag, SIZEOFINT);
        memcpy(&pMessage[ 8], szText, nLength);

        SendMsg(nChannel, MSG_ID, pHeader, pMessage);
    }
}

//*****************************************************************************
// SendMsg_TextBoxSetGeometry
//*****************************************************************************
void FS_Comm::SendMsg_TextBoxSetGeometry(int nChannel,
                                         int nTextBoxIndex,
                                         int nUsableBufferSize,
                                         int nTextBoxLowerLeftX,
                                         int nTextBoxLowerLeftY,
                                         int nTextBoxWidth,
                                         int nTextBoxHeight,
                                         int nTextBoxFont)
{
    const int MSG_SIZE = 28;
    const int MSG_ID   = 91;
    const int MSG_VER  = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nTextBoxIndex, SIZEOFINT);
    memcpy(&pMessage[ 4], &nUsableBufferSize, SIZEOFINT);
    memcpy(&pMessage[ 8], &nTextBoxLowerLeftX, SIZEOFINT);
    memcpy(&pMessage[12], &nTextBoxLowerLeftY, SIZEOFINT);
    memcpy(&pMessage[16], &nTextBoxWidth, SIZEOFINT);
    memcpy(&pMessage[20], &nTextBoxHeight, SIZEOFINT);
    memcpy(&pMessage[24], &nTextBoxFont, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TextBoxSetActive
//*****************************************************************************
void FS_Comm::SendMsg_TextBoxSetActive(int nChannel, int nTextBoxIndex)
{
    const int MSG_SIZE = 4;
    const int MSG_ID   = 92;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nTextBoxIndex, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TextBoxSetRegion
//*****************************************************************************
void FS_Comm::SendMsg_TextBoxSetRegion(int nChannel,
                                       int nTextBoxIndex,
                                       int nAbsoluteRelativeFlag,
                                       int nLinePageMode,
                                       int nLinePageIndex)
{
    const int MSG_SIZE = 16;
    const int MSG_ID   = 93;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[ 0], &nTextBoxIndex, SIZEOFINT);
    memcpy(&pMessage[ 4], &nAbsoluteRelativeFlag, SIZEOFINT);
    memcpy(&pMessage[ 8], &nLinePageMode, SIZEOFINT);
    memcpy(&pMessage[12], &nLinePageIndex, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TextBoxGetContents
//*****************************************************************************
void FS_Comm::SendMsg_TextBoxGetContents(int nChannel, int nTextBoxIndex)
{
    const int MSG_SIZE = 4;
    const int MSG_ID   = 94;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nTextBoxIndex, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_TextBoxSetColors
//*****************************************************************************
void FS_Comm::SendMsg_TextBoxSetColors(
    const int nChannel,
    const int nTextBoxIndex,
    const int nType,
    const int nRedValue,
    const int nGreenValue,
    const int nBlueValue,
    const int nAlphaValue)
{
    const int MSG_SIZE = 24;
    const int MSG_ID = 114;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    memcpy(&pMessage[0],  &nTextBoxIndex, SIZEOFINT);
    memcpy(&pMessage[4],  &nType,         SIZEOFINT);
    memcpy(&pMessage[8],  &nRedValue,     SIZEOFINT);
    memcpy(&pMessage[12], &nGreenValue,   SIZEOFINT);
    memcpy(&pMessage[16], &nBlueValue,    SIZEOFINT);
    memcpy(&pMessage[20], &nAlphaValue,   SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_CompassRoseControl
//*****************************************************************************
void FS_Comm::SendMsg_CompassRoseControl(int nChannel, int nConfiguration)
{
    const int MSG_SIZE = 4;
    const int MSG_ID   = 97;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nConfiguration, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_CompassPointerControl
//*****************************************************************************
void FS_Comm::SendMsg_CompassPointerControl(int    nChannel,
                                            int    nEnableFlag,
                                            int    nPointerSelection,
                                            double dPointerAngle)
{
    const int MSG_SIZE = 16;
    const int MSG_ID   = 98;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[  0], &nEnableFlag, SIZEOFINT);
    memcpy(&pMessage[  4], &nPointerSelection, SIZEOFINT);
    memcpy(&pMessage[  8], &dPointerAngle, SIZEOFDOUBLE);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SearchArea
//*****************************************************************************
void FS_Comm::SendMsg_SearchArea(int    nIndex,
                                 int    nInitialRadius,
                                 double dGrowthRate,
                                 double dLatitude,
                                 double dLongitude)
{
    const int MSG_SIZE = 32;
    const int MSG_ID   = 103;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    memcpy(&pMessage[ 0], &nIndex, SIZEOFINT);
    memcpy(&pMessage[ 4], &nInitialRadius, SIZEOFINT);
    memcpy(&pMessage[ 8], &dGrowthRate, SIZEOFDOUBLE);
    memcpy(&pMessage[16], &dLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[24], &dLongitude, SIZEOFDOUBLE);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SearchPattern
//*****************************************************************************
void FS_Comm::SendMsg_SearchPattern(int    nIndex,
                                    int    nType,
                                    int    nNumberOfTracks,
                                    int    nTrackLength,
                                    int    nTrackSpacing,
                                    int    nFirstTurnDirection,
                                    double dLatitude,
                                    double dLongitude,
                                    double dInitialHeading)
{
    const int MSG_SIZE = 48;
    const int MSG_ID   = 102;
    const int MSG_VER  = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    memcpy(&pMessage[ 0], &nIndex, SIZEOFINT);
    memcpy(&pMessage[ 4], &nType, SIZEOFINT);
    memcpy(&pMessage[ 8], &nNumberOfTracks, SIZEOFINT);
    memcpy(&pMessage[ 12], &nTrackLength, SIZEOFINT);
    memcpy(&pMessage[ 16], &nTrackSpacing, SIZEOFINT);
    memcpy(&pMessage[ 20], &nFirstTurnDirection, SIZEOFINT);
    memcpy(&pMessage[ 24], &dLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[ 32], &dLongitude, SIZEOFDOUBLE);
    memcpy(&pMessage[ 40], &dInitialHeading, SIZEOFDOUBLE);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// FS_Comm::SendMsg_SetMetaData
//*****************************************************************************
void FS_Comm::SendMsg_SetMetaData(const int nObjectID, const char * szObjectMetadata)
{
    const int nMetaDataLength = strlen(szObjectMetadata);
    const int MSG_SIZE = 4 + nMetaDataLength;
    const int MSG_ID = 112;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MAX_MSG_SIZE];

    // Clear Message
    memset(pMessage, 0, MAX_MSG_SIZE);

    // Pack Header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Pack Message
    memcpy(&pMessage[0], &nObjectID, SIZEOFINT);
    memcpy(&pMessage[4], szObjectMetadata, nMetaDataLength);
    pMessage[4 + nMetaDataLength] = 0; // NULL TERMINATE

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// FS_Comm::SendMsg_DynamicGeoTiff
//*****************************************************************************
void FS_Comm::SendMsg_DynamicGeoTiff(int nAction, const char* szProduct, const char* szFileName)
{
    const int MSG_SIZE   = 264;
    const int MSG_ID     = 116;
    const int MSG_VER    = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Pack Message Body
    memcpy(&pMessage[0],  &nAction,   SIZEOFINT);
    strncpy(&pMessage[4], szProduct,  static_cast<int>(FS_Constants::MAX_PRODUCT_CODE_LENGTH) - 1);
    strncpy(&pMessage[8], szFileName, static_cast<int>(FS_Constants::MAX_FILENAME_LENGTH) - 1);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// FS_Comm::SendMsg_VerticalDataProcessing
//*****************************************************************************
void FS_Comm::SendMsg_VerticalDataProcessing(const int nElevationDataProcessing, const int nDepthDataProcessing)
{
    const int MSG_SIZE = 8;
    const int MSG_ID = 117;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Fill Header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Pack Message Body
    memcpy(&pMessage[0], &nElevationDataProcessing, SIZEOFINT);
    memcpy(&pMessage[4], &nDepthDataProcessing,     SIZEOFINT);

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// FS_Comm::SendMsg_MagNorth
//*****************************************************************************
void FS_Comm::SendMsg_MagNorth(double dAngle)
{
    const int MSG_SIZE   = 8;
    const int MSG_ID     = 121;
    const int MSG_VER    = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    memcpy(&pMessage[0], &dAngle, SIZEOFDOUBLE);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// FS_Comm::SendMsg_ObjectGroupDeclutter
//*****************************************************************************
void FS_Comm::SendMsg_ObjectGroupDeclutter(int*  arParameterCode,
                                           void* arParameterValue1,
                                           int*  arParameterValue2,
                                           int   nNumParameters)
{
    int i          = 0;
    int nOffset    = 0;
    int nMsgSize   = 0;
    const int MSG_ID  = 115;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MAX_MSG_SIZE];

    // Each parameter has 2 integer values, code and enable/disable
    nMsgSize = nNumParameters * static_cast<int>(SIZEOFINT) * 2;

    for (i = 0; i < nNumParameters; ++i)
    {
        nMsgSize += arParameterCode[i] == 0 ? 4 : 256;
    }

    if (nMsgSize <= static_cast<int>(MAX_MSG_SIZE))
    {
        // Populate the message header
        PackHeader(pHeader, nMsgSize, RESERVED, MSG_ID, MSG_VER);

        for (i = 0; i < nNumParameters; ++i)
        {
            memcpy(&pMessage[nOffset],   arParameterCode,   SIZEOFINT);
            nOffset += static_cast<int>(SIZEOFINT);

            if (arParameterCode[i] == 0)
            {
                memcpy(&pMessage[nOffset],   arParameterValue1, SIZEOFINT);
                nOffset += static_cast<int>(SIZEOFINT);
            }
            else
            {
                memcpy(&pMessage[nOffset],   arParameterValue1, FS_Constants::MAX_FILENAME_LENGTH);
                nOffset += static_cast<int>(FS_Constants::MAX_FILENAME_LENGTH);
            }

            memcpy(&pMessage[nOffset], arParameterValue2,  SIZEOFINT);
            nOffset += static_cast<int>(SIZEOFINT);
        }

        SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
    }
}

//*****************************************************************************
// SendMsg_SetTime
//*****************************************************************************
void FS_Comm::SendMsg_SetTime(
    int          nChannel,
    unsigned int nYear,
    unsigned int nMonth,
    unsigned int nDay,
    unsigned int nHour,
    unsigned int nMin,
    unsigned int nSec)
{
    const int MSG_SIZE = 24;
    const int MSG_ID = 122;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nYear, SIZEOFINT);
    memcpy(&pMessage[4], &nMonth, SIZEOFINT);
    memcpy(&pMessage[8], &nDay, SIZEOFINT);
    memcpy(&pMessage[12], &nHour, SIZEOFINT);
    memcpy(&pMessage[16], &nMin, SIZEOFINT);
    memcpy(&pMessage[20], &nSec, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

void FS_Comm::SendMsg_SetGeoMultiPointSymbol(
    const int       nFSUID,
    const int       nRenderPriority,
    const int       nType,
    const int       nSubType,
    const int       nKey,
    const double    dLineWidth,
    const int       nLineType,
    const int       nLineTextureIndex,
    const int       nFillTextureIndex,
    const int       nLineModulationColor,
    const int       nFillModulationColor,
    const int       nVerticalHeight,
    const double    dOffsetX,
    const double    dOffsetY,
    const int       nNumberOfPoints,
    const double    arLocations[][3])
{
    const int MSG_SIZE = 72 + (nNumberOfPoints * 24);
    const int MSG_ID = 123;
    const int MSG_VER = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MAX_MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0],  &nFSUID,               SIZEOFINT);
    memcpy(&pMessage[4],  &nRenderPriority,      SIZEOFINT);
    memcpy(&pMessage[8],  &nType,                SIZEOFINT);
    memcpy(&pMessage[12], &nSubType,             SIZEOFINT);
    memcpy(&pMessage[16], &nKey,                 SIZEOFINT);
    memcpy(&pMessage[20], &dLineWidth,           SIZEOFDOUBLE);
    memcpy(&pMessage[28], &nLineType,            SIZEOFINT);
    memcpy(&pMessage[32], &nLineTextureIndex,    SIZEOFINT);
    memcpy(&pMessage[36], &nFillTextureIndex,    SIZEOFINT);
    memcpy(&pMessage[40], &nLineModulationColor, SIZEOFINT);
    memcpy(&pMessage[44], &nFillModulationColor, SIZEOFINT);
    memcpy(&pMessage[48], &nVerticalHeight,      SIZEOFINT);
    memcpy(&pMessage[52], &dOffsetX,             SIZEOFDOUBLE);
    memcpy(&pMessage[60], &dOffsetY,             SIZEOFDOUBLE);
    memcpy(&pMessage[68], &nNumberOfPoints,      SIZEOFINT);

    // loop variables
    int nPointIndex = 0;
    int nLocation = 0;
    for (; nPointIndex < nNumberOfPoints; nPointIndex++)
    {
        // Copy at n % 3 == 0
        memcpy(&pMessage[72 + nLocation], &arLocations[nPointIndex][0], SIZEOFDOUBLE);

        // Copy at n % 3 == 1
        memcpy(&pMessage[72 + (nLocation + SIZEOFDOUBLE)], &arLocations[nPointIndex][1], SIZEOFDOUBLE);

        // Copy at n % 3 == 2
        memcpy(&pMessage[72 + (nLocation + (2 * SIZEOFDOUBLE))], &arLocations[nPointIndex][2], SIZEOFDOUBLE);

        // Increment 3 slots equal to the size of a double.
        nLocation += 3*SIZEOFDOUBLE;
    }

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

void FS_Comm::SendMsg_SetGeoPointSymbol(
    const int      nFSUID,
    const int      nRenderPriority,
    const int      nType,
    const int      nSubType,
    const int      nKey,
    const int      nSkinIndex,
    const double   dOrientation,
    const int      nRotateWithMap,
    const double   dMagnification,
    const int      nTextureModulationColor,
    const int      nBackgroundColor,
    const double   dLatitude,
    const double   dLongitude,
    const double   dElevationMSL,
    const double   dOffsetX,
    const double   dOffsetY,
    const int      nLabelAnchorPosition,
    const double   dLabelOffsetX,
    const double   dLabelOffsetY,
    const char *   szLabelText,
    const int      nLabelFontIndex)
{
    const int MSG_SIZE = 148;
    const int MSG_ID = 124;
    const int MSG_VER = 3;
    char pHeader[HDR_SIZE];
    char pMessage[MAX_MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Copy over message
    memcpy(&pMessage[0],  &nFSUID,                  SIZEOFINT);
    memcpy(&pMessage[4],  &nRenderPriority,         SIZEOFINT);
    memcpy(&pMessage[8],  &nType,                   SIZEOFINT);
    memcpy(&pMessage[12], &nSubType,                SIZEOFINT);
    memcpy(&pMessage[16], &nKey,                    SIZEOFINT);
    memcpy(&pMessage[20], &nSkinIndex,              SIZEOFINT);
    memcpy(&pMessage[24], &dOrientation,            SIZEOFDOUBLE);
    memcpy(&pMessage[32], &nRotateWithMap,          SIZEOFINT);
    memcpy(&pMessage[36], &dMagnification,          SIZEOFDOUBLE);
    memcpy(&pMessage[44], &nTextureModulationColor, SIZEOFINT);
    memcpy(&pMessage[48], &nBackgroundColor,        SIZEOFINT);
    memcpy(&pMessage[52], &dLatitude,               SIZEOFDOUBLE);
    memcpy(&pMessage[60], &dLongitude,              SIZEOFDOUBLE);
    memcpy(&pMessage[68], &dElevationMSL,           SIZEOFDOUBLE);
    memcpy(&pMessage[76], &dOffsetX,                SIZEOFDOUBLE);
    memcpy(&pMessage[84], &dOffsetY,                SIZEOFDOUBLE);
    memcpy(&pMessage[92], &nLabelAnchorPosition,    SIZEOFINT);
    memcpy(&pMessage[96], &dLabelOffsetX,           SIZEOFDOUBLE);
    memcpy(&pMessage[104], &dLabelOffsetY,          SIZEOFDOUBLE);
    memcpy(&pMessage[112], szLabelText,             32);
    memcpy(&pMessage[144], &nLabelFontIndex,        SIZEOFINT);

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

void FS_Comm::SendMsg_SetGeoSymbolOffscreenIdicator(
    const int nFSUID,
    const int nAction,
    const int nSpriteIndex)
{
    const int MSG_SIZE = 12;
    const int MSG_ID = 151;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MAX_MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Copy over message
    memcpy(&pMessage[0], &nFSUID, SIZEOFINT);
    memcpy(&pMessage[4], &nAction, SIZEOFINT);
    memcpy(&pMessage[8], &nSpriteIndex, SIZEOFINT);

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}
//*****************************************************************************
// SendMsg_SymbolFileAction
//*****************************************************************************
void FS_Comm::SendMsg_SymbolFileAction(
    const int nAction,
    const int nType,
    const int nEnableFlag,
    const char * szFileName,
    int nCount,
    ...)
{
    int nMsgSize = 268;
    const int MSG_SIZE = 1024;
    const int MSG_ID = 130;
    const int MSG_VER = 3;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    

    memcpy(&pMessage[0], &nAction,     SIZEOFINT);
    memcpy(&pMessage[4], &nType,       SIZEOFINT);
    memcpy(&pMessage[8], &nEnableFlag, SIZEOFINT);
    memcpy(&pMessage[12], szFileName,  FS_Constants::MAX_FILENAME_LENGTH);

    int    nIndex = 0;
    int    nParameterCode = 0;
    double dParameterValue = 0;
    const char * szParameterValue = "";

    // Prime the Variable Argument List
    va_list hParamList;
    va_start(hParamList, nCount);

    for (nIndex = 0; nIndex < nCount; ++nIndex)
    {
        nParameterCode = va_arg(hParamList, int);
        memcpy(&pMessage[nMsgSize], &nParameterCode, SIZEOFINT);
        nMsgSize += 4;

        switch (nParameterCode)
        {
        case 0:  // AOI North (Intentional Fall)
        case 1: // AOI South (Intentional Fall)
        case 2:   // AOI East (Intentional Fall)
        case 3:     // AOI West (Intentional Fall)
        case 5:  // Hide above range (Intentional Fall)
            dParameterValue = va_arg(hParamList, double);
            memcpy(&pMessage[nMsgSize], &dParameterValue, SIZEOFDOUBLE);
            nMsgSize += 8;
            break;
        case 4:      // Display at product
            szParameterValue = va_arg(hParamList, char *);
            memcpy(&pMessage[nMsgSize], &szParameterValue, 4);
            nMsgSize += 8;
            break;

        default:
            // No appropriate action to take!
            break;
        }
    }
    va_end(hParamList);
    pMessage[MSG_SIZE - 1] = 0; // Null-Terminated.
    
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_MonochromeSelect
//*****************************************************************************
void FS_Comm::SendMsg_MonochromeSelect(
    const int nChannel,
    const int nEnableState,
    const int nMonochromeMode)
{
    const int MSG_SIZE = 8;
    const int MSG_ID = 131;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    memcpy(&pMessage[0], &nEnableState, SIZEOFINT);
    memcpy(&pMessage[4], &nMonochromeMode, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_LandingZone
//*****************************************************************************
void FS_Comm::SendMsg_LandingZone(
    const int    nChannel,
    const double dLatitude,
    const double dLongitude,
    const double dApproachBearing,
    const int    nResolutionMode)
{
    const int MSG_SIZE = 28;
    const int MSG_ID = 135;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    memcpy(&pMessage[0], &dLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[8], &dLongitude, SIZEOFDOUBLE);
    memcpy(&pMessage[16], &dApproachBearing, SIZEOFDOUBLE);
    memcpy(&pMessage[24], &nResolutionMode, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_PerspectiveCameraFull
//*****************************************************************************
void FS_Comm::SendMsg_PerspectiveCameraFull(
    const int nChannel,
    const int nCameraMode,
    const int nSrcObjectID,
    const double dSrcLat,
    const double dSrcLon,
    const double dSrcAlt,
    const int nTargetObjectID,
    const double dTargetLat,
    const double dTargetLon,
    const double dTargetAlt,
    const double dVectorAzi,
    const double dVectorTilt,
    const double dVectorDepth,
    const int nAttitude)
{
    const int MSG_SIZE = 88;
    const int MSG_ID = 137;
    const int MSG_VER = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Populate the message body
    memcpy(&pMessage[0], &nCameraMode, SIZEOFINT);
    memcpy(&pMessage[4], &nSrcObjectID, SIZEOFINT);
    memcpy(&pMessage[8], &dSrcLat, SIZEOFDOUBLE);
    memcpy(&pMessage[16], &dSrcLon, SIZEOFDOUBLE);
    memcpy(&pMessage[24], &dSrcAlt, SIZEOFDOUBLE);
    memcpy(&pMessage[32], &nTargetObjectID, SIZEOFINT);
    memcpy(&pMessage[36], &dTargetLat, SIZEOFDOUBLE);
    memcpy(&pMessage[44], &dTargetLon, SIZEOFDOUBLE);
    memcpy(&pMessage[52], &dTargetAlt, SIZEOFDOUBLE);
    memcpy(&pMessage[60], &dVectorAzi, SIZEOFDOUBLE);
    memcpy(&pMessage[68], &dVectorTilt, SIZEOFDOUBLE);
    memcpy(&pMessage[76], &dVectorDepth, SIZEOFDOUBLE);
    memcpy(&pMessage[84], &nAttitude, SIZEOFINT);

    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_CursorConfiguration
//*****************************************************************************
void FS_Comm::SendMsg_CursorConfiguration(
    const int    nChannel,
    const int    nCursorSkinIndex,
    const double dHighlightWidth,
    const double dHighlightHeight,
    const int    nOutlineRed,
    const int    nOutlineGreen,
    const int    nOutlineBlue,
    const int    nOutlineAlpha,
    const int    nFillRed,
    const int    nFillGreen,
    const int    nFillBlue,
    const int    nFillAlpha)
{
    const int MSG_SIZE = 52;
    const int MSG_ID = 142;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // pack Header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Pack Message
    memcpy(&pMessage[0], &nCursorSkinIndex, SIZEOFINT);
    memcpy(&pMessage[4], &dHighlightWidth, SIZEOFDOUBLE);
    memcpy(&pMessage[12], &dHighlightHeight, SIZEOFDOUBLE);
    memcpy(&pMessage[20], &nOutlineRed, SIZEOFINT);
    memcpy(&pMessage[24], &nOutlineGreen, SIZEOFINT);
    memcpy(&pMessage[28], &nOutlineBlue, SIZEOFINT);
    memcpy(&pMessage[32], &nOutlineAlpha, SIZEOFINT);
    memcpy(&pMessage[36], &nFillRed, SIZEOFINT);
    memcpy(&pMessage[40], &nFillGreen, SIZEOFINT);
    memcpy(&pMessage[44], &nFillBlue, SIZEOFINT);
    memcpy(&pMessage[48], &nFillAlpha, SIZEOFINT);

    // send message
    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SensorConfiguration
//*****************************************************************************
void FS_Comm::SendMsg_SensorConfiguration(
    const int nVehicleIndex,
    const int nSensorIndex,
    const int nTextureID)
{
    const int MSG_SIZE = 12;
    const int MSG_ID = 143;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    memcpy(&pMessage[0], &nVehicleIndex, SIZEOFINT);
    memcpy(&pMessage[4], &nSensorIndex,  SIZEOFINT);
    memcpy(&pMessage[0], &nTextureID,    SIZEOFINT);

    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_EnableByUID
//*****************************************************************************
void FS_Comm::SendMsg_EnableByUID(const int nChannel, const int nEnableFlag, const int nFSUID)
{
    const int MSG_SIZE = 8;
    const int MSG_ID = 146;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Pack the header
    PackHeader(pHeader, MSG_SIZE, nChannel, MSG_ID, MSG_VER);

    // Pack the payload
    memcpy(&pMessage[0], &nEnableFlag, SIZEOFINT);
    memcpy(&pMessage[4], &nFSUID, SIZEOFINT);

    // Send the message
    SendMsg(nChannel, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetRangeRingSymbol
//*****************************************************************************
void FS_Comm::SendMsg_SetRangeRingSymbol(
    const int      nFSUID,
    const int      nKey,
    const int      nRRDef,
    const int      nRRCenterPoint,
    const double   dLat,
    const double   dLon,
    const int      nCPUID,
    const double   dScreenX,
    const double   dScreenY)
{
    const int MSG_SIZE = 52;
    const int MSG_ID = 148;
    const int MSG_VER = 2;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Copy over message
    memcpy(&pMessage[0], &nFSUID, SIZEOFINT);
    memcpy(&pMessage[4], &nKey, SIZEOFINT);
    memcpy(&pMessage[8], &nRRDef, SIZEOFINT);
    memcpy(&pMessage[12], &nRRCenterPoint, SIZEOFINT);
    memcpy(&pMessage[16], &dLat, SIZEOFDOUBLE);
    memcpy(&pMessage[24], &dLon, SIZEOFDOUBLE);
    memcpy(&pMessage[32], &nCPUID, SIZEOFINT);
    memcpy(&pMessage[36], &dScreenX, SIZEOFDOUBLE);
    memcpy(&pMessage[44], &dScreenY, SIZEOFDOUBLE);

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetDynamicInstrument
//*****************************************************************************
void FS_Comm::SendMsg_SetDynamicInstrument(
    const int      nIndex,
    const double   dScreenX,
    const double   dScreenY)
{
    const int MSG_SIZE = 20;
    const int MSG_ID = 41;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Copy over message
    memcpy(&pMessage[0], &nIndex, SIZEOFINT);
    memcpy(&pMessage[4], &dScreenX, SIZEOFDOUBLE);
    memcpy(&pMessage[12], &dScreenY, SIZEOFDOUBLE);

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_DMS_Conversion
//*****************************************************************************
void FS_Comm::SendMsg_DMS_Conversion(
    const int      nConversionCode,
    const double   dLatitude,
    const double   dLongitude,
    const int      nDegreesLatitude,
    const int      nMinutesLatitude,
    const double   dSecondsLatitude,
    const int      nDegreesLongitude,
    const int      nMinutesLongitude,
    const double   dSecondsLongitude,
    const int      nOutputFormat,
    const char *   szOutputString)
{
    const int MSG_SIZE = 88;
    const int MSG_ID = 150;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Copy over message
    memcpy(&pMessage[0], &nConversionCode, SIZEOFINT);
    memcpy(&pMessage[4], &dLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[12], &dLongitude, SIZEOFDOUBLE);
    memcpy(&pMessage[20], &nDegreesLatitude, SIZEOFINT);
    memcpy(&pMessage[24], &nMinutesLatitude, SIZEOFINT);
    memcpy(&pMessage[28], &dSecondsLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[36], &nDegreesLongitude, SIZEOFINT);
    memcpy(&pMessage[40], &nMinutesLongitude, SIZEOFINT);
    memcpy(&pMessage[44], &dSecondsLongitude, SIZEOFDOUBLE);
    memcpy(&pMessage[52], &nOutputFormat, SIZEOFINT);
    strncpy(&pMessage[56], szOutputString, 31);
    //pMessage[56 + 32 - 1] = '\0'; // Null-Terminated.

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}

//*****************************************************************************
// SendMsg_SetStormscopeSymbol
//*****************************************************************************
void FS_Comm::SendMsg_SetStormscopeSymbol(
    const int      nFSUID,
    const int      nKey,
    const int      nSkinIndex,
    const double   dOrientation,
    const int      nRotateFlag,
    const double   dMagnification,
    const int      nOpacity,
    const int      nBackgroundOpacity,
    const double   dLatitude,
    const double   dLongitude)
{
    const int MSG_SIZE = 56;
    const int MSG_ID = 152;
    const int MSG_VER = 1;
    char pHeader[HDR_SIZE];
    char pMessage[MSG_SIZE];

    // Populate the message header
    PackHeader(pHeader, MSG_SIZE, RESERVED, MSG_ID, MSG_VER);

    // Copy over message
    memcpy(&pMessage[0], &nFSUID, SIZEOFINT);
    memcpy(&pMessage[4], &nKey, SIZEOFINT);
    memcpy(&pMessage[8], &nSkinIndex, SIZEOFINT);
    memcpy(&pMessage[12], &dOrientation, SIZEOFDOUBLE);
    memcpy(&pMessage[20], &nRotateFlag, SIZEOFINT);
    memcpy(&pMessage[24], &dMagnification, SIZEOFDOUBLE);
    memcpy(&pMessage[32], &nOpacity, SIZEOFINT);
    memcpy(&pMessage[36], &nBackgroundOpacity, SIZEOFINT);
    memcpy(&pMessage[40], &dLatitude, SIZEOFDOUBLE);
    memcpy(&pMessage[48], &dLongitude, SIZEOFDOUBLE);

    // Send Message
    SendMsg(RESERVED, MSG_ID, pHeader, pMessage);
}
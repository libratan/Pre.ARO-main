//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Commercial Computer Software - Non-deliverable Source Code
// See FAR 52.227-19(c)
// The rights of the Government regarding use, reproduction and disclosure are
// as set forth in the applicable FliteScene contract.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Copyright (C) Harris Corporation 2017  - All Rights Reserved
//*****************************************************************************
// FILE:            FS_Comm.h
//
// CLASSIFICATION:  Unclassified
//
// DESCRIPTION:
//
//      This class acts as the wrapper around the ICD.
//
// LIMITATIONS:     none
//
// SOFTWARE HISTORY:
//
//     See ClearCase (cleartool lshistory)
//
//*****************************************************************************
#if !defined(_FS_COMM_H)
#define _FS_COMM_H 1

#include "FS_Constants.h"       // For FS_Message

//##Documentation
//## **************************************************************************
//## CLASS FS_Comm
//## **************************************************************************
class FS_Comm
{
public:     // Constructors and Destructors

    FS_Comm() {}
    virtual ~FS_Comm() {}

private:    // Prevent copy and assignments (memory safe operations)

    FS_Comm(const FS_Comm&) { /* do not create copies */ }
    FS_Comm& operator=(const FS_Comm&) { return *this; }

private:

    //##Documentation
    //## This function stuffs the header of the given message buffer
    static void PackHeader(void* pBuffer,
                           int   nSize,
                           int   nChannel,
                           int   nId,
                           int   nVersion);

public:

    //##Documentation
    //## Wrapper for sending messages to FliteScene.
    //##
    //## Inputs:
    //##    nChannel - Channel number
    //##    nId      - FliteScene message number
    //##    pHeader  - Pointer to the buffer holding the header
    //##    pMessage - Pointer to buffer storing data to send
    //##
    static void SendMsg(
        int nChannel,
        int nId,
        void * pHeader,
        void * pMessage);

    //##Documentation
    //## **************************************************************************
    //## Swaps the bytes of any 32-bit number on little-endian systems only.
    //## On big-endian systems this function will not alter the value in any way.
    //##
    //## Input/Output:
    //##   pValue - Pointer to a 32-bit value to be byte-swapped
    //##
    //## **************************************************************************
    static void SwapEndianess_32(void * pValue);

    //##Documentation
    //## **************************************************************************
    //## Swaps the bytes of any 64-bit number on little-endian systems only.
    //## On big-endian systems this function will not alter the value in any way.
    //##
    //## Input/Output:
    //##   pValue - Pointer to a 64-bit value to be byte-swapped
    //##
    //## **************************************************************************
    static void SwapEndianess_64(void * pValue);

    //##Documentation
    //## Returns the message Endian flag of the given buffer
    //##
    //## Inputs:
    //##   pMessage - Pointer to the message buffer
    //##
    //## Returns:
    //##   int - Endian flag of the message
    static int GetMessageEndian(const void* pMessage);

    //##Documentation
    //## Returns the message Channel ID of the given buffer
    //##
    //## Inputs:
    //##   pMessage - Pointer to the message buffer
    //##
    //## Returns:
    //##   int - Channel of the message
    static int GetMessageChannel(const void* pMessage);

    //##Documentation
    //## Returns the message ID of the given buffer
    //##
    //## Inputs:
    //##   pMessage - Pointer to the message buffer
    //##
    //## Returns:
    //##   int - ID of the message
    static int GetMessageId(const void* pMessage);

    //##Documentation
    //## This is FliteScene Message 3 as defined by the ICD.  See Doc# 8015395.
    //## Provides the dimensions of the OpenGL Viewport on which the map will be
    //##  rendered.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Viewport(
        int nChannel,
        int nViewportIndex,
        int nEnableFlag,
        int nViewportLowerLeftX,
        int nViewportLowerLeftY,
        int nViewportWidth,
        int nViewportHeight);

    //##Documentation
    //## This is FliteScene Message 4 as defined by the ICD.  See Doc# 8015395.
    //## Provides a mapping of 16 bit elevation values to 8 bit values used in
    //##  Threat Inter-visibility calculations. Note: This message is not used
    //##  if the graphics driver supports (and FliteScene is configured to use)
    //##  Pixel Shader
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TIVAltitudeTable(
        int         nChannel,
        const void* pTable);

    //##Documentation
    //## This is FliteScene Message 5 as defined by the ICD.  See Doc# 8015395.
    //## Provides a mapping of 16 bit elevation values to 8 bit values used in
    //##  Elevation Bands calculations. Note: This message is not used if the
    //##  graphics driver supports (and FliteScene is configured to use) Pixel
    //##  Shader or Height Field.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_EBAltitudeTable(
        int         nChannel,
        const void* pTable);

    //##Documentation
    //## This is FliteScene Message 6 as defined by the ICD.  See Doc# 8015395.
    //## Defines the current display mode of FliteScene.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Mode(
        int         nChannel,
        int         nMode,
        const char* szProductCode,
        double      dRange);

    //##Documentation
    //## This is FliteScene Message 7 as defined by the ICD.  See Doc# 8015395.
    //## Defines the geographic position, velocity, altitude, pitch, roll,
    //##  heading, and the 3D perspective viewpoint of the indexed vehicle.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_FlightDynamics(
        int nVehicle,
        int nCount,
        ...);

    //##Documentation
    //## This is FliteScene Message 8 as defined by the ICD.  See Doc# 8015395.
    //## The amount of magnification to be applied to the display.  Not valid
    //##  for Data Frame Underlay.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Zoom(
        int    nChannel,
        double dZoom);

    //##Documentation
    //## This is FliteScene Message 9 as defined by the ICD.  See Doc# 8015395.
    //## The amount of horizontal and vertical decenter to be applied.  Decenter
    //##  is only valid in 2D view. The screen percentages are defined with the
    //##  50% midpoint at the center of the screen.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Decenter(
        int    nChannel,
        double dDecenterX,
        double dDecenterY);

    //##Documentation
    //## This is FliteScene Message 10 as defined by the ICD.  See Doc# 8015395.
    //## Specifies the data frame to be displayed, and how to orient the image
    //##  relative to the screen.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_DataFrameControl(
        int         nChannel,
        int         nScreenPositionX,
        int         nScreenPositionY,
        double      dOrientation,
        double      dZoom,
        const char* szFilename);

    //##Documentation
    //## This is FliteScene Message 11 as defined by the ICD.  See Doc# 8015395.
    //## Enables or disables the selected map overlay
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_OverlaySelect(
        int nChannel,
        int nEnableFlag,
        int nOverlayType);

    //##Documentation
    //## This is FliteScene Message 12 as defined by the ICD.  See Doc# 8015395.
    //## Defines a color to be used for a map feature, as described below.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_OverlayColors(
        int nChannel,
        int nColorID,
        int nRedValue,
        int nGreenValue,
        int nBlueValue,
        int nAlphaValue);

    //##Documentation
    //## This is FliteScene Message 13 as defined by the ICD.  See Doc# 8015395.
    //## Defines the dynamic properties of the slope shading overlay.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SlopeShadingControl(
        int    nChannel,
        int    nSunAzimuthSelect,
        double dSunAzimuth);

    //##Documentation
    //## This is FliteScene Message 14 as defined by the ICD.  See Doc# 8015395.
    //## Defines the dynamic properties of the contour line overlay.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_ContourLineControl(
        int nChannel,
        double dBaseElevation,
        double dLineSpacing);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 118 as defined by the ICD.  See Doc# 8015395.
    //## Defines the properties of the Vertical Bands overlay.
    //##
    //## Return:
    //##   int - '1' indicates that the message was successfully sent.
    //##         '0' indicates that the message failed to sent.
    //##
    //## **********************************************************************
    static void SendMsg_VerticalBandsControl(
        int         nChannel,
        const void* pData);

    //##Documentation
    //## This is FliteScene Message 15 as defined by the ICD.  See Doc# 8015395.
    //## Defines the dynamic properties of the Elevation Bands overlay.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_ElevationBandsControl(
        int nChannel,
        int nDeltaHeight1,
        int nDeltaHeight2,
        int nDeltaHeight3,
        int nDeltaHeight4,
        int nDeltaHeight5,
        int nDeltaHeight6,
        int nDeltaHeight7);

    //##Documentation
    //## This is FliteScene Message 16 as defined by the ICD.  See Doc# 8015395.
    //## Defines a threat’s location and characteristics for TIV. Note: Threats
    //##  can also be set using XML via the ThreatXML message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Threat(
        const int nAction,
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
        const char * szMIL_STD2525_Code);

    //##Documentation
    //## This is FliteScene Message 17 as defined by the ICD.  See Doc# 8015395.
    //## Defines a geo chip’s location and characteristics.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_GeoChip(
        int         nChannel,
        int         nActionType,
        int         nGeoChipID,
        double      dGeoChipLatitude1,
        double      dGeoChipLongitude1,
        double      dGeoChipLatitude2,
        double      dGeoChipLongitude2,
        double      dDiscernableFactor,
        const char* szFilename);

    //##Documentation
    //## This is FliteScene Message 18 as defined by the ICD.  See Doc# 8015395.
    //## Defines a request for a Screen coordinate based on a Lat/Lon coordinate
    //##  (2D), a Screen coordinate based on a Lat/Lon coordinate and an
    //##  elevation (3D), a Lat/Lon coordinate based on a Screen coordinate
    //##  (2D), an Elevation value based on a Screen coordinate (2D), or an
    //##  Elevation value based on a Lat/Lon coordinate (2D or 3D).  FliteScene
    //##  sends a Geo Response for every Geo Query.  Only one Geo Query is
    //##  processed at a time – if a second query is received before the first
    //##  query has been processed, then the second query is ignored.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_GeoQuery(
        int    nChannel,
        int    nKey,
        int    nInputData,
        int    nOutputData,
        double dScreenX,
        double dScreenY,
        double dLatitude,
        double dLongitude);

    //##Documentation
    //## This is FliteScene Message 20 as defined by the ICD.  See Doc# 8015395.
    //## Requests map status from FliteScene for the specified channel.  The
    //##  status is returned in the Map Status message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Get_Status(int nChannel);

    //##Documentation
    //## This is FliteScene Message 22 as defined by the ICD.  See Doc# 8015395.
    //## Requests the version ID from FliteScene.  The version ID information
    //##  is returned in the Version ID message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Get_Version_ID(void);

    //##Documentation
    //## This is FliteScene Message 24 as defined by the ICD.  See Doc# 8015395.
    //## Used to extract useful data from FliteScene for Harris testing purposes.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TestData(
        int         nChannel,
        int         nTestType,
        const char* szTestData);

    //##Documentation
    //## This is FliteScene Message 26 as defined by the ICD.  See Doc# 8015395.
    //## When this message is received, FliteScene flushes the requested cache
    //##  for all channels and refreshes it by requesting data from mass
    //##  storage.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_RefreshCache(
        int nRefreshUnderlayCacheFlag,
        int nRefreshElevationAndThreatCachesFlag,
        int nRefreshGeoChipCacheFlag);

    //##Documentation
    //## This is FliteScene Message 27 as defined by the ICD.  See Doc# 8015395.
    //## Causes FliteScene to shutdown.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Shutdown(void);

    //##Documentation
    //## This is FliteScene Message 30 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to define and display a MIL-STD-2525 tactical symbol.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SetTacticalSymbol(
        int         nSymbolIndex,
        double      dLatitude,
        double      dLongitude,
        int         nAltitude,
        double      dMagnification,
        double      dOrientation,
        int         nDirectionOfMovementEnable,
        double      dDirectionOfMovementAngle,
        const char* szCharacterCode,
        const char* szTextLabel);

    //##Documentation
    //## This is FliteScene Message 30 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to define and display a MIL-STD-2525 tactical graphic.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SetTacticalGraphic(
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
        double      dDirectionOfMovementAngle);

    //##Documentation
    //## This is FliteScene Message 31 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to change the Vertical Obstruction parameters.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SetVOParameters(
        int nChannel,
        int nWarningHeight,
        int nVO_RefAltitudeSelect);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 32 as defined by the ICD.  See Doc# 8015395.
    //## Defines a request to determine if the Line of Sight between two points
    //##  is clear or obstructed. Only one request is processed at a time – if a
    //##  second query is received before the first query has been processed,
    //##  then the second query is ignored. The query results are returned via
    //##  the Line of Sight Results message. The results can be displayed if
    //##  enabled via the Overlay Select message.
    //##
    //## Return:
    //##   int - '1' indicates that the message was successfully sent.
    //##         '0' indicates that the message failed to sent.
    //##
    //## **********************************************************************
    static void SendMsg_LineofSightQuery(
        int    nChannel,
        int    nKey,
        int    nInputDataType,
        double dX1,
        double dY1,
        double dElevation1,
        double dX2,
        double dY2,
        double dElevation2);

    //##Documentation
    //## This is FliteScene Message 34 as defined by the ICD.  See Doc# 8015395.
    //## Defines a request to determine the terrain intercept point for a given
    //##  line. Only one request is processed at a time – if a second query is
    //##  received before the first query has been processed, then the second
    //##  query is ignored. The query results are returned via the Point of
    //##  Intercept Results message. The results can be displayed if enabled
    //##  via the Overlay Select message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_PointofInterceptQuery(
        int    nChannel,
        double dLatitude,
        double dLongitude,
        int    nElevation,
        double dBearing,
        double dPitch);

    //##Documentation
    //## This is FliteScene Message 36 as defined by the ICD.  See Doc# 8015395.
    //## Defines the time in seconds for up to four trend dots. A trend dot is
    //##  displayed at the aircraft’s projected location in the future.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TrendDot(
        int nChannel,
        int nVehicleID,
        int nDot1_Time,
        int nDot2_Time,
        int nDot3_Time,
        int nDot4_Time);

    //##Documentation
    //## This is FliteScene Message 37 as defined by the ICD.  See Doc# 8015395.
    //## Defines the slew angle and slew position. This message is used to
    //## (a) slew map to a location different from the aircraft location, or
    //## (b) set North-up vs Track-up operation.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Slew(
        int    nChannel,
        int    nSlewHeadingEnabled,
        double dSlewAngle,
        int    nSlewPositionEnabled,
        int    nSlewPositionType,
        double dSlewX,
        double dSlewY);

    //##Documentation
    //## This is FliteScene Message 38 as defined by the ICD.  See Doc# 8015395.
    //## Defines the position and action for cursor operations.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_CursorAction(
        int    nChannel,
        int    nAction,
        int    nSelectType,
        double dX,
        double dY,
        int    nPositionUpdate,
        int    nVerticalRange,
        int    nHorizontalRange,
        int    nObjectID);

    //##Documentation
    //## This is FliteScene Message 42 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to request FliteScene to perform a Capture of the contents
    //##  of a Viewport. The results of the capture are returned via the Screen
    //##  Capture Results message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_ScreenCapture(
        int nChannel,
        int nViewportIndex,
        int nViewportLowerLeftX,
        int nViewportLowerLeftY,
        int nViewportWidth,
        int nViewportHeight);

    //##Documentation
    //## This is FliteScene Message 45 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to define parameters for a specific sensor.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SensorControl(
        int    nVehicleIndex,
        int    nSensorIndex,
        double dPitch,
        double dBearing,
        double dFieldOfView,
        double dAspectRatio);

    //##Documentation
    //## This is FliteScene Message 46 as defined by the ICD.  See Doc# 8015395.
    //## Adjusts the zoom, offset and page number of a PDF data frame.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_RasterControl(
        int    nChannel,
        double dOffsetX,
        double dOffsetY,
        double dZoom,
        int    nPageNumber);

    //##Documentation
    //## This is FliteScene Message 47 as defined by the ICD.  See Doc# 8015395.
    //## Defines the underlay product for any single Underlay Level other than
    //##  the base underlay (level 1).
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_UnderlayLevelProduct(
        int         nChannel,
        int         nUnderlayLevel,
        const char* szUnderlayProductCode);

    //##Documentation
    //## This is FliteScene Message 48 as defined by the ICD.  See Doc# 8015395.
    //## Enables or disables the processing or rendering for any single
    //##  Underlay Level.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_UnderlaySelect(
        int nChannel,
        int nEnableFlag,
        int nProcessingType,
        int nUnderlayLevel);

    //##Documentation
    //## This is FliteScene Message 49 as defined by the ICD.  See Doc# 8015395.
    //## Enables or disables an individual threat overlay.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_ThreatSelect(
        int nChannel,
        int nEnableFlag,
        int nOverlayType,
        int nThreatIndex);

    //##Documentation
    //## This is FliteScene Message 50 as defined by the ICD.  See Doc# 8015395.
    //## Enables or disables an individual geo chip overlay.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_GeochipSelect(
        int nEnableFlag,
        int nOverlayType,
        int nGeochipIndex);

    //##Documentation
    //## This is FliteScene Message 52 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to set a general geo-referenced symbol. General symbols
    //##  include lines, polygons, arcs, graphics (sprite), and strings.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SetGeoUserGeneralSymbol(
        int           nSymbolIndex,
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
        const double* ppLocationArray);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 53 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to set a screen referenced general symbol.
    //##
    //## Return:
    //##   int - '1' indicates that the message was successfully sent.
    //##         '0' indicates that the message failed to sent.
    //##
    //## **********************************************************************
    static void SendMsg_SetScreenUserGeneralSymbol(
        int           nChannel,
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
        const double* ppLocationArray);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 54 as defined by the ICD.  See Doc# 8015395.
    //## Loads the given image into the specified geo symbol skin.  Geo Skins
    //##  are used when defining sprite symbols via the Set Geo User General
    //##  Symbol message.
    //##
    //## Return:
    //##   int - '1' indicates that the message was successfully sent.
    //##         '0' indicates that the message failed to sent.
    //##
    //## **********************************************************************
    static void SendMsg_SetGeoUserSymbolSkin(
        int         nSkinIndex,
        int         nSkinType,
        const char* szFilename);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 55 as defined by the ICD.  See Doc# 8015395.
    //## Loads the given image into the specified screen symbol skin.  Screen
    //##  Skins are used when defining sprite symbols via the Set Screen User
    //##  General Symbol message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    //##
    //## **********************************************************************
    static void SendMsg_SetScreenUserSymbolSkin(
        int         nChannel,
        int         nSkinIndex,
        int         nSkinTypeEnableFlag,
        const char* szFilename);

    //##Documentation
    //## This is FliteScene Message 56 as defined by the ICD.  See Doc# 8015395.
    //## Enables an individual geo-referenced user commanded symbol
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_EnableGeoSymbol(
        int nChannel,
        int nEnableType,
        int nEnableFlag,
        int nSymbolType,
        int nSymbolIndex);

    //##Documentation
    //## This is FliteScene Message 57 as defined by the ICD.  See Doc# 8015395.
    //## Enables an individual Screen Symbol.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_EnableScreenSymbol(
        int nChannel,
        int nEnableFlag,
        int nSymbolType,
        int nSymbolIndex);

    //##Documentation
    //## This is FliteScene Message 58 as defined by the ICD.  See Doc# 8015395.
    //## Sets the elevation value for TIV, Elevation Bands, and VO reference
    //##  altitudes to either the current ownship altitude or to user defined
    //##  values.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_ElevationControl(
        int nChannel,
        int nDefinitionFlag,
        int nParameterCode,
        int nParameterValue);

    //##Documentation
    //## This is FliteScene Message 59 as defined by the ICD.  See Doc# 8015395.
    //## Enables or disables a specific feature of an individual vehicle or
    //##  sensor.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_VehicleEnables(
        int nChannel,
        int nVehicleIndex,
        int nSensorIndex,
        int nEnableFlag,
        int nFeatureType);

    //##Documentation
    //## This is FliteScene Message 61 as defined by the ICD.  See Doc# 8015395.
    //## Sets the Ownship to the specified Vehicle Index.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_OwnshipControl(
        int nChannel,
        int nVehicleIndex);

    //##Documentation
    //## This is FliteScene Message 64 as defined by the ICD.  See Doc# 8015395.
    //## Specifies the start and end points of a line that is used to calculate
    //##  the range and bearing from the start point to the end point. The
    //##  message provides the location of the source and destination,
    //##  FliteScene calculates and renders, if enabled via the Overlay
    //##  Select message, the range/bearing line and a text label with those
    //##  calculated values.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SetRangeandBearing(
        int    nChannel,
        int    nSourceCoordinateType,
        double dSourceX,
        double dSourceY,
        int    nDestinationCoordinateType,
        double dDestinationX,
        double dDestinationY);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 66 as defined by the ICD.  See Doc# 8015395.
    //## Defines a request for an MGRS Grid code based on a coordinate
    //##  (Lat/Lon or Screen X/Y), or a request for a Lat/Lon coordinate based
    //##  on a given MGRS code.  FliteScene sends a MGRS Conversion response for
    //##  every MGRS Conversion request.  Only one MGRS Query is processed at a
    //##  time – if a second query is received before the first query has been
    //##  processed, then the second query is ignored.  The same message format
    //##  is used for the request and response, the Conversion code indicates
    //##  whether the message is a request or a response. In the response
    //##  message, the input values are echoed back, along with the results.
    //##
    //## Return:
    //##   int - '1' indicates that the message was successfully sent.
    //##         '0' indicates that the message failed to sent.
    //##
    //## **********************************************************************
    static void SendMsg_MGRSConversion(
        int         nChannel,
        int         nConversionType,
        double      dScreenX_or_Longitude,
        double      dScreenY_or_Latitude,
        const char* szMGRS_Code);

    //##Documentation
    //## This is FliteScene Message 68 as defined by the ICD.  See Doc# 8015395.
    //## Specifies the parameters for a single waypoint.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_RouteWaypoint(
        int         nWaypointIndex,
        double      dLatitude,
        double      dLongitude,
        double      dElevation,
        double      dOrientation,
        int         nRotateWithMap,
        int         nSpriteType,
        int         nRenderState,
        const char* szLabel);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 69 as defined by the ICD.  See Doc# 8015395.
    //## Specifies the waypoints and parameters for a single route leg. All
    //##  other leg parameters are set through the Route Leg Parameter Message.
    //##
    //## Return:
    //##   int - '1' indicates that the message was successfully sent.
    //##         '0' indicates that the message failed to sent.
    //##
    //## **********************************************************************
    static void SendMsg_RouteLeg(
        int            nRouteLegIndex,
        int            nStartWaypointIndex,
        int            nEndWaypointIndex,
        int            nCorridorWidth,
        int            nLegType,
        int            nLineType,
        int            nTurnDirection,
        int            nSubSegmentCount,
        const double** ppdSubSegmentLatLongElevArray);

    //##Documentation
    //## This is FliteScene Message 70 as defined by the ICD.  See Doc# 8015395.
    //## Specifies the render parameters for a single route leg.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_RouteLegParameters(
        int nRouteLegIndex,
        int nRenderColorIndex,
        int nLineStyleIndex);

    //##Documentation
    //## This is FliteScene Message 71 as defined by the ICD.  See Doc# 8015395.
    //## Specifies the Percent Complete parameters for a single route leg.
    //##  FliteScene renders the percent complete portion of the leg in the
    //##  percent complete color set via the Overlay Colors message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_RouteLegPercentComplete(
        int    nRouteLegIndex,
        double dPercentComplete);

    //##Documentation
    //## This is FliteScene Message 72 as defined by the ICD.  See Doc# 8015395.
    //## This messages allows the user to associate (enable) or disassociate
    //##  (disable) a previously created waypoint or leg to a route group.
    //##  Associating multiple waypoints and legs to a group is accomplished by
    //##  calling this message multiple times (once for each waypoint or leg).
    //##  Once a group is defined, it can be enabled or disabled via the Route
    //##  Group Enable message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_RouteGroup(
        int nGroupIndex,
        int nFeatureType,
        int nFeatureIndex,
        int nEnableFlag);

    //##Documentation
    //## This is FliteScene Message 73 as defined by the ICD.  See Doc# 8015395.
    //## Enables or disables features of a route group for rendering.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_RouteGroupEnable(
        int nChannel,
        int nRouteGroupIndex,
        int nOverlayIndex,
        int nEnableFlag);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 75 as defined by the ICD.  See Doc# 8015395.
    //## This defines a Flight Plan for purposes of route conflict detection and
    //##  resolution. Note: the Route Group message is used for rendering route
    //##  components.
    //##
    //## Return:
    //##   int - '1' indicates that the message was successfully sent.
    //##         '0' indicates that the message failed to sent.
    //##
    //## **********************************************************************
    static void SendMsg_SetFlightPlan(
        int        nFlightPlanID,
        int        nNumberOfLegs,
        const int* pLegIDs);

    //##Documentation
    //## **********************************************************************
    //## This is FliteScene Message 101 as defined by the ICD.  See Doc# 8015395.
    //## This enables or disables features of a route flight plan in
    //##   3D Perspective View.
    //##
    //## **********************************************************************
    static void SendMsg_RouteFlightPlanEnable(
        const int nChannel,
        const int nFlightPlanIndex,
        const int nOverlayCode,
        const int nEnableFlag);

    //##Documentation
    //## This is FliteScene Message 82 as defined by the ICD.  See Doc# 8015395.
    //## Defines the display configuration of the Elevation Profile window.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_ElevationProfileControl(
        int    nChannel,
        double dProfileScale,
        double dProfileStart);

    //##Documentation
    //## This is FliteScene Message 83 as defined by the ICD.  See Doc# 8015395.
    //## Sets the icon definition for a vehicle.  If used, this message will
    //##  supersede the XML configuration for a vehicle definition.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_VehicleIcon(
        int         nChannel,
        int         nVehicleIndex,
        int         nImageFlag,
        const char* szIconPath);

    //##Documentation
    //## This is FliteScene Message 84 as defined by the ICD.  See Doc# 8015395.
    //## Specifies the parameters for a single route leg
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_RouteLegGate(
        int         nRouteLegIndex,
        int         nGateType,
        int         nEnableFlag,
        int         nDistanceMeters,
        const char* szTextLabel);

    //##Documentation
    //## This is FliteScene Message 85 as defined by the ICD.  See Doc# 8015395.
    //## Specifies the parameters for a single racetrack route leg.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_Racetrack(
        int    nRouteLegIndex,
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
        double dLongitude4);

    //##Documentation
    //## This is FliteScene Message 88 as defined by the ICD.  See Doc# 8015395.
    //## Enables or disables an individual Text Box
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TextBoxEnable(
        int nChannel,
        int nTextBoxIndex,
        int nEnableFlag);

    //##Documentation
    //## This is FliteScene Message 89 as defined by the ICD.  See Doc# 8015395.
    //## Performs operations on a Text Box’s text buffer including setting text
    //##  and clearing the buffer
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TextBoxSetText(
        int         nChannel,
        int         nTextBoxIndex,
        int         nClearFirstFlag,
        int         nCharacterStartIndex,
        const char* szNewText,
        int         nNewTextLength);

    //##Documentation
    //## This is FliteScene Message 90 as defined by the ICD.  See Doc# 8015395.
    //## Performs operations on a Text Box’s text buffer including inserting
    //##  text and clearing the buffer.  All operations are performed in the
    //##  currently active text box at the current text cursor position.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TextBoxInsertText(
        int         nChannel,
        int         nTextBoxIndex,
        int         nClearFirstFlag,
        const char* szNewText,
        int         nNewTextLength);

    //##Documentation
    //## This is FliteScene Message 91 as defined by the ICD.  See Doc# 8015395.
    //## Sets the size and position of a single Text box.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TextBoxSetGeometry(
        int nChannel,
        int nTextBoxIndex,
        int nUsableBufferSize,
        int nTextBoxLowerLeftX,
        int nTextBoxLowerLeftY,
        int nTextBoxWidth,
        int nTextBoxHeight,
        int nTextBoxFont);

    //##Documentation
    //## This is FliteScene Message 92 as defined by the ICD.  See Doc# 8015395.
    //## Moves the Text Cursor to the upper-left corner of the specified Text
    //##  Box.  The specified Text Box is then the active box, and will be
    //##  rendered on top of all other boxes.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TextBoxSetActive(
        int nChannel,
        int nTextBoxIndex);

    //##Documentation
    //## This is FliteScene Message 93 as defined by the ICD.  See Doc# 8015395.
    //## Sets the viewing "window" that dictates what section of the text buffer
    //##  is viewable within the Text box. This does not affect the position of
    //##  the text cursor; it must be set separately with the Insert Text
    //##  command.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TextBoxSetRegion(
        int nChannel,
        int nTextBoxIndex,
        int nAbsoluteRelativeFlag,
        int nLinePageMode,
        int nLinePageIndex);

    //##Documentation
    //## This is FliteScene Message 94 as defined by the ICD.  See Doc# 8015395.
    //## Gets the text buffer from the specified Text Box and returns the buffer
    //##  to the user via the TextBoxContentsResponse message.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_TextBoxGetContents(
        int nChannel,
        int nTextBoxIndex);

    //##Documentation
    //## This is FliteScene Message 114 as defined by the ICD.  See Doc# 8015395.
    //## Defines a color to be used for a specific text box.
    //##
    static void SendMsg_TextBoxSetColors(
        const int nChannel,
        const int nTextBoxIndex,
        const int nType,
        const int nRedValue,
        const int nGreenValue,
        const int nBlueValue,
        const int nAlphaValue);

    //##Documentation
    //## This is FliteScene Message 97 as defined by the ICD.  See Doc# 8015395.
    //##
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_CompassRoseControl(
        int nChannel,
        int nConfigurationSelection);

    //##Documentation
    //## This is FliteScene Message 98 as defined by the ICD.  See Doc# 8015395.
    //##
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_CompassPointerControl(
        int    nChannel,
        int    nEnableFlag,
        int    nPointerSelection,
        double dPointerAngle);

    //##Documentation
    //## This is FliteScene Message 107 as defined by the ICD.  See Doc# 8015395.
    //## Generates and displays a search area on the map.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SearchPattern(
        int    nIndex,
        int    nType,
        int    nNumberOfTracks,
        int    nTrackLength,
        int    nTrackSpacing,
        int    nFirstTurnDirection,
        double dLatitude,
        double dLongitude,
        double dInitialHeading);

    //##Documentation
    //## This is FliteScene Message 106 as defined by the ICD.  See Doc# 8015395.
    //## Generates and displays a search area on the map.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_SearchArea(
        int    nIndex,
        int    nInitialRadius,
        double dGrowthRate,
        double dLatitude,
        double dLongitude);

    //##Documentation
    //## This is FliteScene Message 112 as defined by the ICD.  See Doc# 8015395.
    //## Updates the metadata text for a specified FliteScene object.
    //##
    static void SendMsg_SetMetaData(
        const int nObjectID,
        const char * szObjectMetadata);

    //##Documentation
    //## This is FliteScene Message 116 as defined by the ICD.  See Doc# 8015395.
    //## Adds/Deletes a GeoTiff file to an existing product code.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_DynamicGeoTiff(
        int         nAction,
        const char* szProductCode,
        const char* szFileName);

    //##Documentation
    //## This is FliteScene Message 117 as defined by the ICD.  See Doc# 8015395.
    //## Defines what vertical data FliteScene will process
    //##
    static void SendMsg_VerticalDataProcessing(
        const int nElevationDataProccessing,
        const int nDepthDataProcessing);

    //##Documentation
    //## This is FliteScene Message 121 as defined by the ICD.  See Doc# 8015395.
    //## Adds an offset to the compass rose.
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_MagNorth(double dAngle);

    //##Documentation
    //## This is FliteScene Message 115 as defined by the ICD.  See Doc# 8015395.
    //## Declutters object group(s).
    //##
    //## Return:
    //## int - '1' indicates that the message was successfully sent.
    //##       '0' indicates that the message failed to sent.
    static void SendMsg_ObjectGroupDeclutter(
        int*  arParameterCode,
        void* arParameterValue1,
        int*  arParameterValue2,
        int   nNumParameters);

    //##Documentation
    //## This is FliteScene Message 123 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to set general geo-reference multi-point symbol.
    //## Note: This is different from the Set Geo Symbol msg.
    //##
    static void SendMsg_SetGeoMultiPointSymbol(
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
		const double    arLocations[][3]);

    //##Documentation
    //## This is FliteScene Message 124 as defined by the ICD.  See Doc# 8015395.
    //## Allows user to set general geo-reference multi-point symbol.
    //## Note: This is different from the Set Geo Symbol msg.
    //##
    static void SendMsg_SetGeoPointSymbol(
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
		const int      nLabelFontIndex);

	//##Documentation
	//## This is FliteScene Message 151 as defined by the ICD.  See Doc# 8015395.
	//## Allows the user to set an off-screen indicator for a given geo user
	//## symbol’s FSUID. This applies to symbols utilized by the Set Geo Symbol,
    //## Set Geo Point Symbol, Set Geo Multi - Point Symbol, Set Geo Arc Symbol,
    //## and Set Geo String messages.
	//##
	static void SendMsg_SetGeoSymbolOffscreenIdicator(
		const int nFSUID,
		const int nAction,
		const int nSpriteIndex);

    //##Documentation
    //## This is FliteScene Message 130 as defined by the ICD.  See Doc# 8015395.
    //## Processes the specified symbol file with the given action.
    //## At present this is used for dynamically loading files such as Drawing Files,
    //##    Local Points, and Manual CHUM.
    //##
    static void SendMsg_SymbolFileAction(
        const int nAction,
        const int nType,
        const int nEnableFlag,
        const char * szFileName,
        int nCount, 
        ...);

    //##Documentation
    //## This is FliteScene Message 131 as defined by the ICD.  See Doc# 8015395.
    //## Defines the color component for the monochrome output.
    //##
    static void SendMsg_MonochromeSelect(
        const int nChannel,
        const int nEnableState,
        const int nMonochromeMode);

    //##Documentation
    //## This is FliteScene Message 135 as defined by the ICD.  See Doc# 8015395.
    //## Configures the Perspective Landing Zone
    //##
    static void SendMsg_LandingZone(
        const int    nChannel,
        const double dLatitude,
        const double dLongitude,
        const double dApproachBearing,
        const int    nResolutionMode);

    //##Documentation
    //## This is FliteScene Message 138 as defined by the ICD.  See Doc# 8015395.
    //## Sets the color and opacity of the Vehicle History Trail.
    //##
    static void SendMsg_VehicleHistoryProperties(
        const int nVehicleIndex,
        const int nRedValue,
        const int nGreenValue,
        const int nBlueValue,
        const int nAlphaValue);

    //##Documentation
    //## This is FliteScene Message 142 as defined by the ICD.  See Doc# 8015395.
    //## Selects the cursor icon and configures the cursor highlight box (size, outline color, and fill color)
    //##
    static void SendMsg_CursorConfiguration(
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
        const int    nFillAlpha);

    //##Documentation
    //## This is FliteScene Message 143 as defined by the ICD.  See Doc# 8015395.
    //## Sets configuration data for an individual sensor on a vehicle
    //##
    static void SendMsg_SensorConfiguration(
        const int nVehicleIndex,
        const int nSensorIndex,
        const int nTextureID);

    //##Documentation
    //## This function sets the current time for flitescene.
    static void SendMsg_SetTime(
        int          nChannel,
        unsigned int nYear,
        unsigned int nMonth,
        unsigned int nDay,
        unsigned int nHour,
        unsigned int nMin,
        unsigned int nSec);

    //##Documentation
    //## This is the fulle FliteScene Message 137 as defined by the ICD.
    //## See Doc# 8015395.
    //## Sets the virtual “camera” orientation for the wingman view in the 3D
    //##  perspective map mode.
    //##
    static void SendMsg_PerspectiveCameraFull(
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
        const int nRelativeAttitdue);

    //##Documentation
    //## This is FliteScene Message 146 as defined by the ICD.  See Doc# 8015395.
    //## Enables an object with a FliteScene UID
    static void SendMsg_EnableByUID(
        const int nChannel,
        const int nEnableFlag,
        const int nFSUID);

    //##Documentation
    //## This is the FliteScene Message 148 as defined by the ICD.
    //## See Doc# 8015395.
    //## Sets Range Rings
    //##
    static void SendMsg_SetRangeRingSymbol(
        const int      nFSUID,
        const int      nKey,
        const int      nRRDef,
        const int      nRRCenterPoint,
        const double   dLat,
        const double   dLon,
        const int      nCPUID,
		const double   dScreenX,
		const double   dScreenY);

    //##Documentation
    //## This is the FliteScene Message 41 as defined by the ICD.
    //## See Doc# 8015395.
    //## Sets Dynamic Instruments
    //##
    static void SendMsg_SetDynamicInstrument(
        const int      nIndex,
        const double   dScreenX,
        const double   dScreenY);

    //##Documentation
    //## This is the FliteScene Message 150 as defined by the ICD.
    //## See Doc# 8015395.
    //## Defines a request to convert from decimal Degrees coordinates to 
    //## Degrees Minutes Seconds (DMS) coordinates and vice versa.
    //##
    static void SendMsg_DMS_Conversion(
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
        const char *   szOutputString);

    //##Documentation
    //## This is the FliteScene Message 152 as defined by the ICD.
    //## See Doc# 8015395.
    //## Allows user to set a stormscope geo-referenced symbol in Plan View.
    //##
    static void SendMsg_SetStormscopeSymbol(
        const int      nFSUID,
        const int      nKey,
        const int      nSkinIndex,
        const double   dOrientation,
        const int      nRotateFlag,
        const double   dMagnification,
        const int      nOpacity,
        const int      nBackgroundOpacity,
        const double   dLatitude,
        const double   dLongitude);

private:    // Private Constants

    //##Documentation
    //## Constants used within this class.
    enum FS_COMM_CONSTANTS
    {
        HDR_SIZE              = 20,
        MAX_MSG_SIZE          = 16384, // 16KB
        SIZEOFINT             = sizeof(int),
        SIZEOFDOUBLE          = sizeof(double)
    };

    typedef unsigned __int32 FS_uint32;

private:    // Private Member Data

};

#endif

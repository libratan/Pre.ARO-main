/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++ FliteScene Interface Source Code
++ FliteScene License holders are authorized to use this source code file
++ for the purposes of integrating FliteScene with their software applications
++ in accordance with the license agreement.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
** Copyright (C) L3Harris Technologies 2006, 2010-2016, 2019 - All Rights Reserved
*/
/******************************************************************************
** FILE:            FliteScene.h
**
** CLASSIFICATION:  Unclassified
**
** DESCRIPTION:
**
**   This file defines the FliteScene interface function prototypes.
**
** LIMITATIONS:     none
**
** SOFTWARE HISTORY:
**
**     See ClearCase (cleartool lshistory)
**
******************************************************************************/
#ifndef _FLITESCENE_H
#define _FLITESCENE_H 1

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
** Initializes the Map. This must be called first.
**
** Input:
**   pXMLBuffer - Memory buffer containing the directory configuration file
**                (null terminated).
**
** Return:
**   1: If successful
**   0: Otherwise
**
******************************************************************************/
int FS_Initialize_Map(char* pXMLBuffer);

/******************************************************************************
** Initializes the graphics memory and interfaces
**
** Input:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**
** Return:
**   1: If successful
**   0: Otherwise
**
** ***************************************************************************/
int FS_Initialize_Graphics(int nChannel);

/******************************************************************************
** Spawns the task for each library. This method must only be called once
** initialization for each channel has completed.
**
** Inputs:
**  nEnableMemoryManager - Indicates whether to use the OS memory management(0)
**                         or FliteScene's custom memory manager(1).
**                         No dynamic allocations will occur after this function
**                         call if using the FS memory manager.
**
******************************************************************************/
void FS_Finish_Initialization(int nEnableMemoryManager);

/******************************************************************************
** Returns FliteScene's initialization state. Having been initialized indicates
** that all of the static and dynamic memory allocations based on configuration
** file parameters, as well as spawning of threads, have been completed.
** Note, additional "run-time" initialization may still be in progress for
** symbol loading activities.
**
** Applications can poll this function to ensure FliteScene has been
** initialized before sending messages to it.
**
** Return:
**   0: If FliteScene is not initialized.
**   1: If FliteScene is initialized.
******************************************************************************/
int FS_Get_Initialize_State(void);

/******************************************************************************
** Clears the frame buffer for rendering. Allows FliteScene to specify which
** buffers to clear based on features enabled (Depth, Stencil, Color).
**
** Input:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**
******************************************************************************/
void FS_Clear_Screen(int nChannel);

/******************************************************************************
** Renders all geo-located and then all screen-located objects. Also handles
** message processing. 
**
** This is the equivalent of calling FS_Render_With_Style(nChannel, 0).
**
** Input:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**
******************************************************************************/
void FS_Render(int nChannel);

/******************************************************************************
** Renders all geo-located and screen-located objects. Also handles message
** processing. Delegates geo and screen rendering to FS_Render_Map and
** FS_Render_Symbols.
**
** Input:
**   nChannel    - Channel number in the range [0, NUM_CHANNELS)
**   nLayerStyle - 0 to render geo, then screen symbols
**                 1 to render mixed symbols
**
******************************************************************************/
void FS_Render_With_Style(int nChannel,
                          int nLayerStyle);

/******************************************************************************
** Alternative to FS_Render(). This differs from FS_Render in that it does 
** NOT process messages first. In normal usage, FS_Process_Messages must be 
** called before each FS_Render_Frame call. 
**
** This is the equivalent of calling FS_Render_Frame_With_Style(nChannel, 0).
**
** Input:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**
******************************************************************************/
void FS_Render_Frame(int nChannel);

/******************************************************************************
** Alternative to FS_Render_With_Style(). This differs from 
** FS_Render_With_Style in that it does NOT process messages first. In normal 
** usage, FS_Process_Messages must be called before each 
** FS_Render_Frame_With_Style call. Delegates geo and screen rendering to 
** FS_Render_Map and FS_Render_Symbols.
**
** Input:
**   nChannel    - Channel number in the range [0, NUM_CHANNELS)
**   nLayerStyle - 0 to render geo, then screen symbols
**                 1 to render mixed symbols
**
******************************************************************************/
void FS_Render_Frame_With_Style(int nChannel,
							    int nLayerStyle);

/******************************************************************************
** Alternative to FS_Render_Frame(). This differs from FS_Render_Frame in 
** that it only renders the geo-registered objects (map and symbols). In 
** normal usage, FS_Process_Messages must be called before each FS_Render_Geo 
** call. 
**
** This is the equivalent of calling FS_Render_Map(nChannel) followed by
** FS_Render_Symbols(nChannel, 1).
**
** Input:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**
******************************************************************************/
void FS_Render_Geo(int nChannel);

/******************************************************************************
** Alternative to FS_Render_Frame(). This differs from FS_Render_Frame in 
** that it only renders the screen-registered symbols. In normal usage,
** FS_Process_Messages must be called before each FS_Render_Screen call.
**
** This is the equivalent of calling FS_Render_Symbols(nChannel, 2).
**
** Input:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**
******************************************************************************/
void FS_Render_Screen(int nChannel);

/******************************************************************************
** Alternative to FS_Render_Frame_With_Style(). This differs from 
** FS_Render_Frame_With_Style in that it only renders the map underlays and 
** map-conformal overlays (e.g. elevation overlays, geochips). In normal usage, 
** FS_Process_Messages must be called before each FS_Render_Map call.
**
** Input:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**
******************************************************************************/
void FS_Render_Map(int nChannel);

/******************************************************************************
** Alternative to FS_Render_Frame_With_Style(). This differs from 
** FS_Render_Frame_With_Style in that it only renders symbols non-conformal 
** (e.g. user symbols, DAFIF, ARINC) with the map underlays. In normal usage, 
** FS_Process_Messages must be called before each FS_Render_Symbols call.
**
** Input:
**   nChannel -    Channel number in the range [0, NUM_CHANNELS)
**   nSymbolType - Specify which symbol type(s) to render.
**                 0 => screen and geo symbols
**                 1 => geo symbols
**                 2 => screen symbols
**
******************************************************************************/
void FS_Render_Symbols(int nChannel,
                       int nSymbolType);

/******************************************************************************
** Alternative to FS_Render_Frame_With_Style(). This function only performs 
** message processing of messages received via FS_Set_Message. No rendering 
** is performed.
**
** Input:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**
******************************************************************************/
void FS_Process_Messages(int nChannel);

/******************************************************************************
** Calls SetData function of a message object specified by MessageID
**
** Input:
**   nChannel     - Channel number in the range [0, NUM_CHANNELS)
**   nMessageID   - Specifies the ID of message to set data.
**   pHeader      - Pointer to message header buffer.
**   pMessage     - Pointer to message data buffer.
**
** Return:
**   1: If successful
**   0: Otherwise
**
******************************************************************************/
int FS_Set_Message(int   nChannel,
                   int   nMessageID,
                   void* pHeader,
                   void* pMessage);

/******************************************************************************
** Returns the number of channels as defined in the FliteScene_Config.xml file.
**
** Return:
**   Number of channels (NUM_CHANNELS) for which FliteScene is configured.
******************************************************************************/
int FS_Get_Channel_Count(void);

/******************************************************************************
** Returns the height and width of the map viewport for the specified channel.
** These values are contained in the FliteScene config XML file. This function
** can only be called after the map is initialized (FS_Initialize_Map is
** called).
**
** Input:
**   nChannel  - Channel number in the range [0, NUM_CHANNELS)
**
** Output:
**   nWidth    - Width (in pixels) of the map viewport for the secified channel
**               Provided pointer must be non-null and point to a valid int.
**   nHeight   - Height (in pixels) of the map viewport for the secified channel
**               Provided pointer must be non-null and point to a valid int.
**
** Return:
**   1: If successful
**   0: Otherwise
**
******************************************************************************/
int FS_Get_Viewport_Size(int  nChannel,
                         int* nWidth,
                         int* nHeight);

/******************************************************************************
** Gets the latitude,longitude, and elevation for a given screen location.
** When in Perspective 3D mode, this function should be called before calling
** FS_Render (or FS_Render_Frame/Render_Geo, depending on which function(s)
** are in use) as opposed to after. Must be called from render thread to
** get valid results in perspective mode.
**
** Inputs:
**   nChannel - Channel number in the range [0, NUM_CHANNELS)
**   dScreenX - Position in pixels in the X direction from the center of the
**              screen.
**              Provided pointer must be non-null and point to a valid double.
**   dScreenY - Position in pixels in the Y direction from the center of the
**              screen.
**              Provided pointer must be non-null and point to a valid double.
**
** Outputs:
**   dLatitude  - Passes back latitude based on ScreenX.
**   dLongitude - Passes back longitude based on ScreenY.
**
******************************************************************************/
void FS_Get_Position_From_Screen(int     nChannel,
                                 double  dScreenX,
                                 double  dScreenY,
                                 double* dLatitude,
                                 double* dLongitude);

/******************************************************************************
** Gets the elevation for a given geo location (in scene).
**
** Inputs:
**   nChannel   - Channel number in the range [0, NUM_CHANNELS)
**   dLatitude  - Latitude position in degrees.
**   dLongitude - Longitude position in degrees.
**
** Outputs:
**   nElevation - Passes back the elevation (in meters)
**                Provided pointer must be non-null and point to a valid int.
**
** Returns:
**   int- value indicating the type of elevation value retrieved from
**        the scene. Refer to the GeoResponse ICD message.
**
******************************************************************************/
int FS_Get_Elevation_From_Geo(int    nChannel,
                              double dLatitude,
                              double dLongitude,
                              double* pElevation);

/******************************************************************************
**  This method assists in geo-locating data into the 3D scene. It provides
**  the capability to convert an array of latitudes/longitudes/elevations
**  into either object space (3D coordinates) for rendering in 3D OR
**  screen space coordinates to locate where it is on screen. The map must
**  be in Perspective mode for valid results to be returned.
**
**  Inputs:
**    nChannel    - Channel number in the range [0, NUM_CHANNELS)
**    nVertexType - Vertex type that should be output from this method.
**                    Type: GEO_REQUEST(0) or SCREEN_REQUEST(1)
**    nNumVertices- Number of points in the following arrays.
**    pLatitudes  - An array of nNumVertices latitudes.
**    pLongitudes - An array of nNumVertices longitudes.
**    pElevations - An array of nNumVertices elevations.
**    pVertices   - A user allocated array to store the results of this call.
**                  The size of the array is dependent on the output, detailed below.
**
**  Outputs:
**    pVertices   - The output array is the resulting conversion of the given
**                  lat/lon/elev into the desired VertexType. When processing
**                  different output VertexTypes, pVertices will be interpreted
**                  differently.
**                  Types:
**                  *GEO_REQUEST(0): The output, pVertices, is interpreted as
**                     an array of length 3*sizeof(float)*nNumVertices. Each
**                     set of three floats within the array are object
**                     space (x,y,z) coordinates for rendering. I.E.,
**                     x is the distance between the requested location and the
**                     focus location in the longitude direction in meters, y
**                     is the distance in the latitude direction in meters, and
**                     z is the input altitude.
**
**                  *SCREEN_REQUEST(1): The output, pVertices, is interpreted as
**                     an array of length 3*sizeof(int)*nNumVertices. Each
**                     set of three integers have the following meaning:
**                     (ScreenX, ScreenY, OnScreen). The OnScreen element
**                     will indicate if the element is visible on screen (1.0f)
**                     or not (0.0f).
**
******************************************************************************/
void FS_GeoVertex(int     nChannel,
                  int     nVertexType,
                  int     nNumVertices,
                  double* pLatitudes,
                  double* pLongitudes,
                  int*    pElevations,
                  void*   pVertices);

/******************************************************************************
**  Gets the modelview and projection matrices that are used to render the
**  FliteScene map. This is necessary to render objects on top of the
**  scene in any external rendering functions when using the OpenGL ES 2.0
**  specification, as the matrices are no longer stored by OpenGL.
**
**  Output:
**    pModelview  - preallocated size 16 float array to store modelview matrix.
**    pProjection - preallocated size 16 float array to store projection matrix.
**
******************************************************************************/
void FS_Get_Transform_Matrices(float* pModelView,
                               float* pProjection);

#ifdef __cplusplus
} /* end export "C" */
#endif

#endif

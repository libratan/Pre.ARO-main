// This file is currently for testing map scaling functions.
#include <../DMM/header/MapScale.h>
#include <../DMM/header/FS_Comm.h>

// Static Map Product Codes Array - Only listed a few in order
// To explore how to obtain list from XML. Not sure if FlightScene already stores it somewhere after reading CONFIG_DIRECTORY.XML
static char s_arMapProductCodes[][FS_Constants::MAX_FILENAME_LENGTH] = {
    "Q1",
    "Q2",
    "GN",
    "JN",
    "ON",
    "Q3",
    "TP",
    "LF",
    "ES",
    "JA",
    "TF",
    "QB"}; 

static int nMapScaleCode = 0;

void MapScale::IncreaseMapScale()
{
    if (strlen(s_arMapProductCodes[nMapScaleCode + 1]) == 2)
    {
        int nChannel = 0;
        nMapScaleCode += 1;

        FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::UNDERLAY_FILE_SCALING);
        //FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::CONTOUR_LINES);

        FS_Comm::SendMsg_Mode(0,    // Channel
            0,    // Mode - 0 for 2D, 1 for 3D
            s_arMapProductCodes[nMapScaleCode], // Underlay Product Code defined in CONFIG_DIRECTORY.XML - "Q1" for Geotiff 4km
            0.0); // Range - Distance in nautical miles from top to bottom of the Map Window viewport.  Only applicable in 2D.


    }
    else
    {
        // Already using smallest scale map
    }

}

void MapScale::DecreaseMapScale()
{
    if (nMapScaleCode > 0)
    {
        int nChannel = 0;
        nMapScaleCode -= 1;

        FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::UNDERLAY_FILE_SCALING);
        //FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::CONTOUR_LINES);

        FS_Comm::SendMsg_Mode(0,    // Channel
            0,    // Mode - 0 for 2D, 1 for 3D
            s_arMapProductCodes[nMapScaleCode], // Underlay Product Code defined in CONFIG_DIRECTORY.XML - "Q1" for Geotiff 4km
            0.0); // Range - Distance in nautical miles from top to bottom of the Map Window viewport.  Only applicable in 2D.
    }
    else
    {
        // Already using furthest scale map
    }

}
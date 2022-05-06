#include <../DMM/header/FS_Comm.h>
#include <../DMM/header/FS_Constants.h>
#include <../DMM/header/MapTactical.h>

// This function turns on all the overlays for the tactical symbols and graphics to be shown.
void MapTactical::SetMapTacticalOverlays()
{
    int nChannel = 0;

    // Enable / disable selected map overlays
    // Global enable/disable for MIL STD 2525 Symbols
    // This overlay setting affects both symbols and graphics.  If any of the layer needs to be enabled this must be enabled.
    // Disabling this overlay disables all tactical symbols and graphics overlays.
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::TACTICAL_SYMBOLS);

    // Different Standard ID Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::AFFILIATION_FRIEND);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::AFFILIATION_NEUTRAL);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::AFFILIATION_HOSTILE);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::AFFILIATION_UNKNOWN);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::AFFILIATION_EXCERCISE);

    // Different Dimension Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::DIMENSION_UNKNOWN);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::DIMENSION_SPACE);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::DIMENSION_AIR);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::DIMENSION_GROUND);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::DIMENSION_SEA_SURFACE);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::DIMENSION_SUB_SURFACE);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::DIMENSION_SOF);

    // Frame, Fill, and Icon modifiers for Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::FILL_MODIFIER);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::ICON_MODIFIER);
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::FRAME_MODIFIER);

    // Tactical Symbol Text Modifier
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::TACTICAL_LABEL);

    // Movement Indicator of Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::MOVEMENT_INDICATOR);

    
    // Global enable/disable for all Tactical Graphics
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::TACTICAL_GRAPHICS);

    // Tactical Graphics Text Modifier
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::TACTICAL_GRAPHIC_LABELS);

    // Movement Indicator of Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::MOVEMENT_INDICATOR);
    // End of enable / disable selected map overlays 

    // Set the colors for the supported tactical standard identities
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_PENDING, 255, 0, 255, 255);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_UNKNOWN, 255, 255, 0, 255);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_ASSUMED_FRIEND, 0, 128, 255, 255);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_FRIEND, 0, 0, 255, 255);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_NEUTRAL, 0, 255, 0, 255);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_SUSPECT, 128, 255, 0, 255);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_HOSTILE, 255, 0, 0, 255);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_EXCERCISE_PENDING, 255, 0, 255, 128);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_EXCERCISE_UNKNOWN, 255, 255, 0, 128);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_EXCERCISE_ASSUMED_FRIEND, 0, 128, 255, 128);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_EXCERCISE_FRIEND, 0, 0, 255, 128);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_EXCERCISE_NEUTRAL, 0, 255, 0, 128);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_JOKER, 255, 255, 128, 255);
    FS_Comm::SendMsg_OverlayColors(0, FS_Constants::COLOR_TACTICAL_FAKER, 255, 0, 0, 255);


}

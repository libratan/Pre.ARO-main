// This file uses the symbols config in XML.  Might be removed in future implementation.
// Use MapTactical.cpp functions to set and update symbols in real time.

#include <../DMM/header/FS_Comm.h>
#include <../DMM/header/FS_Constants.h>
#include <../DMM/header/MapSymbols.h>

static int en_Symbols = 0;

void MapSymbols::SetMapSymbols()
{
    int nChannel = 0;

    if (en_Symbols == 1)
    {
        // Symbols are enabled, set to disable
        en_Symbols = 0;
    }
    else
    {
        // Symbols are disabled, set to enable
        en_Symbols = 1;
    }

    // Enable / disable selected map symbols overlays 
    // Global enable/disable for MIL STD 2525 Symbols
    // This overlay setting affects both symbols and graphics.  If any of the layer needs to be enabled this must be enabled.
    // Disabling this overlay disables all tactical symbols and graphics overlays.
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::TACTICAL_SYMBOLS);

    // Different Standard ID Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::AFFILIATION_FRIEND);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::AFFILIATION_NEUTRAL);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::AFFILIATION_HOSTILE);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::AFFILIATION_UNKNOWN);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::AFFILIATION_EXCERCISE);

    // Different Dimension Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::DIMENSION_UNKNOWN);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::DIMENSION_SPACE);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::DIMENSION_AIR);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::DIMENSION_GROUND);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::DIMENSION_SEA_SURFACE);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::DIMENSION_SUB_SURFACE);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::DIMENSION_SOF);

    // Frame, Fill, and Icon modifiers for Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::FILL_MODIFIER);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::ICON_MODIFIER);
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::FRAME_MODIFIER);

    // Tactical Symbol Text Modifier
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::TACTICAL_LABEL);

    // Movement Indicator of Tactical Symbols
    FS_Comm::SendMsg_OverlaySelect(nChannel, en_Symbols, FS_Constants::MOVEMENT_INDICATOR);

}
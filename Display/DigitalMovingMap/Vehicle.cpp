#include "FS_Comm.h"
#include "Vehicle.h"
#include "FS_Constants.h"

// For testing
//#include "TestFiles.h"
#include "Test_Constants.h"

// Static variables
static int s_nOwnshipIconIndex = 0;
static int s_nToggleCompassFlag = 0;
static int s_nToggleNorthUp = 0;
static int nChannel = 0;

// Static Icon Filepath Array - to explore how to set this from XML
static char s_arOwnshipIconsFilepaths[][FS_Constants::MAX_FILENAME_LENGTH] = {
    "#DEVICE0/ICON/ownship.png",
    "#DEVICE0/ICON/UAV2.ico",
    "#DEVICE0/ICON/ownship.ico",
    "SFAPMHA--------" }; // Tactical Symbol Code

void Vehicle::SetOwnshipVehicle(double lat, double lon, double heading)
{
    int nChannel = 0;
    
    // Enable vehicle overlay
    FS_Comm::SendMsg_OverlaySelect(nChannel, 1, FS_Constants::VEHICLE_SYMBOL);

    // Enable vehicle symbol 
    FS_Comm::SendMsg_VehicleEnables(nChannel, FS_Constants::VEHICLE_1, FS_Constants::SENSOR_1, 1, FS_Constants::ENABLE_VEHICLE);

    // Set icon/symbol to display for Ownship
    FS_Comm::SendMsg_VehicleIcon(nChannel, FS_Constants::VEHICLE_1, 0, s_arOwnshipIconsFilepaths[s_nOwnshipIconIndex]);

    FS_Comm::SendMsg_FlightDynamics(FS_Constants::VEHICLE_1, // Ownship Index
                                    3, // Number of Parameters
                                    FS_Constants::LATITUDE, lat, // Lat Parameter Code and Value  
                                    FS_Constants::LONGITUDE, lon, // Lon Parameter Code and Value
                                    FS_Constants::HEADING, heading); // Heading Parameter Code and Value 

}

void Vehicle::UpdateOwnship(double lat, double lon, double heading)
{
    FS_Comm::SendMsg_FlightDynamics(FS_Constants::VEHICLE_1, // Ownship Index
                                    3, // Number of Parameters
                                    FS_Constants::LATITUDE, lat, // Lat Parameter Code and Value  
                                    FS_Constants::LONGITUDE, lon, // Lon Parameter Code and Value  
                                    FS_Constants::HEADING, heading); // Heading Parameter Code and Value 
}
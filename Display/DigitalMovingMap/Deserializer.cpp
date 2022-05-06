#include "Deserializer.h"
#include "FS_Comm.h"
#include <stdio.h>

using namespace ICD;

void Deserializer::processMessage(char* pMessage, int msglen)
{
    // Declare message header struct to save new message
    ICD_header msgHeader;
    const int maxbuffersize = 1024;

    char pHeader[20];
    char pData[maxbuffersize];

    memset(pHeader, 0, 20);
    memset(pData, 0, maxbuffersize);

    // Check size of pMessage
    if (msglen >= sizeof(ICD_header))
    {
        // Message contains at least header size
        // Continue with message processing

        // Split pMessage to pHeader and pData
        memcpy(&pHeader, &pMessage[0], sizeof(ICD_header));
        memcpy(&pData, &pMessage[sizeof(ICD_header)], (msglen - (sizeof(ICD_header))));
        
        // For testing and debugging
        printf("Size of pMessage is %lu.\n", msglen);
        
        // Get msg header
        msgHeader = getMsgHeader(pHeader);

        // Decode message based on message ID
        switch (msgHeader.msg_id)
        {
        case FS_Constants::MSG_FLIGHT_DYNAMICS:
            update_FlightDynamics(pData);
            break;
        case FS_Constants::MSG_TACTICAL_GRAPHIC:
            update_TacticalGraphic(pData);
            break;
        default:
            // Msg ID not valid
            break;
        }
    }
    else
    {
        // Message contains less than header, discard.
    }
}

ICD_header Deserializer::getMsgHeader(char* pHeader)
{
    ICD_header msgHeader;
    memcpy((void*)&msgHeader.msg_id, &pHeader[0], sizeof(int));

    return msgHeader;
}

void Deserializer::update_TacticalGraphic(char* pData)
{
    TacticalGraphicMsg msg;
    msg.set_msgid(FS_Constants::MSG_TACTICAL_GRAPHIC);
    msg.decode_msg(pData);
    msg.send_update();

}

void Deserializer::update_FlightDynamics(ICD_FlightDynamics vehicle)
{
    const int vehIndex = vehicle.veh_index();

    if (vehicle.positionValid())
    {
        // Send lat and lon to FliteScene
        FS_Comm::SendMsg_FlightDynamics(vehIndex, 2, FS_Constants::LATITUDE, vehicle.lat(), FS_Constants::LONGITUDE, vehicle.lon());
    }
    else
    {
        // Position values are invalid.
    }

    if (vehicle.headingValid())
    {
        FS_Comm::SendMsg_FlightDynamics(vehIndex, 1, FS_Constants::HEADING, vehicle.heading());
    }
    else
    {
        // Heading value is invalid.
    }

    if (vehicle.attitudeValid())
    {
        FS_Comm::SendMsg_FlightDynamics(vehIndex, 2, FS_Constants::PITCH, vehicle.pitch(), FS_Constants::ROLL, vehicle.roll());
    }
    else
    {
        // Pitch and roll values are out of range
    }

    if (vehicle.mag_yawValid())
    {
        FS_Comm::SendMsg_FlightDynamics(vehIndex, 1, FS_Constants::MAG_YAW, vehicle.mag_yaw());
    }
    else
    {
        // Yaw value is out of range
    }

    if (vehicle.velocity_valid())
    {
        FS_Comm::SendMsg_FlightDynamics(vehIndex, 1, FS_Constants::VELOCITY, vehicle.velocity());
    }
    else
    {
        // Velocity value is not valid.
    }
}
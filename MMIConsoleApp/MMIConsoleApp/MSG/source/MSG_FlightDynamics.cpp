//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: FlightDynamicsMsg.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// entry point for FlightDynamicsMsg
//
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../MSG/header/MSG_FlightDynamics.h>
#include <../DMM/header/FS_Comm.h>

// Default Destructor
FlightDynamicsMsg::~FlightDynamicsMsg()
{
}

//****************************************************************************
//* Function Name  : bool positionValid()
//* Purpose        : Returns true if position is valid. Otherwise, return false. 
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
bool FlightDynamicsMsg::positionValid()
{
    bool result = false; // return variable

    // Check range validity of each field
    if (message.position_valid == true)
    {
        // Group 1 parameters (refer to FliteScene documentation on Flight Dynamics)
        if ((message.lat >= m_min_lat) && (message.lat <= m_max_lat) &&
            (message.lon >= m_min_long) && (message.lon <= m_max_long))
        {
            result = true;
        }
    }

    return result;
}

//****************************************************************************
//* Function Name  : bool headingValid()
//* Purpose        : Returns true if heading is valid. Otherwise, return false. 
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
bool FlightDynamicsMsg::headingValid()
{
    bool result = false; // return variable

    if (message.heading_valid == true)
    {
        if ((message.heading >= m_min_heading) && (message.heading <= m_max_heading))
        {
            result = true;
        }
    }

    return result;
}

//****************************************************************************
//* Function Name  : bool attitudeValid()
//* Purpose        : Returns true if attitude is valid. Otherwise, return false. 
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
bool FlightDynamicsMsg::attitudeValid()
{
    bool result = false; // return variable

    if (message.attitude_valid == true)
    {
        // Group 2 parameters (refer to FliteScene documentation on Flight Dynamics)
        if ((message.pitch >= m_min_pitch) && (message.pitch <= m_max_pitch) &&
            (message.roll >= m_min_roll) && (message.roll <= m_max_roll))
        {
            result = true;
        }
    }

    return result;
}

//****************************************************************************
//* Function Name  : bool mag_yawValid()
//* Purpose        : Returns true if magnetic yaw is valid. Otherwise, return false. 
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
bool FlightDynamicsMsg::mag_yawValid()
{
    bool result = false; // return variable

    if (message.attitude_valid == true)
    {
        const INT16 two = 2; // constant 2

        if ((message.mag_yaw >= 0.0) && (message.mag_yaw <= (two * m_pi)))
        {
            result = true;
        }
    }

    return result;
}

//****************************************************************************
//* Function Name  : bool velocity_valid()
//* Purpose        : Returns true if velocity is valid. Otherwise, return false. 
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
bool FlightDynamicsMsg::velocity_valid()
{
    bool result = false; // return variable
        
    if (message.velocity_valid == true)
    {
        result = true;
    }

    return result;
}


void FlightDynamicsMsg::decode_msg(char* pData)
{
    INT32 ptr = 0; // indexing ptr
    memcpy(&message.veh_index, &pData[0], sizeof(INT32));
    ptr = ptr + sizeof(INT32);
    memcpy(&message.position_valid, &pData[ptr], sizeof(bool));
    ptr = ptr + sizeof(bool);
    memcpy(&message.lat, &pData[ptr], sizeof(FLOAT64));
    ptr = ptr + sizeof(FLOAT64);
    memcpy(&message.lon, &pData[ptr], sizeof(FLOAT64));
    ptr = ptr + sizeof(FLOAT64);
    memcpy(&message.heading_valid, &pData[ptr], sizeof(bool));
    ptr = ptr + sizeof(bool);
    memcpy(&message.heading, &pData[ptr], sizeof(FLOAT64));
    ptr = ptr + sizeof(FLOAT64);
    memcpy(&message.attitude_valid, &pData[ptr], sizeof(bool));
    ptr = ptr + sizeof(bool);
    memcpy(&message.pitch, &pData[ptr], sizeof(FLOAT64));
    ptr = ptr + sizeof(FLOAT64);
    memcpy(&message.roll, &pData[ptr], sizeof(FLOAT64));
    ptr = ptr + sizeof(FLOAT64);
    memcpy(&message.mag_yaw, &pData[ptr], sizeof(FLOAT64));
    ptr = ptr + sizeof(FLOAT64);
    memcpy(&message.altitude_valid, &pData[ptr], sizeof(bool));
    ptr = ptr + sizeof(bool);
    memcpy(&message.altitude, &pData[ptr], sizeof(INT32));
    ptr = ptr + sizeof(INT32);
    memcpy(&message.velocity_valid, &pData[ptr], sizeof(bool));
    ptr = ptr + sizeof(bool);
    memcpy(&message.velocity, &pData[ptr], sizeof(FLOAT64));
}

void FlightDynamicsMsg::send_update()
{
    if (positionValid())
    {
        // Send lat and lon to FliteScene
        FS_Comm::SendMsg_FlightDynamics(veh_index(), 2, FS_Constants::LATITUDE, lat(),
            FS_Constants::LONGITUDE, lon());
    }
    else
    {
        // Position values are invalid.
    }

    if (headingValid())
    {
        FS_Comm::SendMsg_FlightDynamics(veh_index(), 1, FS_Constants::HEADING, heading());
    }
    else
    {
        // Heading value is invalid.
    }

    if (attitudeValid())
    {
        FS_Comm::SendMsg_FlightDynamics(veh_index(), 2, FS_Constants::PITCH, pitch(),
            FS_Constants::ROLL, roll());
    }
    else
    {
        // Pitch and roll values are out of range
    }

    if (mag_yawValid())
    {
        FS_Comm::SendMsg_FlightDynamics(veh_index(), 1, FS_Constants::MAG_YAW, mag_yaw());
    }
    else
    {
        // Yaw value is out of range
    }

    if (velocity_valid())
    {
        FS_Comm::SendMsg_FlightDynamics(veh_index(), 1, FS_Constants::VELOCITY, velocity());
    }
    else
    {
        // Velocity value is not valid.
    }
}


INT32 FlightDynamicsMsg::veh_index()
{
    return message.veh_index;
}

inline FLOAT64 FlightDynamicsMsg::lat()
{
    return message.lat;
}

inline FLOAT64 FlightDynamicsMsg::lon()
{
    return message.lon;
}

inline FLOAT64 FlightDynamicsMsg::heading()
{
    return message.heading;
}

inline FLOAT64 FlightDynamicsMsg::pitch()
{
    return message.pitch;
}

inline FLOAT64 FlightDynamicsMsg::roll()
{
    return message.roll;
}

inline FLOAT64 FlightDynamicsMsg::mag_yaw()
{
    return message.mag_yaw;
}

inline INT32 FlightDynamicsMsg::altitude()
{
    return message.altitude;
}

inline FLOAT64 FlightDynamicsMsg::velocity()
{
    return message.velocity;
}
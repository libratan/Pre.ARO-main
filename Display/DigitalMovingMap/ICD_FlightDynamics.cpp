#include "ICD_FlightDynamics.h"

bool ICD_FlightDynamics::positionValid()
{
    // Check range validity of each field
    if (message.position_valid == true)
    {
        // Group 1 parameters (refer to FliteScene documentation on Flight Dynamics)
        if ((message.lat >= -90.0) && (message.lat <= 90.0) &&
            (message.lon >= -180.0) && (message.lon <= 180.0))
        {
            return true;
        }
    }
    return false;
}

bool ICD_FlightDynamics::headingValid()
{
    if (message.heading_valid == true)
    {
        if (message.heading >= 0.0 && message.heading <= 360.0)
        {
            return true;
        }
    }
    return false;
}

bool ICD_FlightDynamics::attitudeValid()
{
    if (message.attitude_valid == true)
    {
        // Group 2 parameters (refer to FliteScene documentation on Flight Dynamics)
        if ((message.pitch >= -90.0 && message.pitch <= 90.0) &&
            (message.roll >= -180.0 && message.roll <= 180.0))
        {
            return true;
        }
    }
    return false;
}

bool ICD_FlightDynamics::mag_yawValid()
{
    const double m_PI = 3.14159;

    if (message.attitude_valid == true) 
    {
        if (message.mag_yaw >= 0.0 && message.mag_yaw <= (2 * m_PI))
        {
            return true;
        }
    }
    return false;
}

bool ICD_FlightDynamics::velocity_valid() 
{
    if (message.velocity_valid == true)
    {
        return true;
    }
    return false;
}
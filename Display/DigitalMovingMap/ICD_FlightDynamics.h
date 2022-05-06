#pragma once
#include <string>
#include "icd.h"
using namespace ICD;

class ICD_FlightDynamics
{

private:

    FlightDynamics message;

public:
    ICD_FlightDynamics() 
    {
        message.veh_index = 0;
        message.position_valid = true;
        message.lat = 0.0F;
        message.lon = 0.0F;
        message.heading_valid = true;
        message.heading = 0.0F;
        message.attitude_valid = true;
        message.pitch = 0.0F;
        message.roll = 0.0F;
        message.mag_yaw = 0.0F;
        message.altitude_valid = true;
        message.altitude = 0;
        message.velocity_valid = true;
        message.velocity = 0.0F;
    };

    ICD_FlightDynamics(char* pData) 
    {
        int ptr = 0;
        memcpy(&message.veh_index, &pData[0], sizeof(int));
        ptr = ptr + sizeof(int);
        memcpy(&message.position_valid, &pData[ptr], sizeof(bool));
        ptr = ptr + sizeof(bool);
        memcpy(&message.lat, &pData[ptr], sizeof(double));
        ptr = ptr + sizeof(double);
        memcpy(&message.lon, &pData[ptr], sizeof(double));
        ptr = ptr + sizeof(double);
        memcpy(&message.heading_valid, &pData[ptr], sizeof(bool));
        ptr = ptr + sizeof(bool);
        memcpy(&message.heading, &pData[ptr], sizeof(double));
        ptr = ptr + sizeof(double);
        memcpy(&message.attitude_valid, &pData[ptr], sizeof(bool));
        ptr = ptr + sizeof(bool);
        memcpy(&message.pitch, &pData[ptr], sizeof(double));
        ptr = ptr + sizeof(double);
        memcpy(&message.roll, &pData[ptr], sizeof(double));
        ptr = ptr + sizeof(double);
        memcpy(&message.mag_yaw, &pData[ptr], sizeof(double));
        ptr = ptr + sizeof(double);
        memcpy(&message.altitude_valid, &pData[ptr], sizeof(bool));
        ptr = ptr + sizeof(bool);
        memcpy(&message.altitude, &pData[ptr], sizeof(int));
        ptr = ptr + sizeof(int);
        memcpy(&message.velocity_valid, &pData[ptr], sizeof(bool));
        ptr = ptr + sizeof(bool);
        memcpy(&message.velocity, &pData[ptr], sizeof(double));
    };

    ~ICD_FlightDynamics()
    {
    }

    int veh_index() { return message.veh_index; };
    double lat() { return message.lat; };
    double lon() { return message.lon; };
    double heading() { return message.heading; };
    double pitch() { return message.pitch; };
    double roll() { return message.roll; };
    double mag_yaw() { return message.mag_yaw; };
    int altitude() { return message.altitude; };
    double velocity() { return message.velocity; };

    bool positionValid();
    bool headingValid();
    bool attitudeValid();
    bool mag_yawValid();
    bool velocity_valid();
};

//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: icd.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// This file contains ICD definitions
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef ICD_H
#define ICD_H

#pragma once
#pragma pack(4)
#include <../Common/gen_type.h>

using namespace std;

namespace ICD
{
    struct ICD_header
    {
        INT32 msg_id; //Message ID
    };

    struct FlightDynamics
    {
        INT32       veh_index;      //veh_index;
        BOOL        position_valid; //position_valid;
        FLOAT64     lat;            //lat;
        FLOAT64     lon;            //lon;
        BOOL        heading_valid;  //heading_valid;
        FLOAT64     heading;        //heading;
        BOOL        attitude_valid; //attitude_valid;
        FLOAT64     pitch;          //pitch;
        FLOAT64     roll;           //roll;
        FLOAT64     mag_yaw;        //mag_yaw;
        BOOL        altitude_valid; //altitude_valid;
        INT32       altitude;       //altitude;
        BOOL        velocity_valid; //velocity_valid;
        FLOAT64     velocity;       //velocity;
    };

    struct TacticalGraphic
    {
        INT32       symbol_id;                   //symbol_id;
        CHAR        SIDC[16];                    //SIDC[16];
        INT32       modifier_count;              //modifier_count;
        INT32       point_count;                 //point_count;
        FLOAT64     latitude;                    //latitude;
        FLOAT64     longitude;                   //longitude;
        FLOAT64     altitude;                    //altitude;
        FLOAT64     magnification;               //magnification;
        FLOAT64     orientation;                 //orientation;
        INT32       direction_of_movement_en;    //direction_of_movement_en;
        FLOAT64     direction_of_movement_angle; //direction_of_movement_angle;
    };
}
#endif
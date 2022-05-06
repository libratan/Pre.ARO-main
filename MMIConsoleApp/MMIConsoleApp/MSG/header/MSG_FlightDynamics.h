//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: FlightDynamicsMsg.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for FlightDynamicsMsg
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef MSG_FLIGHTDYNAMICS_H
#define MSG_FLIGHTDYNAMICS_H

#include <../MSG/header/icd.h>
#include <../MSG/header/Message.h>
#include <../Common/gen_type.h>


class FlightDynamicsMsg : public Message
{

public:
    FlightDynamics message;
    
    // Default Constructor
    FlightDynamicsMsg() : Message(0, "")
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
    }
 
    // Default Destructor
    ~FlightDynamicsMsg();
    
    //****************************************************************************
    //* Function Name  : void decode_msg()
    //* Purpose        : Returns vehicle index 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void decode_msg(char* pData);

    //****************************************************************************
    //* Function Name  : void send_update()
    //* Purpose        : Returns vehicle index 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void send_update(void);

private:
    //****************************************************************************
    //* Function Name  : INT32 veh_index()
    //* Purpose        : Returns vehicle index 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    INT32 veh_index();

    //****************************************************************************
    //* Function Name  : FLOAT64 lat()
    //* Purpose        : Returns latitude 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    FLOAT64 lat();

    //****************************************************************************
    //* Function Name  : FLOAT64 lon()
    //* Purpose        : Returns longitude 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    FLOAT64 lon();

    //****************************************************************************
    //* Function Name  : FLOAT64 heading()
    //* Purpose        : Returns heading 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    FLOAT64 heading();

    //****************************************************************************
    //* Function Name  : FLOAT64 pitch()
    //* Purpose        : Returns pitch 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    FLOAT64 pitch();

    //****************************************************************************
    //* Function Name  : FLOAT64 roll()
    //* Purpose        : Returns roll 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    FLOAT64 roll();

    //****************************************************************************
    //* Function Name  : FLOAT64 mag_yaw()
    //* Purpose        : Returns mag_yaw 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    FLOAT64 mag_yaw();

    //****************************************************************************
    //* Function Name  : INT32 altitude()
    //* Purpose        : Returns altitude 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    INT32 altitude();

    //****************************************************************************
    //* Function Name  : FLOAT64 velocity()
    //* Purpose        : Returns velocity 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    FLOAT64 velocity();

    //****************************************************************************
    //* Function Name  : bool positionValid()
    //* Purpose        : Returns true if position is valid. Otherwise, return false. 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    bool positionValid();

    //****************************************************************************
    //* Function Name  : bool headingValid()
    //* Purpose        : Returns true if heading is valid. Otherwise, return false. 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    bool headingValid();

    //****************************************************************************
    //* Function Name  : bool attitudeValid()
    //* Purpose        : Returns true if attitude is valid. Otherwise, return false. 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    bool attitudeValid();

    //****************************************************************************
    //* Function Name  : bool mag_yawValid()
    //* Purpose        : Returns true if magnetic yaw is valid. Otherwise, return false. 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    bool mag_yawValid();

    //****************************************************************************
    //* Function Name  : bool velocity_valid()
    //* Purpose        : Returns true if velocity is valid. Otherwise, return false. 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    bool velocity_valid();

};


#endif // !FLIGHTDYNAMICSMSG_H
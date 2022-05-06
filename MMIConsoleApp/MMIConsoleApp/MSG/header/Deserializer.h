//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Deserializer.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for Deserializer
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <../MSG/header/MSG_FlightDynamics.h>
#include <../MSG/header/MSG_TacticalGraphic.h>

using namespace ICD;

class Deserializer
{
public:
    
    //*This enum to hold relevant constants
    enum DESERIALIZER_CONSTANTS
    {
        header_size = 20,                   // header size 
        data_buffer_size = 1024             // buffer data size 
    };

    //****************************************************************************
    //* Function Name  : Deserializer()
    //* Purpose        : Constructor
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    Deserializer();

    //****************************************************************************
    //* Function Name  : ~Deserializer()
    //* Purpose        : Destructor 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    ~Deserializer();

    //****************************************************************************
    //* Function Name  : void processMessage(const CHAR* pMessage, INT32 msglen)
    //* Purpose        : Process Message that was received
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    //JSF rule disallow passing of array for void processMessage(const CHAR* pMessage, INT32 msglen);
    void processMessage(const CHAR (&pMessage)[data_buffer_size], UINT32 msglen);

private:
    static const INT32 maxbuffersize = 1024;   // maximum buffer size
    static const INT32 headersize = 20;        // msg header size

    //****************************************************************************
    //* Function Name  : ICD_header getMsgHeader()
    //* Purpose        : Get message header 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    ICD_header getMsgHeader(char* pHeader);   

    //****************************************************************************
    //* Function Name  : void update_TacticalGraphic(char* pData)
    //* Purpose        : Update Tactical Graphic Message
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    void update_TacticalGraphic(char* pData);

    //****************************************************************************
    //* Function Name  : void update_FlightDynamics(char* pData)
    //* Purpose        : Update Flight Dynamics Message
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Private
    //* Note           :
    //****************************************************************************
    void update_FlightDynamics(char* pData);

};

#endif // !DESERIALIZER_H
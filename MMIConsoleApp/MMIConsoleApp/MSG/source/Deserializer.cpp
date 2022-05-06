//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: DigitalMovingMap.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// entry point for digital map display
//
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../MSG/header/Deserializer.h>
#include <../DMM/header/LogClient.h>
#include <../DMM/header/FS_Constants.h>

using namespace ICD;

//****************************************************************************
//* Function Name  : Deserializer()
//* Purpose        : Constructor
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
Deserializer::Deserializer()
{
}

//****************************************************************************
//* Function Name  : ~Deserializer()
//* Purpose        : Destructor 
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
Deserializer::~Deserializer()
{
}

//****************************************************************************
//* Function Name  : void processMessage(const CHAR* pMessage, INT32 msglen)
//* Purpose        : Process Message that was received
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void Deserializer::processMessage(const CHAR(&pMessage)[data_buffer_size], UINT32 msglen)
{
    LogClient* logClient = LogClient::getInstance();
    char pHeader[headersize];           // pointer to message header
    char pData[maxbuffersize];          // pointer to message data
    
    memset(pHeader, 0, headersize);
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
        string s("Data Received at Deserializer");
        logClient->writeLog(s.c_str());
        
        // Get msg header
          // Declare message header struct to save new message
        ICD_header msgHeader;
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

//****************************************************************************
//* Function Name  : ICD_header getMsgHeader()
//* Purpose        : Get message header 
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Private
//* Note           :
//****************************************************************************
ICD_header Deserializer::getMsgHeader(char* pHeader)
{
    ICD_header msgHeader;       // ICD message header
    memcpy((void*)&msgHeader.msg_id, &pHeader[0], sizeof(INT32));

    return msgHeader;
}

//****************************************************************************
//* Function Name  : void update_TacticalGraphic(char* pData)
//* Purpose        : Update Tactical Graphic Message
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Private
//* Note           :
//****************************************************************************
void Deserializer::update_TacticalGraphic(char* pData)
{
    TacticalGraphicMsg msg;     // msg data
    msg.set_msgid(FS_Constants::MSG_TACTICAL_GRAPHIC);
    msg.decode_msg(pData);
    msg.send_update();
}

//****************************************************************************
//* Function Name  : void update_FlightDynamics(char* pData)
//* Purpose        : Update Flight Dynamics Message
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Private
//* Note           :
//****************************************************************************
void Deserializer::update_FlightDynamics(char* pData)
{
    FlightDynamicsMsg msg; //msg data
    msg.set_msgid(FS_Constants::MSG_FLIGHT_DYNAMICS);
    msg.decode_msg(pData);
    msg.send_update();
}
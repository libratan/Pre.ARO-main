//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Message.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for Message
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef MESSAGE_H
#define MESSAGE_H

#pragma once
#include <../MSG/header/icd.h>
#include <../Common/gen_type.h>
#include <string>

using namespace ICD;
using namespace std;

class Message
{
private:
    string timestamp;
    INT32 msg_id;

public:
    string get_timestamp(void) { return timestamp; };
    INT32 get_msgid(void) { return msg_id; };

    void set_timestamp(string time) { timestamp = time; };
    void set_msgid(INT32 id) { msg_id = id; };

    virtual void decode_msg(CHAR* pData) = 0;
    virtual void send_update(void) = 0;

protected:
    Message(INT32 id, string time)
    {
        timestamp = time;
        msg_id = id;
    }
};


#endif
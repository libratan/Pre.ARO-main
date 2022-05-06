#pragma once
#include "ICD_FlightDynamics.h"
#include "Message.h"

using namespace ICD;

class Deserializer
{
public:
    Deserializer()
    {
    }

    ~Deserializer()
    {
    }

    void processMessage(char* pMessage, int msglen);

private:

    const int bits2bytes = 4;

    ICD_header getMsgHeader(char* pHeader);
    void update_TacticalGraphic(char* pData);
    void update_FlightDynamics(ICD_FlightDynamics vehicle);

};


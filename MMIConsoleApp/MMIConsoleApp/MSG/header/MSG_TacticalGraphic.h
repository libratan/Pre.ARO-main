#ifndef MSG_TACTICALGRAPHIC_H
#define MSG_TACTICALGRAPHIC_H

#include <../MSG/header/icd.h>
#include <../MSG/header/Message.h>

#pragma once
class TacticalGraphicMsg : public Message
{
public:
    TacticalGraphic message;

    TacticalGraphicMsg() : Message(0, "")
    {
        message.symbol_id = 0;
        memset(message.SIDC, 0, 16);
        message.modifier_count = 0;
        message.point_count = 0;
        message.latitude = 0.0F;
        message.longitude = 0.0F;
        message.altitude = 0.0F;
        message.magnification = 0.0F;
        message.orientation = 0.0F;
        message.direction_of_movement_en = 0;
        message.direction_of_movement_angle = 0.0F;
    }

    ~TacticalGraphicMsg()
    {
    }

    void decode_msg(char* pData);
    void send_update(void);

    struct TacticalGraphicModifiers
    {
        INT32 modifier_code;
        char modifier_test[36];
    };

    struct TacticalGraphicPoints
    {
        FLOAT64 lat;
        FLOAT64 lon;
        FLOAT64 altitude;
    };

private:
    INT32 check_FSUID(void);
    void update_DB_timestamp(void);

    bool modcount_valid(void);
    bool pointcount_valid(void);
    bool latitude_valid(void);
    bool longitude_valid(void);
    bool altitude_valid(void);
    bool orientation_valid(void);
    bool dirofmovement_en_valid(void);
    bool dirofmovement_angle_valid(void);
};

#endif
#pragma once
#include "icd.h"
#include "FS_Comm.h"
#include <stdio.h>
#include <string>

using namespace ICD;
using namespace std;

class Message
{
private:
    string timestamp;
    int msg_id;

public:
    string get_timestamp(void) { return timestamp; };
    int get_msgid(void) { return msg_id; };

    void set_timestamp(string time) { timestamp = time; };
    void set_msgid(int id) { msg_id = id; };

    virtual void decode_msg(char* pData) = 0;
    virtual void send_update(void) = 0;

protected:
    Message(int id, string time)
    {
        timestamp = time;
        msg_id = id;
    }
};

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
        int modifier_code;
        char modifier_test[36];
    };

    struct TacticalGraphicPoints
    {
        double lat;
        double lon;
        double altitude;
    };

private:
    int check_FSUID(void);
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


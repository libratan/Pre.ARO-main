#include <../MSG/header/MSG_TacticalGraphic.h>
#include <../DMM/header/SymbolDB.h>
#include <../DMM/header/FS_Comm.h>
#include <string>
using namespace std;

void TacticalGraphicMsg::decode_msg(char* pData)
{
    int ptr = 0;
    memcpy(&message.symbol_id, &pData[ptr], sizeof(int));
    ptr = ptr + sizeof(int);
    memcpy(&message.SIDC, &pData[ptr], 16);
    ptr = ptr + 16;
    memcpy(&message.modifier_count, &pData[ptr], sizeof(int));
    ptr = ptr + sizeof(int);
    memcpy(&message.point_count, &pData[ptr], sizeof(int));
    ptr = ptr + sizeof(int);
    memcpy(&message.latitude, &pData[ptr], sizeof(double));
    ptr = ptr + sizeof(double);
    memcpy(&message.longitude, &pData[ptr], sizeof(double));
    ptr = ptr + sizeof(double);
    memcpy(&message.altitude, &pData[ptr], sizeof(double));
    ptr = ptr + sizeof(double);
    memcpy(&message.magnification, &pData[ptr], sizeof(double));
    ptr = ptr + sizeof(double);
    memcpy(&message.orientation, &pData[ptr], sizeof(double));
    ptr = ptr + sizeof(double);
    memcpy(&message.direction_of_movement_en, &pData[ptr], sizeof(int));
    ptr = ptr + sizeof(int);
    memcpy(&message.direction_of_movement_angle, &pData[ptr], sizeof(double));

}

void TacticalGraphicMsg::send_update()
{
    if (modcount_valid() &&
        pointcount_valid() &&
        latitude_valid() &&
        longitude_valid() &&
        altitude_valid() &&
        orientation_valid() &&
        dirofmovement_en_valid() &&
        dirofmovement_angle_valid())
    {

        update_DB_timestamp(); // Save to sym_map DB

        TacticalGraphicModifiers TacticalModifiers[1];
        TacticalGraphicPoints TacticalGraphicPoints[1];

        TacticalGraphicPoints[0].lat = message.latitude;
        TacticalGraphicPoints[0].lon = message.longitude;
        TacticalGraphicPoints[0].altitude = message.altitude;


        FS_Comm::SendMsg_SetTacticalGraphic(
            check_FSUID(),
            message.symbol_id, 
            message.SIDC, 
            message.modifier_count, 
            reinterpret_cast<char*>(&TacticalModifiers), 
            message.point_count, 
            reinterpret_cast<char*>(&TacticalGraphicPoints), 
            message.magnification, 
            message.orientation, 
            message.direction_of_movement_en, 
            message.direction_of_movement_angle);

        printf("Symbol %d update sent to FS.\n", message.symbol_id);
    }
}

void TacticalGraphicMsg::update_DB_timestamp()
{
    if (check_FSUID() < 0)
    {
        // Symbol is new, does not exist in DB yet.
        int x = -1;
        string y = this->get_timestamp();
        SymbolDB::add_Symbol(message.symbol_id, x, y);
    }
    else
    {
        // Symbol exists in DB, update last_update
        SymbolDB::update_SymbolTime(message.symbol_id, this->get_timestamp());
    }
}

int TacticalGraphicMsg::check_FSUID()
{
    return SymbolDB::get_FSUID(message.symbol_id);
}

bool TacticalGraphicMsg::modcount_valid(void)
{
    // modifier_count should be 0
    if (message.modifier_count == 0)
    {
        return true;
    }

    return false;
}

bool TacticalGraphicMsg::pointcount_valid(void)
{
    // point_count should be 1
    if (message.point_count == 1)
    {
        return true;
    }

    return false;
}

bool TacticalGraphicMsg::latitude_valid(void)
{
    if (message.latitude >= -80.0 && message.latitude <= 80.0)
    {
        return true;
    }

    return false;
}

bool TacticalGraphicMsg::longitude_valid(void)
{
    if (message.longitude >= -180.0 && message.longitude <= 180.0)
    {
        return true;
    }

    return false;
}

bool TacticalGraphicMsg::altitude_valid(void)
{
    if (message.altitude >= -16384.0 && message.altitude <= 32767.0)
    {
        return true;
    }

    return false;
}

bool TacticalGraphicMsg::orientation_valid(void)
{
    if (message.orientation >= 0.0 && message.orientation <= 360.0)
    {
        return true;
    }

    return false;
}

bool TacticalGraphicMsg::dirofmovement_en_valid(void)
{
    if (message.direction_of_movement_en == 0 || message.direction_of_movement_en == 1)
    {
        return true;
    }

    return false;
}

bool TacticalGraphicMsg::dirofmovement_angle_valid(void)
{
    if (message.direction_of_movement_angle >= 0.0 && message.direction_of_movement_angle <= 360.0)
    {
        return true;
    }

    return false;
}
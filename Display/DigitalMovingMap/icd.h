#pragma once
#pragma pack(4)
#include <string>


using namespace std;

namespace ICD
{
    struct ICD_header
    {
        int msg_id;
    };

    struct FlightDynamics
    {
        int			veh_index;
        bool		position_valid;
        double		lat;
        double		lon;
        bool		heading_valid;
        double		heading;
        bool		attitude_valid;
        double		pitch;
        double		roll;
        double		mag_yaw;
        bool		altitude_valid;
        int			altitude;
        bool		velocity_valid;
        double		velocity;
    };

    struct TacticalGraphic
    {
        int		symbol_id;
        char	SIDC[16];
        int		modifier_count;
        int		point_count;
        double	latitude;
        double	longitude;
        double	altitude;
        double	magnification;
        double	orientation;
        int		direction_of_movement_en;
        double	direction_of_movement_angle;

    };
}
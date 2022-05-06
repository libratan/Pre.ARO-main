#pragma once
#include <sys/timeb.h>

class OwnshipTest
{
public:

    OwnshipTest(void);

    ~OwnshipTest(void)
    {

    }


    // This is a continual update via FlightDynamics to have a vehicle fly 
    // between two lat,lon points and two altitudes. 
    void UpdatePosition(void);


    // Static getter to get the Heading 
    // to calculate the Azimuth to set 3rd Person View in Perspective Mode.
    static double GetHeading(void);


private:
    // Constants
    const double POINT_LAT_ONE = 33.48;
    const double POINT_LON_ONE = -116.22;
    const double ALTITUDE_ONE = 1000.0;
    const double POINT_LAT_TWO = 38.68;
    const double POINT_LON_TWO = -114.68;
    const double ALTITUDE_TWO = 10000.0;
    const double NM_PER_DEGREE = 60.0;
    const double DEG_TO_RADIAN = 0.0174532925;
    const double HOUR_TO_SECONDS = 3600.0;

    // Flexible values  
    double m_dVelocity = 3000.0;
    double m_dAltitudeDelta = 5;

    // Flag values for checks.
    int m_nIsCeiling = 0; // Altitude 
    int m_nIsFencePostNS = 0; // Lat
    int m_nIsFencePostEW = 0; // Lon

    // time values 
    struct timeb struct_time;
    double m_dLastTimeStamp;
    double m_dLastMilliSeconds;

};


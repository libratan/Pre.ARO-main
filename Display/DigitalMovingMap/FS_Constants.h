//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Commercial Computer Software - Non-deliverable Source Code
// See FAR 52.227-19(c)
// The rights of the Government regarding use, reproduction and disclosure are
// as set forth in the applicable FliteScene contract.
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//  Copyright (C) Harris Corporation 2017 - All Rights Reserved
// *****************************************************************************
//  FILE:            FS_Constants.h
//
//  CLASSIFICATION:  Unclassified
//
//  DESCRIPTION:     Definitions for constants which are defined in the ICD.
//
//  LIMITATIONS:     none
//
//  SOFTWARE HISTORY:
//
//      See ClearCase (cleartool lshistory)
//
// *****************************************************************************
#if !defined(FS_CONSTANTS_H_HEADER_INCLUDED)
#define FS_CONSTANTS_H_HEADER_INCLUDED

#include <string.h>     // for memset()

//*****************************************************************************
// FS_Message: Base class for the FliteScene response messages definitions.
// The classes derived from this class are defined in the FS_Constants class to
// minimize the global namespace.  However, this class was defined outside of
// the FS_Constants class to prevent FS_Comm.h from needing to include this file
// due to FS_Comm.h being included in the BezelKeyDLL.cpp file.  This is because
// some of the enumeration values clash with MicroSoft's headers.
//
//*****************************************************************************
class FS_Message
{
public:     // Constructors and Destructors
    FS_Message() : m_nEndian(0), m_nSize(0), m_nChannel(0), m_nId(0), m_nVersion(0), m_nUpdated(0) { }
    virtual ~FS_Message() {}

public:     // Member Functions
    virtual void Swap();

public:     // Class Data
    int m_nEndian;
    int m_nSize;
    int m_nChannel;
    int m_nId;
    int m_nVersion;
    int m_nUpdated;
};

//##Documentation
//## **************************************************************************
//## CLASS FS_Constants
//## **************************************************************************
class FS_Constants
{
public:

    //##Documentation
    //## Enumeration of the FliteScene message numbers as defined by the ICD.
    //## See Doc# 8015395.
    enum FLITESCENE_MSG_IDS
    {
        MSG_VIEWPORT                        = 3,
        MSG_TIVALTITUDETABLE                = 4,
        MSG_EBALTITUDETABLE                 = 5,
        MSG_MODE                            = 6,
        MSG_FLIGHT_DYNAMICS                 = 7,
        MSG_ZOOM                            = 8,
        MSG_DECENTER                        = 9,
        MSG_DATA_FRAME_CONTROL              = 10,
        MSG_OVERLAY_SELECT                  = 11,
        MSG_OVERLAY_COLORS                  = 12,
        MSG_SLOPE_SHADING_CONTROL           = 13,
        MSG_CONTOUR_LINE_CONTROL            = 14,
        MSG_ELEVATION_BANDS_CONTROL         = 15,
        MSG_THREAT                          = 16,
        MSG_GEO_CHIP                        = 17,
        MSG_GEO_QUERY                       = 18,
        MSG_GEO_RESPONSE                    = 19,
        MSG_GET_STATUS                      = 20,
        MSG_MAP_STATUS                      = 21,
        MSG_GET_VERSION_ID                  = 22,
        MSG_VERSION_ID                      = 23,
        MSG_TEST_DATA                       = 24,
        MSG_TEST_RESULTS                    = 25,
        MSG_REFRESH_CACHE                   = 26,
        MSG_SHUTDOWN                        = 27,
        MSG_SET_2525_SYMBOL                 = 30,
        MSG_VO_PARAMETERS                   = 31,
        MSG_CLOS_QUERY                      = 32,
        MSG_CLOS_RESULTS                    = 33,
        MSG_POI_QUERY                       = 34,
        MSG_POI_RESULTS                     = 35,
        MSG_TREND_DOTS                      = 36,
        MSG_SLEW                            = 37,
        MSG_CURSOR                          = 38,
        MSG_SCREEN_CAPTURE                  = 42,
        MSG_SCREEN_CAPTURE_RESULTS          = 43,
        MSG_SENSOR_CONTROL                  = 45,
        MSG_RASTER_CONTROL                  = 46,
        MSG_UNDERLAY_LEVEL_PRODUCT          = 47,
        MSG_UNDERLAY_SELECT                 = 48,
        MSG_THREAT_SELECT                   = 49,
        MSG_GEOCHIP_SELECT                  = 50,
        MSG_SET_GEO_SYMBOL                  = 52,
        MSG_SET_SCREEN_SYMBOL               = 53,
        MSG_SET_GEO_SYMBOL_SKIN             = 54,
        MSG_SET_SCREEN_SYMBOL_SKIN          = 55,
        MSG_ENABLE_GEO_SYMBOL               = 56,
        MSG_ENABLE_SCREEN_SYMBOL            = 57,
        MSG_ELEVATION_CONTROL               = 58,
        MSG_VEHICLE_ENABLES                 = 59,
        MSG_OWNSHIP_CONTROL                 = 61,
        MSG_RANGE_BEARING                   = 64,
        MSG_GRID_CONVERSION                 = 66,
        MSG_SET_ROUTE_WAYPOINT              = 68,
        MSG_SET_ROUTE_LEG                   = 69,
        MSG_LEG_PARAMETERS                  = 70,
        MSG_LEG_PERCENT_COMPLETE            = 71,
        MSG_ROUTE_SET_GROUP                 = 72,
        MSG_ROUTE_ENABLE_GROUP              = 73,
        MSG_PERSPECTIVE                     = 74,
        MSG_SET_FLIGHT_PLAN                 = 75,
        MSG_ELEVATION_PROFILE_CONTROL       = 82,
        MSG_VEHICLE_ICON                    = 83,
        MSG_ROUTE_LEG_GATE                  = 84,
        MSG_RACETRACK                       = 85,
        MSG_TEXTBOX_ENABLE                  = 88,
        MSG_TEXTBOX_SET_TEXT                = 89,
        MSG_TEXTBOX_INSERT_TEXT             = 90,
        MSG_TEXTBOX_SET_GEOMETRY            = 91,
        MSG_TEXTBOX_SET_ACTIVE              = 92,
        MSG_TEXTBOX_SET_REGION              = 93,
        MSG_TEXTBOX_GET_CONTENTS            = 94,
        MSG_TEXTBOX_RESPONSE                = 96,
        MSG_COMPASS_ROSE_CONTROL            = 97,
        MSG_COMPASS_ROSE_POINTER            = 98,
        MSG_COCKPIT_CAMERA                  = 99,
        MSG_CURSOR_SELECTION_RESPONSE       = 100,
        MSG_FLIGHT_PLAN_ENABLE              = 101,
        MSG_CURSOR_OBJECT_INFO              = 104,
        MSG_CURSOR_SELECTED_OBJECTS         = 105,
        MSG_VERTICAL_BANDS_PROCESSING       = 117,
		MSG_VERTICAL_BANDS_CONTROL			= 118,
        MSG_SET_OBJECT_RESPONSE				= 119,
        MSG_RANGE_BEARING_RESULTS           = 126,
        FLITESCENE_UID_RESPONSE             = 129,
        MSG_LANDING_ZONE                    = 135,
        MSG_DATAFRAME_RESPONSE              = 141,
        MSG_TACTICAL_GRAPHIC                = 145,
        MSG_DMS_CONVERSION                  = 150
    };

    enum ENABLE_CONSTANTS
    {
        DISABLE = 0,
        ENABLE  = 1
    };

    enum VIEWPORT_CONSTANTS
    {
        FRAME_BUFFER = 0,
        MAP_WINDOW   = 1
    };

    enum MODE_CONSTANTS
    {
        PLAN_VIEW        = 0,
        PERSPECTIVE_VIEW = 1,
        DATAFRAME_VIEW   = 2,
        BLANK_VIEW       = 3
    };

    enum FLIGHTDYNAMICS_CONSTANTS
    {
        LATITUDE   = 0,
        LONGITUDE  = 1,
        HEADING    = 2,
        PITCH      = 3,
        ROLL       = 4,
        ALTITUDE   = 8,
        VELOCITY   = 9,
        TURN_RATE  = 10,
        ALTITUDE_F = 15,
        MAG_YAW    = 19
    };

    enum ZOOM_CONSTANTS
    {
        ZOOM_STEP  = 12
    };

    enum OVERLAYSELECT_CONSTANTS
    {
        CONTOUR_LINES                                         = 1,
        SLOPE_SHADING                                         = 2,
        ELEVATION_BANDS                                       = 3,
        THREAT_INTERVISIBILITY                                = 4,
        GEO_CHIP_FEATURE                                      = 6,
        GEO_CHIP_NON_DISCERNABLE_SYMBOLS                      = 8,
        GEO_CHIP_LOCATION_SYMBOLS                             = 9,
        THREAT_DETECTION_RING                                 = 10,
        THREAT_LETHALITY_RING                                 = 11,
        THREAT_CALCULATED_RING                                = 12,
        USER_GEO_SYMBOLS                                      = 13,
        DRAWING_SYMBOLS                                       = 14,
        DVOF_TOWER_SYMBOLS                                    = 15,
        DVOF_PYLON_SYMBOLS                                    = 16,
        DVOF_BUILDING_SYMBOLS                                 = 17,
        DVOF_OTHER_SYMBOLS                                    = 18,
        DVOF_DECLUTTER_BY_HEIGHT                              = 19,
        TACTICAL_SYMBOLS                                      = 20,
        COCKPIT_PERSPECTIVE                                   = 21,
        UNDERLAY_PROCESSING                                   = 24,
        GEOCHIP_PROCESSING                                    = 25,
        ELEVATION_PROCESSING                                  = 26,
        THREAT_PROCESSING                                     = 27,
        SYMBOL_PROCESSING                                     = 28,
        PERSPECTIVE_PROCESSING                                = 29,
        VEHICLE_SYMBOL                                        = 30,
        TREND_DOTS                                            = 31,
        LINE_OF_SIGHT                                         = 32,
        POINT_OF_INTERCEPT_LINE                               = 33,
        POI_SPRITE                                            = 34,
        CURSOR                                                = 35,
        AFFILIATION_FRIEND                                    = 36,
        AFFILIATION_NEUTRAL                                   = 37,
        AFFILIATION_HOSTILE                                   = 38,
        AFFILIATION_UNKNOWN                                   = 39,
        DIMENSION_UNKNOWN                                     = 40,
        DIMENSION_SPACE                                       = 41,
        DIMENSION_AIR                                         = 42,
        DIMENSION_GROUND                                      = 43,
        DIMENSION_SEA_SURFACE                                 = 44,
        DIMENSION_SUB_SURFACE                                 = 45,
        DIMENSION_SOF                                         = 46,
        MOVEMENT_INDICATOR                                    = 47,
        SENSOR_OVERLAY                                        = 50,
        PERIODIC_POI_POINTS                                   = 52,
        MCHUM_POINTS                                          = 54,
        MCHUM_LINES                                           = 55,
        MCHUM_DISABLE_BY_HEIGHT                               = 56,
        MCHUM_COLOR_BY_HEIGHT                                 = 57,
        CLOS_RUBBERBAND                                       = 58,
        TERRAIN_MODE                                          = 60,
        USER_SCREEN_SYMBOLS                                   = 61,
        ALL_GEO_SYMBOLS                                       = 62,
        LOCAL_POINT_SYMBOLS                                   = 63,
        LOCAL_POINT_LABELS                                    = 64,
        ELEVATION_SELECTION_FILE_IO                           = 65,
        MCHUM_SYMBOLS                                         = 66,
        DVOF_SYMBOLS                                          = 67,
        ECHUM_SYMBOLS                                         = 68,
        NORTH_UP_INDICATOR                                    = 70,
        THREAT_OVERLAYS                                       = 71,
        RANGE_BEARING_LINE                                    = 74,
        THREAT_LETHALITY_DOMES                                = 75,
        ECHUM_POINTS                                          = 76,
        ECHUM_LINES                                           = 77,
        ECHUM_DECLUTTER_BY_HEIGHT                             = 78,
        ECHUM_COLOR_BY_VO                                     = 79,
        THREAT_SYMBOLS                                        = 80,
        THREAT_LABELS                                         = 81,
        VEHICLE_HISTORY_PROCESSING                            = 82,
        VEHICLE_HISTORY_DISPLAY                               = 83,
        ROUTE_GROUP                                           = 85,
        ROUTE_LEG                                             = 86,
        ROUTE_LEG_CORRIDOR                                    = 87,
        ROUTE_PERCENT_COMPLETE                                = 88,
        ROUTE_WAYPOINT                                        = 89,
        ROUTE_WAYPOINT_LABEL                                  = 90,
        ROUTE_WAYPOINT_INDEX                                  = 91,
        OWNSHIP_VISIBILITY                                    = 92,
        ELEVATION_PROFILE_CLOS                                = 93,
        CIB_AUTO_CONTRAST                                     = 94,
        COMPASS_ROSE                                          = 95,
        AIRSPACE_ACO                                          = 96,
        PERSPECTIVE_TEXTURE                                   = 99,
        PERSPECTIVE_WIREFRAME                                 = 100,
        TACTICAL_LABEL                                        = 101,
        ROUTE_FLIGHT_PLAN                                     = 102,
        TEXT_BOX                                              = 103,
        OFFSCREEN_INDICATOR                                   = 104,
        SLEW_SYMBOL                                           = 105,
        SEARCH_PATTERNS                                       = 106,
        SEARCH_AREAS                                          = 107,
        SCENE_OFFSET_3D                                       = 108,
        FIX_COMPASS_TO_OWNSHIP                                = 109,
        AFFILIATION_EXCERCISE                                 = 110,
		VERTICAL_BANDS										  =	111,
        OFFSCREEN_DISTANCE_LABEL                              = 112,
        GEO_REGISTER_PDF                                      = 113,
        PLACEMARKS                                            = 114,
        UNDERLAY_FILE_SCALING                                 = 115, // Added by MQ
        LANDING_ZONE                                          = 117,
        FILL_MODIFIER                                         = 119,
        DATAFRAME_RESPONSE                                    = 120,
        VECTOR_OVERLAY                                        = 121,
        MAP_WINDOW_SCALING                                    = 123,
        ROUTE_LEG_SIDERAILS                                   = 124,
        FRAME_MODIFIER                                        = 125,
        ICON_MODIFIER                                         = 126,
        TACTICAL_GRAPHICS                                     = 127,
        TACTICAL_GRAPHIC_LABELS                               = 128,
        RANGE_RING_SYMBOL                                     = 129,
        RANGE_RING_LABEL                                      = 130,
        VO_LABEL_DECLUTTER                                    = 131,
        BASE_CONTOUR_LINE_COLORING                            = 132,
        PERFORMANCE_BAND                                      = 135,
        STORMSCOPE_SYMBOL                                     = 136,
        RANGE_BEARING_RESPONSE                                = 137,
        SHAPEFILE                                             = 138,
        KML_KMZ_SYMBOL                                        = 139,
        GEO_SYMBOL_OFFSCREEN_INDICATOR                        = 140,
        ARINC_424_FEATURE                                     = 200,
        ARINC_424_VHF_NAVAIDS                                 = 201,
        ARINC_424_NDB_NAVAIDS                                 = 202,
        ARINC_424_WAYPOINTS                                   = 203,
        RESERVED_ARINC_424_HOLDING_PATTERNS                   = 204,
        ARINC_424_ENROUTES                                    = 205,
        ARINC_424_AIRPORTS                                    = 206,
        RESERVED_AIRPORT_GATES                                = 207,
        RESERVED_AIRPORT_SID_STARS                            = 208,
        ARINC_424_RUNWAYS                                     = 209,
        RESERVED_ARINC_424_AIRPORT_HELIPORT_LOCALIZERS        = 210,
        RESERVED_ARINC_424_COMPANY_ROUTES                     = 211,
        RESERVED_ARINC_424_AIRPORT_HELIPORT_LOCALIZER_MARKERS = 212,
        RESERVED_ARINC_424_AIRPORT_COMMUNICATIONS             = 213,
        RESERVED_ARINC_424_AIRWAY_MARKERS                     = 214,
        RESERVED_ARINC_424_CRUISING_TABLES                    = 215,
        RESERVED_ARINC_424_FIR_UIR                            = 216,
        ARINC_424_RESTRICTED_AIRSPACES                        = 217,
        RESERVED_ARINC_424_GRID_MORA                          = 218,
        RESERVED_ARINC_424_AIRPORT_MSA                        = 219,
        RESERVED_ARINC_424_ENROUTE_RESTRICTIVE                = 220,
        RESERVED_ARINC_424_MLS_RECORDS                        = 221,
        RESERVED_ARINC_424_ENROUTE_COMM                       = 222,
        RESERVED_ARINC_424_PREFERRED_ROUTE                    = 223,
        ARINC_424_CONTROLLED_AIRSPACES                        = 224,
        RESERVED_ARINC_424_GEOGRAPHICAL_REFERENCES            = 225,
        RESERVED_ARINC_424_FLIGHT_PLANNING                    = 226,
        RESERVED_ARINC_424_PATH_POINT                         = 227,
        RESERVED_ARINC_424_GLS                                = 228,
        RESERVED_ARINC_424_ALTERNATES                         = 229,
        RESERVED_ARINC_424_AIRPORT_TAA                        = 230,
        ARINC_424_HELIPORTS                                   = 231,
        RESERVED_ARINC_424_HELIPORT_TWR                       = 232,
        RESERVED_ARINC_424_HELIPORT_SID_STAR                  = 233,
        RESERVED_ARINC_424_HELIPORT_MSA                       = 234,
        RESERVED_ARINC_424_HELIPORT_COMM                      = 235,
        RESERVED_ARINC_424_HELIPORT_TAA                       = 236,
        DAFIF_FEATURE                                         = 300,
        DAFIF_AIRPORT                                         = 301,
        DAFIF_BOUNDARY                                        = 302,
        DAFIF_HELIPORT                                        = 303,
        DAFIF_MTR                                             = 304,
        DAFIF_NAVAID                                          = 305,
        DAFIF_SUAS                                            = 306,
        DAFIF_WAYPOINT                                        = 307,
        RESERVED_DAFIF_AIR_REFUELING                          = 308,
        RESERVED_DAFIF_ATCR                                   = 309,
        RESERVED_DAFIF_PREFERRED_ROUTES                       = 310,
        RESERVED_DAFIF_PARACHUTE_ROUTES                       = 311,
        RESERVED_DAFIF_TERMINAL_SYMBOLS                       = 312,
        RESERVED_DAFIF_HOLDING_PATTERNS                       = 313,
        RESERVED_DAFIF_AIRPORT_SUPPLEMENT                     = 314,
        RESERVED_DAFIF_OFF_ROUTE_TCA                          = 315,
        RESERVED_DAFIF_RNAV_APPROACH                          = 316,
        RESERVED_DAFIF_VFR_ROUTE                              = 317,
        RESERVED_DAFIF_TIME_ZONES                             = 318,
        RESERVED_DAFIF_ICAO_REGIONS                           = 319,
        DAFIF_RUNWAYS                                         = 320,
        AFD_SYMBOLS = 400,
        AFD_CONTROL_TOWER = 401,
        AFD_NAVAID = 402,
        AFD_ILS_COMPONENT = 403,
        AFD_APRON_HARDSTAND = 404,
        AFD_ARRESTING_GEAR = 405,
        AFD_HELIPAD = 406,
        AFD_STOPWAY = 407,
        AFD_RUNWAY = 408,
        AFD_RUNWAY_ENDPOINT = 409,
        AFD_TAXIWAY_SYMBOLS = 410,
        AFD_DISPLACED_THRESH_AREA = 411,
        AFD_DISPLACED_THRESH_POINT = 412,
        AFD_HANGAR = 413,
        AFD_TOWER = 414,
        AFD_WATER_TOWER = 415,
        AFD_SMOKESTACK = 416,

        NUMBER_OF_OVERLAYS                                    = 512
    };

    enum OVERLAYCOLORS_CONSTANTS
    {
        COLOR_COMPONENTS              = 4,
        COLOR_ELEVATION_BAND_1        = 0,
        COLOR_ELEVATION_BAND_2        = 1,
        COLOR_ELEVATION_BAND_3        = 2,
        COLOR_ELEVATION_BAND_4        = 3,
        COLOR_ELEVATION_BAND_5        = 4,
        COLOR_ELEVATION_BAND_6        = 5,
        COLOR_ELEVATION_BAND_7        = 6,
        COLOR_ELEVATION_BAND_8        = 7,
        COLOR_TIV_DATA_NA_INVALID     = 8,
        COLOR_UNDERLAY_DATA_NA        = 9,
        COLOR_ELEVATION_DATA_NA       = 10,
        COLOR_CONTOUR_LINE            = 11,
        COLOR_THREAT_DETECTION_RING   = 12,
        COLOR_THREAT_LETHALITY_RING   = 13,
        COLOR_THREAT_CALCULATED_RING  = 14,
        COLOR_UNDERLAY_MODULATION     = 15,
        COLOR_VO_CLEAR                = 16,
        COLOR_VO_DANGER               = 17,
        COLOR_VO_WARNING              = 18,
        COLOR_TREND_DOTS              = 19,
        COLOR_LOS_UNKNOWN             = 20,
        COLOR_LOS_CLEAR               = 21,
        COLOR_LOS_BLOCKED             = 22,
        COLOR_TERRAIN                 = 25,
        COLOR_ROUTE_TEXT              = 30,
        COLOR_ROUTE_FILL              = 31,
        COLOR_ROUTE_PERCENT_COMPLETE  = 32,
        COLOR_VO_DEFAULT              = 33,
        COLOR_OWNSHIP_VISIBILITY      = 34,
        COLOR_UNDERLAY_LOADING        = 35,
        COLOR_SPEED_GATE_LABEL        = 36,
        COLOR_ALTITUDE_GATE_LABEL     = 37,
        COLOR_TIME_STALE_MODULATION   = 42,
        COLOR_TIME_FUTURE_MODULATION  = 43,
        COLOR_GEO_SYMBOL_MODULATION   = 44,
        COLOR_LANDING_ZONE            = 48,
        COLOR_LANDING_ZONE_PRIMARY    = 49,
        COLOR_LANDING_ZONE_SECONDARY  = 50,
        COLOR_BASE_CONTOUR_LINE      = 52,
        // Tactical Graphics colors
        COLOR_TACTICAL_PENDING = 53,
        COLOR_TACTICAL_UNKNOWN = 54,
        COLOR_TACTICAL_ASSUMED_FRIEND = 55,
        COLOR_TACTICAL_FRIEND = 56,
        COLOR_TACTICAL_NEUTRAL = 57,
        COLOR_TACTICAL_SUSPECT = 58,
        COLOR_TACTICAL_HOSTILE = 59,
        COLOR_TACTICAL_EXCERCISE_PENDING = 60,
        COLOR_TACTICAL_EXCERCISE_UNKNOWN = 61,
        COLOR_TACTICAL_EXCERCISE_ASSUMED_FRIEND = 62,
        COLOR_TACTICAL_EXCERCISE_FRIEND = 63,
        COLOR_TACTICAL_EXCERCISE_NEUTRAL = 64,
        COLOR_TACTICAL_JOKER = 65,
        COLOR_TACTICAL_FAKER = 66,

        COLOR_UNDERLAY_LEVEL1         = 100,
        COLOR_UNDERLAY_LEVEL2         = 101,
        COLOR_UNDERLAY_LEVEL3         = 102,
        COLOR_UNDERLAY_LEVEL4         = 103,
        COLOR_UNDERLAY_COUNT          = 100,

        COLOR_ROUTE_WAYPOINT          = 200,
        COLOR_ROUTE_COUNT             = 50,

        COLOR_COMPASS_MAJOR_TICKS     = 250,
        COLOR_COMPASS_MINOR_TICKS     = 270,
        COLOR_COMPASS_CARDINAL_LBL    = 290,
        COLOR_COMPASS_NUMERALS        = 310,
        COLOR_COMPASS_POINTERS        = 330,
        COLOR_COMPASS_COUNT           = 15,

        NUMBER_OF_COLORS              = 512
    };

    enum SLOPESHADINGCONTROL_CONSTANTS
    {
        SCREEN_REFERENCED = 0,
        GEO_REFERENCED    = 1
    };

    enum DATAFRAMECONTROL_CONSTANTS
    {
        MIN_X_POSITION = -2047,
        MAX_X_POSITION = +2047,
        MIN_Y_POSITION = -2047,
        MAX_Y_POSITION = +2047,

        MIN_ORIENTATION = 0,
        MAX_ORIENTATION = 360,

        MIN_ZOOM = 0,

        DEFAULT_SLEW_STEP     = 100,
        DEFAULT_ROTATION_STEP = 45,
        DEFAULT_ZOOM          = 1
    };

    enum ELEVATIONBANDS_CONSTANTS
    {
        NUMBER_OF_BANDS = 7,

        OFF          = 0,
        HAT          = 1,
        STATIC       = 2,
        NUM_EB_MODES = 3
    };

    enum VERTICALBANDS_CONSTANTS
    {
        NUMBER_OF_VERTICALBANDS = 64,
		NUMBER_BYTES_PER_BAND = 16,
        VERTICALBANDS_ELEVATION = 0,
        VERTICALBANDS_DEPTH = 1,
        VERTICALBANDS_OFF = 2,
        VERTICALBANDS_BOTH = 3,
        NUM_VB_MODES = 4
    };

    enum THREAT_CONSTANTS
    {
        THREAT_NO_ACTION = 0,
        THREAT_UPDATE    = 1,
        THREAT_REPLACE   = 2,
        THREAT_DELETE    = 3,
        THREAT_TYPE_1    = 1,
        THREAT_TYPE_2    = 2
    };

    enum GEOCHIP_CONSTANTS
    {
        CHIP_NO_ACTION = 0,
        CHIP_UPDATE    = 1,
        CHIP_REPLACE   = 2,
        CHIP_DELETE    = 3,

        INDIVIDUAL_GEOCHIP = 0,

        DISCERNABLE_FACTOR_MAX = 1,
        DISCERNABLE_FACTOR_MIN = 0
    };


    enum GEOQUERY_INPUT_CONSTANTS
    {
        INPUT_GEOQUERY_SCREEN = 0,
        INPUT_GEOQUERY_GEO = 1,
    };

    enum GEOQUERY_OUTPUT_CONSTANTS
    {
        OUTPUT_GEOQUERY_SCREEN  = 0,
        OUTPUT_GEOQUERY_GEO     = 1,
        GLOBAL_ELEVATION = 2,
        CACHED_ELEVATION = 3
    };

    enum MGRS_CONVERSION_CONSTANTS
    {
        // Request Conversion Type
        SCREEN_TO_MGRS = 0,
        LAT_LON_TO_MGRS = 1,
        MGRS_TO_LAT_LON = 2,

        // Response Conversion Type
        INVALID_REQUEST = 10,
        VALID_MGRS_CODE = 11,
        VALID_LAT_LONG = 12,

        MGRS_CODE_LENGTH = 32
    };

    enum TESTDATA_CONSTANTS
    {
        ACCEPT_TEST_DATA   = 0,
        RETURN_RESULTS     = 1
    };

    enum REFRESHCACHE_CONSTANTS
    {
        REFRESH_FALSE = 0,
        REFRESH_TRUE  = 1
    };

    enum VOPARAMETERS_CONSTANTS
    {
        VO_MSL = 0,
        VO_AGL = 1
    };

    enum LINEOFSIGHT_CONSTANTS
    {
        LOS_OWNSHIP     = 0,
        LOS_FIXED       = 1,
        LOS_NUM_SOURCES = 2,

        LOS_ELEVATION_STEP  = 100,

        LOS_SCREEN = 0,
        LOS_GEO    = 1
    };

    enum SLEW_CONSTANTS
    {
        SLEW_SCREEN = 0,
        SLEW_GEO    = 1,

        SLEW_INCREMENT  = 200,
        SLEW_STEP       = 40,
        MANUAL_SLEW_MAX = 100,
        MANUAL_SLEW_MIN = 3
    };

    enum CURSORPOSITION_CONSTANTS
    {
        CURSOR_POSITION         = 0,
        OBJECT_SELECTION        = 1,
        HIGHLIGHT_OBJECT        = 2,
        DRAW_HIGHLIGHTED_OBJECT = 3,
        UNHIGHLIGHT_OBJECT      = 4,
        MOVE_OBJECT             = 5,
        DELETE_OBJECT           = 6,
        ALTERNATE_CURSOR        = 7,
        STANDARD_CURSOR         = 8,
        QUERY_OBJECT_DATA       = 9,
        QUERY_CURSOR_POSITION   = 10,
        CURSOR_ENABLE_OBJECT    = 11,
        CURSOR_DISABLE_OBJECT   = 12,
        NUM_CURSOR_ACTIONS      = 13,

        SELECT_NONE    = -1,
        SELECT_ALL     = 0,
        SELECT_THREAT  = 1,
        SELECT_VEHICLE = 2,
        SELECT_ROUTE   = 3,
        SELECT_SYMBOL  = 4
    };

    enum UNDERLAY_CONSTANTS
    {
        RENDERING  = 0,
        PROCESSING = 1,

        UNDERLAY_LEVEL1      = 0,
        UNDERLAY_LEVEL2      = 1,
        UNDERLAY_LEVEL3      = 2,
        UNDERLAY_LEVEL4      = 3,
        UNDERLAY_LEVEL_COUNT = 4
    };

    enum THREATSELECT_CONSTANTS
    {
        THREAT_INDIVIDUAL_TIV            = 0,
        THREAT_INDIVIDUAL_DETECTION_RING = 1,
        THREAT_INDIVIDUAL_LETHALITY_RING = 2,
        THREAT_INDIVIDUAL_SYMBOL         = 3,
        THREAT_INDIVIDUAL_LABELS         = 4
    };

    enum SETSYMBOL_CONSTANTS
    {
        LINE              = 1,
        POLYGON           = 2,
        ARC               = 3,
        SPRITE            = 4,
        STRING            = 5,
        LINE_GREAT_CIRCLE = 6,
        LINE_RHUMB        = 7,

        SOLID          = 0,
        TEXTURED       = 3,
        TEXTURED_COUNT = 43,

        NO_FILL                    = 0,
        FILL_HORIZONTAL            = 1,
        FILL_VERTICAL              = 2,
        FILL_BACKWARD_DIAGONAL     = 3,
        FILL_FORWARD_DIAGONAL      = 4,
        FILL_BACK_FORWARD_DIAGONAL = 5,
        FILL_SOLID                 = 7,
        FILL_SHADED                = 8,

        DISABLE_OUTLINE = 0,
        ENABLE_OUTLINE  = 1,

        OPEN_ENDED  = 0,
        CLOSE_ENDED = 1,

        STANDARD_FONT = 0
    };

    enum SETSYMBOLSKIN_CONSTANTS
    {
        NORMAL_SYMBOL,
        DYNAMIC_COLOR_SYMBOL
    };

    enum ENABLESYMBOL_CONSTANTS
    {
        ENABLE_SYMBOL    = 0,
        ENABLE_LABEL     = 1,
        ENABLE_SYMBOL_AND_LABEL = 2,

        GEO_SYMBOL      = 0,
        TACTICAL_SYMBOL = 1,
		ENABLE_BY_UID   = 146
    };

    enum ELEVATIONCONTROL_CONSTANTS
    {
        OWNSHIP_ALTITUDE      = 0,
        USER_DEFINED_ALTITUDE = 1,

        TIV_ALTITUDE_1 = 0,
        TIV_ALTITUDE_2 = 1,
        ELEVATION_BAND_INIT_HEIGHT = 2,
        VO_REF_ALTITUDE = 3
    };

    enum VEHICLEENABLES_CONSTANTS
    {
        ENABLE_VEHICLE               = 0,
        ENABLE_SENSOR                = 1,
        ENABLE_PERIODIC_SENSOR_POI   = 2,
        ENABLE_TREND_DOTS            = 5,
        ENABLE_VEHICLE_HISTORY       = 6,
        ENABLE_DIRECTION_OF_MOVEMENT = 8,
        ENABLE_SENSOR_TEXTURE        = 9
    };

    enum RANGE_AND_BEARING_CONSTANTS
    {
        RANGE_GEOSPATIAL = 0,
        RANGE_SCREEN     = 1,
        RANGE_OWNSHIP    = 2,
    };

    enum ROUTE_LEG_CONSTANTS
    {
        LEG_STRAIGHT   = 0,
        LEG_SERPENTINE = 1,
        LEG_TURN       = 2,

        LEG_FLAT_EARTH   = 0,
        LEG_GREAT_CIRCLE = 1,
        LEG_RHUMB_LINE   = 2,

        LEG_CCW = 0,
        LEG_CW  = 1
    };

    enum ROUTE_GROUP_CONSTANTS
    {
        GROUP_WAYPONT = 0,
        GROUP_LEG     = 1
    };

    enum ROUTE_GROUP_ENABLE_CONSTANTS
    {
        GROUP_ENABLE_OVERLAY          = 85,
        GROUP_ENABLE_LEGS             = 86,
        GROUP_ENABLE_LEG_CORRIDORS    = 87,
        GROUP_ENABLE_PERCENT_COMPLETE = 88,
        GROUP_ENABLE_WAYPONTS         = 89,
        GROUP_ENABLE_WAYPOINT_LABELS  = 90,
        GROUP_ENABLE_WAYPOINT_INDICES = 91
    };

    enum PERSPECTIVE_CONSTANTS
    {
        CAMERA_DEPTH_STEP = 3,

        CAMERA_OFF      = 0,
        CAMERA_TRAILING = 1,
        CAMERA_LEADING  = 2,
        CAMERA_TYPES    = 3
    };

    enum VEHICLEICON_CONSTANTS
    {
        VEHICLE_USE_ICON          = 0,
        VEHICLE_USE_TACTICAL_CODE = 1
    };

    enum ROUTE_LEG_GATE_CONSTANTS
    {
        SPEED_GATE    = 0,
        ALTITUDE_GATE = 1
    };

    enum RACETRACK_CONSTANTS
    {
        RACETRACK_FLAT_EARTH   = 0,
        RACETRACK_GREAT_CIRCLE = 1,
        RACETRACK_RHUMB_LINE   = 2,

        RACETRACK_STANDARD  = 0,
        RACETRACK_ALTERNATE = 1
    };

    enum TEXTBOX_CONSTANTS
    {
        TEXTBOX_DONT_CLEAR  = 0,
        TEXTBOX_CLEAR_FIRST = 1,

        TEXTBOX_ABSOLUTE  = 0,
        TEXTBOX_RELATEIVE = 1,

        TEXTBOX_LINE       = 0,
        TEXTBOX_PAGE       = 1,
        TEXTBOX_FIRST_PAGE = 2,
        TEXTBOX_LAST_PAGE  = 3
    };

    enum COMPASS_CONSTANTS
    {
        POINTER_COUNT = 16
    };

    enum FLIGHT_PLAN_ENABLE_CONSTANTS
    {
        FLIGHT_PLAN_OVERLAY = 102,
        ROUTE_LEGS          = 86,
        ROUTE_LEG_CORRIDORS = 87,
        ROUTE_WAYPOINTS     = 89
    };

    enum SYMBOL_FILE_ACTION_CONSTANTS
    {
        LOCAL_POINT_SYMBOL    = 6,
        MCHUM_SYMBOL          = 8,
        DRAWING_FILE_SYMBOL   = 12,
        VECTOR_OVERLAY_SYMBOL = 15
    };

    enum SYMBOL_FILE_ACTIONS
    {
        ADD_SYMBOL_FILE = 0
    };

    enum CHUM_MODES
    {
        CHUM_MCHUM = 1,
        CHUM_ECHUM = 2
    };

    enum SAR_CONSTANTS
    {
        PARALLEL_TRACK       = 0,
        EXPANDING_SQUARE     = 1,
        SECTOR_SEARCH        = 2,
        SEARCH_PATTERN_TYPES = 3,

        RIGHT_TURN = 0,
        LEFT_TURN  = 1
    };

    enum VEHICLE_CONSTANTS
    {
        VEHICLE_1 = 0,
        VEHICLE_2 = 1,
        VEHICLE_3 = 2,
        VEHICLE_4 = 3,

        SENSOR_1 = 0,
        SENSOR_2 = 1,
        SENSOR_3 = 2,
        SENSOR_4 = 3
    };

    enum VEHICLECONTROL_CONSTANTS
    {
        VEHICLE_SIMULATION       = 0,
        THREAT_PENETRATED_STATUS = 1,
        TIME_ON_TARGET           = 2,
        WAYPOINT_ALERT           = 3,

        WP_NORMAL = 0,
        WP_CRITICAL = 1,

        FP_DESELECT = 0,
        FP_WP_NEXT = 1,
        FP_WP_PREV = 2,

        FP_INACTIVE = 0,
        FP_OWNSHIP  = 1,
        FP_UAV      = 2,
        FP_EDIT     = 3,

        FP_CHANGES_REJECT = 0,
        FP_CHANGES_ACCEPT = 1,

        WP_FIRST_AVAILABLE = -1,

        WP_MOVE_ELEVATION = 0,
        WP_MOVE_POSITION  = 1,
        WP_MOVE_ELEVEVATION_AND_POSITION = 2
    };

    // Buffer constants
    enum BUFFER_CONSTANTS
    {
        MAX_FILENAME_LENGTH = 256,
        MAX_PRODUCT_CODE_LENGTH = 4
    };

    // Geo Point Symbol Constants
    enum GEO_POINT_SYMBOL_TYPES
    {
        TYPE_GEO_USER_SYMBOL      = 4,
        TYPE_TACTICAL_2525_SYMBOL = 5,
        TYPE_LOCAL_POINT_SYMBOL   = 6,
        TYPE_DVOF_SYMBOL          = 7,
        TYPE_MCHUM_SYMBOL         = 8,
        TYPE_ARINC_424_SYMBOL     = 9,
        TYPE_DAFIF_SYMBOL         = 10,
        TYPE_DRAWING_FILE_SYMBOL  = 12,
        TYPE_AIRSPACE_ACO_SYMBOL  = 14,
        TYPE_PLACEMARK_SYMBOL     = 15
    };

    enum LANDING_ZONE_RESOLUTIONS
    {
        AUTO_RESOLUTION   = 0,
        BEACON_RESOLUTION = 1,
        LOW_RESOLUTION    = 2,
        MEDIUM_RESOLUTION = 3,
        HIGH_RESOLUTION   = 4
    };

};

#endif /* FS_CONSTANTS_H_HEADER_INCLUDED */

#include "MapZoom.h"
#include "FS_Comm.h"

// static variables
static double s_dZoom = 1.0;

//****************************************************************************
//* ZoomIn 
//****************************************************************************
void MapZoom::ZoomIn()
{
    // zoom in on Channel 0 by double the previous amount. 
    s_dZoom *= 2.0;
    FS_Comm::SendMsg_Zoom(0, // Channel to send to 
        s_dZoom); // Zoom scale. (> 1.0: zoom in, < 1.0: zoom out)
}

//****************************************************************************
//* ZoomOut 
//****************************************************************************
void MapZoom::ZoomOut()
{
    // zoom out on Channel 0 by half the previous amount. 
    s_dZoom /= 2.0;
    FS_Comm::SendMsg_Zoom(0, // Channel to send to 
        s_dZoom); // Zoom scale. (> 1.0: zoom in, < 1.0: zoom out)
}

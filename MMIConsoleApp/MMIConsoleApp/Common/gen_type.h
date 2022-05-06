//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: gen_type.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// This file contains general types definitions
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef GEN_TYPE_H
#define GEN_TYPE_H

#include<windows.h>

// Define "sized" type for floats and doubles (jsf req)
typedef double FLOAT64;
typedef float FLOAT32;

// Constants
const FLOAT64 m_pi = 3.14159;
const FLOAT64 m_min_lat = -90.0;
const FLOAT64 m_max_lat = 90.0;
const FLOAT64 m_min_long = -180.0;
const FLOAT64 m_max_long = 180.0;
const FLOAT64 m_min_heading = 0.0;
const FLOAT64 m_max_heading = 360.0;
const FLOAT64 m_min_pitch = -90.0;
const FLOAT64 m_max_pitch = 90.0;
const FLOAT64 m_min_roll = -180.0;
const FLOAT64 m_max_roll = 180.0;

#endif // !GEN_TYPE_H
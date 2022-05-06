//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: XmlSerializer.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for XmlSerializer
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#pragma once
#include <vector>
#include <../PAGE/header/structs.h>
#include <../../RapidXml/rapidxml.h>

using namespace rapidxml;

class XmlSerializer
{
    XmlSerializer()
    {
    }

    ~XmlSerializer()
    {
    }

public:
    static vector<char> readXml(string pfile);
    static DISPLAY_CONFIG parseDisplayConfigXml(vector<char> buffer);
};

#endif // !XMLSERIALIZER_H
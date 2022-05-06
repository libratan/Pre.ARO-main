//#pragma once
//#using <System.Xml.dll>
//
//using namespace System::Xml;
//
#include <stdio.h>
#include <vector>>
#include "structs.h"
#include "RapidXml/rapidxml.h"

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


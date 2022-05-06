#include "XmlSerializer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "RapidXml/rapidxml.h"

#include "structs.h"

using namespace std;
using namespace rapidxml;


vector<char> XmlSerializer::readXml(string pfile)
{
    xml_document<> doc;
    xml_node<>* root_node = NULL;
    
    // Read file
    ifstream theFile(pfile.c_str());
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    return buffer;
}


DISPLAY_CONFIG XmlSerializer::parseDisplayConfigXml(vector<char> buffer)
{
    DISPLAY_CONFIG ndisplay_config;
    
    xml_document<> doc;
    xml_node<>* root_node = NULL;

    // Parse the buffer
    doc.parse<0>(&buffer[0]);

    // Find out the root node
    root_node = doc.first_node("DMM_CONFIG"); 

    // Iterate over the nodes
    for (xml_node<>* student_node = root_node->first_node(); student_node; student_node = student_node->next_sibling())
    {
        if (student_node->type() == node_element)
        {
            string nodeName = student_node->name();
            
            if (nodeName == "FS_CONFIG_PATH")
            {
                ndisplay_config.FS_config_path = student_node->value();

            }
            else if(nodeName == "UDP_CONFIG")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "IP_CONFIG")
                        {
                            ndisplay_config.UDP_config.ip_address = student_name_node->value();
                        }
                        else if (nodeName == "PORT_CONFIG")
                        {
                            ndisplay_config.UDP_config.port = stoi(student_name_node->value());
                        }
                    }
                    else
                    {
                        // Node does not have a name.  Currenly ignore such nodes because it should not exist.
                    }
                }
            }
            else
            {
                // Node is not used currently
            }
        }
        else
        {
            // Node does not have a name.  Currenly ignore such nodes because it should not exist.
        }
    }

    return ndisplay_config;
}



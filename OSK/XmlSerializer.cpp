#include "XmlSerializer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "RapidXml/rapidxml.h"

#include "structs.h"
//#include "enums.h"

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
    DISPLAY_CONFIG ndisplay_config = { 75,55,5,5 };
    
    xml_document<> doc;
    xml_node<>* root_node = NULL;

    // Parse the buffer
    doc.parse<0>(&buffer[0]);

    // Find out the root node
    root_node = doc.first_node("KEYBOARD_CONFIG"); 

    // Iterate over the nodes
    for (xml_node<>* student_node = root_node->first_node(); student_node; student_node = student_node->next_sibling())
    {
        if (student_node->type() == node_element)
        {
            string nodeName = student_node->name();
            if (nodeName == "ALPHABET")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "WIDTH")
                        {
                            ndisplay_config.ALPHA_W = stoi(student_name_node->value());
                        }
                        else if (nodeName == "HEIGHT")
                        {
                            ndisplay_config.ALPHA_H = stoi(student_name_node->value());
                        }
                    }
                }
            }

            else if (nodeName == "SPACING")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "WIDTH")
                        {
                            ndisplay_config.SPACE_W = stoi(student_name_node->value());
                        }
                        else if (nodeName == "HEIGHT")
                        {
                            ndisplay_config.SPACE_H = stoi(student_name_node->value());
                        }
                    }
                }
            }

            else if (nodeName == "TEXT")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "R")
                        {
                            ndisplay_config.TEXT_RED = stoi(student_name_node->value());
                        }
                        else if (nodeName == "G")
                        {
                            ndisplay_config.TEXT_GREEN = stoi(student_name_node->value());
                        }
                        else if (nodeName == "B")
                        {
                            ndisplay_config.TEXT_BLUE = stoi(student_name_node->value());
                        }
                        else if (nodeName == "FONT_STYLE")
                        {
                            //display_config.TEXT_STYLE = stoi(student_name_node->value());
                            strcpy_s(ndisplay_config.TEXT_STYLE, student_name_node->value());
                        }
                        else if (nodeName == "FONT_SIZE")
                        {
                            ndisplay_config.TEXT_SIZE = stoi(student_name_node->value());
                        }
                    }
                }
            }

            else if (nodeName == "BUTTON_COLOUR")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "R")
                        {
                            ndisplay_config.BUTTON_RED = stoi(student_name_node->value());
                        }
                        else if (nodeName == "G")
                        {
                            ndisplay_config.BUTTON_GREEN = stoi(student_name_node->value());
                        }
                        else if (nodeName == "B")
                        {
                            ndisplay_config.BUTTON_BLUE = stoi(student_name_node->value());
                        }
                    }
                }
            }

            else if (nodeName == "BACKGROUND_COLOUR")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "R")
                        {
                            ndisplay_config.BG_RED = stoi(student_name_node->value());
                        }
                        else if (nodeName == "G")
                        {
                            ndisplay_config.BG_GREEN = stoi(student_name_node->value());
                        }
                        else if (nodeName == "B")
                        {
                            ndisplay_config.BG_BLUE = stoi(student_name_node->value());
                        }
                    }
                }
            }

            else if (nodeName == "MESSAGE_BOX")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "WIDTH")
                        {
                            ndisplay_config.MSG_W = stoi(student_name_node->value());
                        }
                        else if (nodeName == "HEIGHT")
                        {
                            ndisplay_config.MSG_H = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "WINDOW")
            {
				for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
				{
					if (student_name_node->type() == node_element)
					{
						nodeName = student_name_node->name();

						if (nodeName == "WIDTH")
						{
							ndisplay_config.WINDOW_W = stoi(student_name_node->value());
						}
						else if (nodeName == "HEIGHT")
						{
							ndisplay_config.WINDOW_H = stoi(student_name_node->value());
						}
					}
				}
            }
        }
    }
    return ndisplay_config;
}
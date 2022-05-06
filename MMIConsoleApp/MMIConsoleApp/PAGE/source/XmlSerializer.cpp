#include <../PAGE/header/XmlSerializer.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <../../RapidXml/rapidxml.h>

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
    root_node = doc.first_node("MMI_CONFIG");

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
            else if (nodeName == "UDP_CONFIG")
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
            else if (nodeName == "KEYBOARD_KEYS")
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
                            strcpy_s(ndisplay_config.TEXT_STYLE, student_name_node->value());
                        }
                        else if (nodeName == "KEYBOARD_FONT_SIZE")
                        {
                            ndisplay_config.KEYBOARD_TEXT_SIZE = stoi(student_name_node->value());
                        }
                        else if (nodeName == "OSB_FONT_SIZE")
                        {
                            ndisplay_config.OSB_TEXT_SIZE = stoi(student_name_node->value());
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
                            ndisplay_config.WINDOW_WIDTH = stoi(student_name_node->value());
                        }
                        else if (nodeName == "HEIGHT")
                        {
                            ndisplay_config.WINDOW_HEIGHT = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "OSB_SIZE")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "WIDTH")
                        {
                            ndisplay_config.OSB_SIZE.first = stoi(student_name_node->value());
                        }
                        else if (nodeName == "HEIGHT")
                        {
                            ndisplay_config.OSB_SIZE.second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "T1")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[0].first = stoi(student_name_node->value());
                        }
                        else if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_TOP_POS[0].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "T2")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[1].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[1].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "T3")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[2].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[2].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "T4")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[3].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[3].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "T5")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[4].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[4].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "T6")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[5].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[5].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "T7")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[6].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[6].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "T8")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[7].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[7].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "T9")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[8].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[8].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "T10")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_TOP_POS[9].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_TOP_POS[9].second = ndisplay_config.BUTTON_TOP_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "L1")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_LEFT_POS[0].first = stoi(student_name_node->value());
                        }
                        else if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_LEFT_POS[0].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "L2")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_LEFT_POS[1].first = ndisplay_config.BUTTON_LEFT_POS[0].first;
                            ndisplay_config.BUTTON_LEFT_POS[1].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "L3")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_LEFT_POS[2].first = ndisplay_config.BUTTON_LEFT_POS[1].first;
                            ndisplay_config.BUTTON_LEFT_POS[2].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "L4")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_LEFT_POS[3].first = ndisplay_config.BUTTON_LEFT_POS[1].first;
                            ndisplay_config.BUTTON_LEFT_POS[3].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "R1")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_RIGHT_POS[0].first = stoi(student_name_node->value());
                        }
                        else if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_RIGHT_POS[0].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "R2")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_RIGHT_POS[1].first = ndisplay_config.BUTTON_RIGHT_POS[0].first;
                            ndisplay_config.BUTTON_RIGHT_POS[1].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "R3")
            {
            for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
            {
                if (student_name_node->type() == node_element)
                {
                    nodeName = student_name_node->name();

                    if (nodeName == "Y")
                    {
                        ndisplay_config.BUTTON_RIGHT_POS[2].first = ndisplay_config.BUTTON_RIGHT_POS[0].first;
                        ndisplay_config.BUTTON_RIGHT_POS[2].second = stoi(student_name_node->value());
                    }
                }
            }
            }
            else if (nodeName == "R4")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_RIGHT_POS[3].first = ndisplay_config.BUTTON_RIGHT_POS[0].first;
                            ndisplay_config.BUTTON_RIGHT_POS[3].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "B1")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[0].first = stoi(student_name_node->value());
                        }
                        else if (nodeName == "Y")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[0].second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "B2")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[1].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_BOTTOM_POS[1].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "B3")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[2].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_BOTTOM_POS[2].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "B4")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[3].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_BOTTOM_POS[3].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "B5")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[4].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_BOTTOM_POS[4].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "B6")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[5].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_BOTTOM_POS[5].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "B7")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[6].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_BOTTOM_POS[6].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "B8")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[7].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_BOTTOM_POS[7].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "B9")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.BUTTON_BOTTOM_POS[8].first = stoi(student_name_node->value());
                            ndisplay_config.BUTTON_BOTTOM_POS[8].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                        }
                    }
                }
            }
            else if (nodeName == "B10")
            {
            for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
            {
                if (student_name_node->type() == node_element)
                {
                    nodeName = student_name_node->name();

                    if (nodeName == "X")
                    {
                        ndisplay_config.BUTTON_BOTTOM_POS[9].first = stoi(student_name_node->value());
                        ndisplay_config.BUTTON_BOTTOM_POS[9].second = ndisplay_config.BUTTON_BOTTOM_POS[0].second;
                    }
                }
            }
            }
            else if (nodeName == "TAB_CTRL_SIZE")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "WIDTH")
                        {
                            ndisplay_config.TAB_CTRL_SIZE.first = stoi(student_name_node->value());
                        }
                        else if (nodeName == "HEIGHT")
                        {
                            ndisplay_config.TAB_CTRL_SIZE.second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "TAB_CTRL_POS")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "X")
                        {
                            ndisplay_config.TAB_CTRL_POS.first = stoi(student_name_node->value());
                        }
                        else if (nodeName == "Y")
                        {
                            ndisplay_config.TAB_CTRL_POS.second = stoi(student_name_node->value());
                        }
                    }
                }
            }
            else if (nodeName == "TAB_SIZE")
            {
                for (xml_node<>* student_name_node = student_node->first_node(); student_name_node; student_name_node = student_name_node->next_sibling())
                {
                    if (student_name_node->type() == node_element)
                    {
                        nodeName = student_name_node->name();

                        if (nodeName == "WIDTH")
                        {
                            ndisplay_config.TAB_SIZE.first = stoi(student_name_node->value());
                        }
                        else if (nodeName == "HEIGHT")
                        {
                            ndisplay_config.TAB_SIZE.second = stoi(student_name_node->value());
                        }
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
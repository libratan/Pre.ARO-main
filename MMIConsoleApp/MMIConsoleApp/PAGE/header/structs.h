#ifndef STRUCT_H
#define STRUCT_H
#pragma once
#include <string>
#include <windows.h>

using namespace std;

struct UDP_CONFIG {
    string ip_address;
    int port;
};

struct DISPLAY_CONFIG {
        string FS_config_path;
        UDP_CONFIG UDP_config;
        INT ALPHA_W;
        INT ALPHA_H;

        INT SPACE_W;
        INT SPACE_H;

        INT TEXT_RED;
        INT TEXT_GREEN;
        INT TEXT_BLUE;
        FLOAT KEYBOARD_TEXT_SIZE;
        FLOAT OSB_TEXT_SIZE;
        CHAR TEXT_STYLE[32];

        INT BUTTON_RED;
        INT BUTTON_GREEN;
        INT BUTTON_BLUE;

        INT BG_RED;
        INT BG_GREEN;
        INT BG_BLUE;

        INT MSG_W;
        INT MSG_H;

        INT WINDOW_WIDTH;
        INT WINDOW_HEIGHT;

        std::pair <INT, INT> OSB_SIZE;

        std::pair <INT, INT> BUTTON_TOP_POS[10];
        std::pair <INT, INT> BUTTON_LEFT_POS[4];
        std::pair <INT, INT> BUTTON_RIGHT_POS[4];
        std::pair <INT, INT> BUTTON_BOTTOM_POS[10];

        std::pair <INT, INT> TAB_CTRL_SIZE;
        std::pair <INT, INT> TAB_CTRL_POS;
        std::pair <INT, INT> TAB_SIZE;
};

//DISPLAY_CONFIG sDisplay_config;
//HWND MsgBox;
//HWND alphabet_buttons[26];
//HWND number_buttons[10];
//HWND period_button;
//HWND enter_button;
//HWND space_button;
//HWND backspace_button;
//HDC hDevice;
//HGLRC hContext;

#endif
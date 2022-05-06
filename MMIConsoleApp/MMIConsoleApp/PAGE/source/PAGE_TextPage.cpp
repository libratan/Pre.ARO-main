//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Page_TextPage.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for Text Page
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../PAGE/header/PAGE_TextPage.h>

extern HWND MAIN_WINDOW;
extern HWND DMM_WINDOW;
extern HWND BUTTON_TOP[10];
extern HWND BUTTON_LEFT[4];
extern HWND BUTTON_RIGHT[4];
extern HWND BUTTON_BOTTOM[10];
extern HWND MSGBOX;
extern std::vector<HWND> BUTTON_KEYBOARD_NUMBERS;
extern std::vector<HWND> BUTTON_KEYBOARD_ALPHABET;
extern HWND BUTTON_KEYBOARD_BACKSPACE;
extern HWND BUTTON_KEYBOARD_PERIOD;
extern HWND BUTTON_KEYBOARD_SPACE;
extern HWND BUTTON_KEYBOARD_ENTER;
extern DISPLAY_CONFIG sDisplay_config;

namespace PAGE {

    TextPage::TextPage(void)
    {
    }

    TextPage::~TextPage(void)
    {
    }

    void TextPage::doEndInit()
    {
        
    }
    
    void TextPage::managePage()
    {
        // draw legends, mnenonics and PXLs
        displayStatus();

        // draw symbols
        displaySymbol();
    }

    //****************************************************************************
    //* Function Name  : showRequiredWindows()
    //* Purpose        : Show/Hide required Windows
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void TextPage::showRequiredWindows()
    {
        ShowWindow(DMM_WINDOW, SW_HIDE);

        ShowWindow(BUTTON_TOP[0], SW_SHOW);
        ShowWindow(BUTTON_TOP[1], SW_HIDE);
        ShowWindow(BUTTON_TOP[2], SW_HIDE);
        ShowWindow(BUTTON_TOP[3], SW_HIDE);
        ShowWindow(BUTTON_TOP[4], SW_HIDE);
        ShowWindow(BUTTON_TOP[5], SW_HIDE);
        ShowWindow(BUTTON_TOP[6], SW_HIDE);
        ShowWindow(BUTTON_TOP[7], SW_HIDE);
        ShowWindow(BUTTON_TOP[8], SW_HIDE);
        ShowWindow(BUTTON_TOP[9], SW_SHOW);

        ShowWindow(BUTTON_BOTTOM[0], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[1], SW_HIDE);
        ShowWindow(BUTTON_BOTTOM[2], SW_HIDE);
        ShowWindow(BUTTON_BOTTOM[3], SW_HIDE);
        ShowWindow(BUTTON_BOTTOM[4], SW_HIDE);
        ShowWindow(BUTTON_BOTTOM[5], SW_HIDE);
        ShowWindow(BUTTON_BOTTOM[6], SW_HIDE);
        ShowWindow(BUTTON_BOTTOM[7], SW_HIDE);
        ShowWindow(BUTTON_BOTTOM[8], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[9], SW_SHOW);

        ShowWindow(BUTTON_LEFT[0], SW_HIDE);
        ShowWindow(BUTTON_LEFT[1], SW_HIDE);
        ShowWindow(BUTTON_LEFT[2], SW_HIDE);
        ShowWindow(BUTTON_LEFT[3], SW_HIDE);

        ShowWindow(BUTTON_RIGHT[0], SW_HIDE);
        ShowWindow(BUTTON_RIGHT[1], SW_HIDE);
        ShowWindow(BUTTON_RIGHT[2], SW_HIDE);
        ShowWindow(BUTTON_RIGHT[3], SW_HIDE);

        ShowWindow(MSGBOX, SW_SHOW);
        for (HWND handle : BUTTON_KEYBOARD_NUMBERS)
        {
            ShowWindow(handle, SW_SHOW);
        }
        for (HWND handle : BUTTON_KEYBOARD_ALPHABET)
        {
            ShowWindow(handle, SW_SHOW);
        }
        ShowWindow(BUTTON_KEYBOARD_BACKSPACE, SW_SHOW);
        ShowWindow(BUTTON_KEYBOARD_PERIOD, SW_SHOW);
        ShowWindow(BUTTON_KEYBOARD_SPACE, SW_SHOW);
        ShowWindow(BUTTON_KEYBOARD_ENTER, SW_SHOW);
    }

    void TextPage::displaySymbol()
    {
        PageControlMgr::sendMessageToScreenToDrawSymbols();
    }


    void TextPage::processOsb1Legend()
    {
        //check states for OSB 1
        //and update outgoing structures
    }

    void TextPage::processOsb2Legend()
    {
        //check states for OSB 2
        //and update outgoing structures
    }

    void TextPage::processOsb3Legend()
    {
    }

    void TextPage::processOsb4Legend()
    {
    }

    void TextPage::processOsb5Legend()
    {
    }

    void TextPage::processOsb6Legend()
    {
    }

    void TextPage::processOsb7Legend()
    {
    }

    void TextPage::processOsb8Legend()
    {
    }

    void TextPage::displayStatus()
    {

        processOsb1Legend();

        processOsb2Legend();

        processOsb3Legend();

        processOsb4Legend();

        processOsb5Legend();

        processOsb6Legend();

        processOsb7Legend();

        processOsb8Legend();

        processAndShowImportantStrings();

        //draw OSB legends
        PageControlMgr::sendMessageToScreenToDrawOsbLegends();

    }

    void TextPage::processAndShowImportantStrings()
    {
        //implementation to draw special text
    }
}
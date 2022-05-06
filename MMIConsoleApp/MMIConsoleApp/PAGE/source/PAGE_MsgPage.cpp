//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Page_MsgPage.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for Message Page
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../PAGE/header/PAGE_MsgPage.h>

extern HWND BUTTON_RIGHT[10];
extern HWND BUTTON_BOTTOM[10];
extern HWND DMM_WINDOW;

namespace PAGE {

    MsgPage::MsgPage(void)
    {
    }

    MsgPage::~MsgPage(void)
    {
    }

    void MsgPage::doEndInit()
    {

    }

    void MsgPage::managePage()
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
    void MsgPage::showRequiredWindows()
    {
        ShowWindow(BUTTON_BOTTOM[0], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[1], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[2], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[3], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[4], SW_SHOW);
        ShowWindow(BUTTON_RIGHT[0], SW_SHOW);
        ShowWindow(BUTTON_RIGHT[1], SW_SHOW);
        ShowWindow(BUTTON_RIGHT[2], SW_SHOW);
    }

    void MsgPage::displaySymbol()
    {
        PageControlMgr::sendMessageToScreenToDrawSymbols();
    }


    void MsgPage::processOsb1Legend()
    {
        //check states for OSB 1
        //and update outgoing structures
    }

    void MsgPage::processOsb2Legend()
    {
        //check states for OSB 2
        //and update outgoing structures
    }

    void MsgPage::processOsb3Legend()
    {
    }

    void MsgPage::processOsb4Legend()
    {
    }

    void MsgPage::processOsb5Legend()
    {
    }

    void MsgPage::processOsb6Legend()
    {
    }

    void MsgPage::processOsb7Legend()
    {
    }

    void MsgPage::processOsb8Legend()
    {
    }

    void MsgPage::displayStatus()
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

    void MsgPage::processAndShowImportantStrings()
    {
        //implementation to draw special text
    }
}
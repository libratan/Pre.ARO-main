//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Page_NetPage.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for Network Page
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../PAGE/header/PAGE_NetPage.h>

extern HWND BUTTON_RIGHT[10];
extern HWND BUTTON_BOTTOM[10];
extern HWND DMM_WINDOW;

namespace PAGE {

    NetPage::NetPage(void)
    {
    }

    NetPage::~NetPage(void)
    {
    }

    void NetPage::doEndInit()
    {

    }

    void NetPage::managePage()
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
    void NetPage::showRequiredWindows()
    {
        ShowWindow(DMM_WINDOW, SW_HIDE);
    }

    void NetPage::displaySymbol()
    {
        PageControlMgr::sendMessageToScreenToDrawSymbols();
    }


    void NetPage::processOsb1Legend()
    {
        //check states for OSB 1
        //and update outgoing structures
    }

    void NetPage::processOsb2Legend()
    {
        //check states for OSB 2
        //and update outgoing structures
    }

    void NetPage::processOsb3Legend()
    {
    }

    void NetPage::processOsb4Legend()
    {
    }

    void NetPage::processOsb5Legend()
    {
    }

    void NetPage::processOsb6Legend()
    {
    }

    void NetPage::processOsb7Legend()
    {
    }

    void NetPage::processOsb8Legend()
    {
    }

    void NetPage::displayStatus()
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

    void NetPage::processAndShowImportantStrings()
    {
        //implementation to draw special text
    }
}
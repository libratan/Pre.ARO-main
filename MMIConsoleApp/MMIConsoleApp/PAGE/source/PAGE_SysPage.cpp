//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Page_SysPage.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for System Status Page
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../PAGE/header/PAGE_SysPage.h>

extern HWND BUTTON_RIGHT[10];
extern HWND BUTTON_BOTTOM[10];
extern HWND DMM_WINDOW;

namespace PAGE {

    SysPage::SysPage(void)
    {
    }

    SysPage::~SysPage(void)
    {
    }

    void SysPage::doEndInit()
    {

    }

    void SysPage::managePage()
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
    void SysPage::showRequiredWindows()
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

    void SysPage::displaySymbol()
    {
        PageControlMgr::sendMessageToScreenToDrawSymbols();
    }


    void SysPage::processOsb1Legend()
    {
        //check states for OSB 1
        //and update outgoing structures
    }

    void SysPage::processOsb2Legend()
    {
        //check states for OSB 2
        //and update outgoing structures
    }

    void SysPage::processOsb3Legend()
    {
    }

    void SysPage::processOsb4Legend()
    {
    }

    void SysPage::processOsb5Legend()
    {
    }

    void SysPage::processOsb6Legend()
    {
    }

    void SysPage::processOsb7Legend()
    {
    }

    void SysPage::processOsb8Legend()
    {
    }

    void SysPage::displayStatus()
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

    void SysPage::processAndShowImportantStrings()
    {
        //implementation to draw special text
    }
}
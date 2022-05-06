//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Page_DcltPage.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for Declutter Page
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../PAGE/header/PAGE_DcltPage.h>

extern HWND BUTTON_RIGHT[10];
extern HWND BUTTON_BOTTOM[10];
extern HWND DMM_WINDOW;

namespace PAGE {

    DcltPage::DcltPage(void)
    {
    }

    DcltPage::~DcltPage(void)
    {
    }

    void DcltPage::doEndInit()
    {

    }

    void DcltPage::managePage()
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
    void DcltPage::showRequiredWindows()
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

    void DcltPage::displaySymbol()
    {
        PageControlMgr::sendMessageToScreenToDrawSymbols();
    }


    void DcltPage::processOsb1Legend()
    {
        //check states for OSB 1
        //and update outgoing structures
    }

    void DcltPage::processOsb2Legend()
    {
        //check states for OSB 2
        //and update outgoing structures
    }

    void DcltPage::processOsb3Legend()
    {
    }

    void DcltPage::processOsb4Legend()
    {
    }

    void DcltPage::processOsb5Legend()
    {
    }

    void DcltPage::processOsb6Legend()
    {
    }

    void DcltPage::processOsb7Legend()
    {
    }

    void DcltPage::processOsb8Legend()
    {
    }

    void DcltPage::displayStatus()
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

    void DcltPage::processAndShowImportantStrings()
    {
        //implementation to draw special text
    }
}
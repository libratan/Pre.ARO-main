//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: PAGE_SysPage.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for System Status Page
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef PAGE_SYSPAGE_H
#define PAGE_SYSPAGE_H

#include <../PAGE/header/PAGE_pageControlMgr.h>


namespace PAGE
{
    class SysPage : public PageControlMgr
    {
    public:
        SysPage(void);
        virtual ~SysPage(void);

        virtual void doEndInit();

        virtual void managePage();
        virtual void showRequiredWindows();
        virtual void displaySymbol();
        virtual void displayStatus();

    private:

        void processOsb1Legend();  //check and show legend
        void processOsb2Legend();  //check and show legend
        void processOsb3Legend();  //check and show legend
        void processOsb4Legend();  //check and show legend
        void processOsb5Legend();  //check and show legend
        void processOsb6Legend();  //check and show legend
        void processOsb7Legend();  //check and show legend
        void processOsb8Legend();  //check and show legend
        void processAndShowImportantStrings();

        //member variables
    };
}

#endif
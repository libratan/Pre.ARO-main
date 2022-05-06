//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: PAGE_DcltPage.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for Declutter Page
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef PAGE_DCLTPAGE_H
#define PAGE_DCLTPAGE_H

#include <../PAGE/header/PAGE_pageControlMgr.h>


namespace PAGE
{
    class DcltPage : public PageControlMgr
    {
    public:
        DcltPage(void);
        virtual ~DcltPage(void);

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
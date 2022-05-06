//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Page_pageMgr.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for Page Manager
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef PAGEMGR_H
#define PAGEMGR_H

// Display pages 
#include <../PAGE/header/PAGE_HSDMapPage.h>
#include <../PAGE/header/PAGE_TextPage.h>
#include <../PAGE/header/PAGE_EOPage.h>
#include <../PAGE/header/PAGE_NetPage.h>
#include <../PAGE/header/PAGE_SysPage.h>
#include <../PAGE/header/PAGE_DcltPage.h>
#include <../PAGE/header/PAGE_MsgPage.h>

namespace PAGE
{
    //*****************************************************************************
    // Class Definitions
    // Comments: Singleton class that is used by the "framework"'s DispAppThread class
    //*****************************************************************************
    class PageMgr
    {
    public:

        // Purpose:
        // Singleton instantiation
        // Description:
        // This method ensures that this class is created as a singleton
        static PageMgr* getInstance()
        {
            while (pageMgrPtr_ == NULL)
            {
                pageMgrPtr_ = new PageMgr();
            }

            return pageMgrPtr_;
        }

        // Purpose:
        // Initialization work that is not dependent on the existence of other threads
        void doEndInit();

        // Purpose:
        // This member function is used to control the logic flow of the 
        // Display Control Manager while the thread is running. (Cycle routine code)
        // Comment:
        // the "framework" will periodically call execute() at interval of X ms
        // to wake up the Display Manager
        // this X ms is based on system requirements
        void execute();
 
        // Purpose:
        // Dispose of singleton
        // Description:
        // This method deletes the singleton object of this class
        void dispose()
        {
            if (!pageMgrDisposedFlag_)
            {
                pageMgrDisposedFlag_ = true;
            }
        }   

    private:

        // Purpose:
        // Constructor
        // Description:
        // Initializes all member variables 		
        PageMgr()
        {
            pagePointer_[LAST_PAGE] = NULL;

            pageMgrDisposedFlag_ = false;
        }

        virtual ~PageMgr()
        {
        }

        // DISP Mgr Singleton
        static PageMgr* pageMgrPtr_;

        // Display page objects
        HSDMapPage HSDMapPageObject_;
        NetPage NetPageObject_;
        SysPage SysPageObject_;
        DcltPage DcltPageObject_;
        MsgPage MsgPageObject_;
        TextPage TextPageObject_;
        EOPage EOPageObject_;
        //to implement other pages

        // Pointers to Display pages
        PageControlMgr* pagePointer_[LAST_PAGE];

        bool pageMgrDisposedFlag_;
    };// end PageMgr class 

}// namespace Disp
#endif 


//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: Page_pageMgr.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for Page Manager
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../PAGE/header/PAGE_pageMgr.h>

extern HWND MAIN_WINDOW;

namespace PAGE
{
    PageMgr * PageMgr::pageMgrPtr_ = NULL; //PageMgr singleton class
    
    //****************************************************************************
    //* Function Name  : void execute()
    //* Purpose        : the "framework" will periodically call execute() at interval of X ms
    //*                  to wake up the Display Manager, this X ms is based on system requirementss
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void PageMgr::execute()
    {
        static unsigned short int currentPageIndex;
        static unsigned short int previousPageIndex;

        /*  Performing PAGE Operation
        --------------------------- */
        // get active page index
        currentPageIndex = PageControlMgr::getMasterPageIndex();

        // To avoid currentPageIndex from going beyond max index
        if ((currentPageIndex < LAST_PAGE) && (PageControlMgr::getPageStatus() == OPERATIONAL_STATE))
        {
            if (currentPageIndex != previousPageIndex)
            {
                //PageControlMgr::hideAllWindows();
                pagePointer_[currentPageIndex]->showRequiredWindows();
                previousPageIndex = currentPageIndex;
            }
            //run the active Display page object, drawings etc..
            pagePointer_[currentPageIndex]->managePage();

            //handle key presses (Note: to check which OSB is pressed)
            pagePointer_[currentPageIndex]->manageOsb();
        }
    }
    
    //****************************************************************************
    //* Function Name  : doEndInit()
    //* Purpose        : Do end of initialzation 
    //*                 
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void PageMgr::doEndInit(void)
    {
        //init pointers
        pagePointer_[HSDMAP_PAGE] = static_cast<HSDMapPage*>(&HSDMapPageObject_);
        pagePointer_[NET_PAGE] = static_cast<NetPage*>(&NetPageObject_);
        pagePointer_[SYS_PAGE] = static_cast<SysPage*>(&SysPageObject_);
        pagePointer_[DCLT_PAGE] = static_cast<DcltPage*>(&DcltPageObject_);
        pagePointer_[MSG_PAGE] = static_cast<MsgPage*>(&MsgPageObject_);
        pagePointer_[TEXT_PAGE] = static_cast<TextPage*>(&TextPageObject_);
        pagePointer_[EO_PAGE] = static_cast<EOPage*>(&EOPageObject_);


        PageControlMgr::initializeMainWindowThread();
        //default is Main page, i.e. startup page
        PageControlMgr::setMasterPageIndex(static_cast<unsigned short>(HSDMAP_PAGE));    

        pagePointer_[HSDMAP_PAGE]->doEndInit();
        //pagePointer_[TEXT_PAGE]->doEndInit();

        //PageControlMgr::hideAllWindows();
        pagePointer_[PageControlMgr::getMasterPageIndex()]->showRequiredWindows();

        //Set Page State to Operational State
        PageControlMgr::initializeComplete();
    }
}// namespace Disp
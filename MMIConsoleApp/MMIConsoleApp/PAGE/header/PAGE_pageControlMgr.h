//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: PAGE_pageControlMgr.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for Page Control Manager
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef PAGE_PAGECONTROLMGR_H
#define PAGE_PAGECONTROLMGR_H

#include <../PAGE/header/PAGE_DcmFailure.h>
#include <../PAGE/header/structs.h>
#include <../PAGE/header/XmlSerializer.h>
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>


//enums START - to shift enums to some other header file
enum PageState
{
    INITIALIZATION_STATE = 1,
    OPERATIONAL_STATE = 2
};

enum PAGE_PagesDisplayed
{
    HSDMAP_PAGE = 0,
    DCLT_PAGE,
    NET_PAGE,
    SYS_PAGE,
    MSG_PAGE,
    EO_PAGE,
    TEXT_PAGE,
    LAST_PAGE //i.e. total num of pages
};

enum OSB_NUMS
{
    INVALID_OSB = 0,
    T1,
    T2,
    T3,
    T4,
    T5,
    T6,
    T7,
    T8,
    T9,
    T10,
    R1,
    R2,
    R3,
    R4,
    B10,
    B9,
    B8,
    B7,
    B6,
    B5,
    B4,
    B3,
    B2,
    B1,
    L4,
    L3,
    L2,
    L1
};
struct ButtonData
{
    OSB_NUMS buttonIndex_; //e.g. 1 - 8 -> OSB 1 to 8
};
//enums END

#define NULL 0

namespace PAGE
{
    //TYC 20220301: this is the parent class of all the pages
    class PageControlMgr
    {
    public:

        // Virtual functions
        PageControlMgr(void);
        virtual ~PageControlMgr(void);

        // functions to be implemented by child classes
        virtual void doEndInit() = 0;
        virtual void showRequiredWindows();
        virtual void managePage() = 0;
        virtual void displaySymbol() = 0;
        virtual void displayStatus() = 0;
        virtual void manageOsb();
        virtual BOOL handleT1(){return FALSE;}
        virtual BOOL handleT2(){return FALSE;}
        virtual BOOL handleT3(){return FALSE;}
        virtual BOOL handleT4(){return FALSE;}
        virtual BOOL handleT5(){return FALSE;}
        virtual BOOL handleT6(){return FALSE;}
        virtual BOOL handleT7(){return FALSE;}
        virtual BOOL handleT8(){return FALSE;}
        virtual BOOL handleT9(){return FALSE;}
        virtual BOOL handleT10(){ return FALSE; }
        virtual BOOL handleR1(){ return FALSE; }
        virtual BOOL handleR2() { return FALSE; }
        virtual BOOL handleR3() { return FALSE; }
        virtual BOOL handleR4() { return FALSE; }
        virtual BOOL handleL1() { return FALSE; }
        virtual BOOL handleL2() { return FALSE; }
        virtual BOOL handleL3() { return FALSE; }
        virtual BOOL handleL4() { return FALSE; }
        virtual BOOL handleB1();
        virtual BOOL handleB2();
        virtual BOOL handleB3() { return FALSE; }
        virtual BOOL handleB4() { return FALSE; }
        virtual BOOL handleB5() { return FALSE; }
        virtual BOOL handleB6() { return FALSE; }
        virtual BOOL handleB7();
        virtual BOOL handleB8();
        virtual BOOL handleB9() { return FALSE; }
        virtual BOOL handleB10() { return FALSE; }

        static void handleOSB(HWND button_handle);
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        static int DrawMainWindow(void* pParam);
        static void DrawKeyboard(void);
        static HRESULT DrawButtonTextAndColor(HWND handle);
        static DISPLAY_CONFIG getDisplayConfig(void);
        static void sendKey(char c);

        // Intialization functions
        static void initializeMainWindowThread(void);

        static void sendMessageToScreenToDrawSymbols(void);
        static void sendMessageToScreenToDrawOsbLegends(void);

        static void initializeComplete();

        static void hideAllWindows(void);

        static void processMessageFromPrimaryDisplay(void);

        static bool checkWhetherToHandleOsb(void);

        static inline OSB_NUMS getButtonPressedData(void);

        static inline void setButtonPressedData(int buttonData);

        //get objects
        static inline DcmFailure& getDcmFailureObject(void);

        static inline void setMasterPageIndex(const unsigned short int);
        static inline unsigned short int getMasterPageIndex(void);

        static inline void setPageStatus(const unsigned char option);

        static inline unsigned char getPageStatus(void);

        //set and get functions

    protected:

        //to store the current selected page, to perform page switching
        static unsigned short int masterPageIndex_;

        //e.g. 1 = initialization , 2 = operational
        static unsigned char pageState_;
        //static unsigned char secondaryDispState_;

        // holds structure of incoming button press
        static OSB_NUMS buttonData_;

    private:

        // class to handle failures
        static DcmFailure dcmFailureObject_;



        // add other supporting classes / objects to 
        // contain implementation details

        // buffers to store raw incoming message from display hardware
        // may not be applicable for Windows application
        //char PageControlMgr::primaryIncomingRs422MessageBuffer_[2048] = { 0 };
        //char DisplayControlMgr::secondaryIncomingRs422MessageBuffer_[2048] = { 0 };



    }; //end of class DisplayControlMgr 

    DcmFailure& PageControlMgr::getDcmFailureObject(void)
    {
        return dcmFailureObject_;
    }

    void PageControlMgr::setMasterPageIndex(const unsigned short int option)
    {
        masterPageIndex_ = option;
    }

    unsigned short int PageControlMgr::getMasterPageIndex(void)
    {
        return masterPageIndex_;
    }
    
    void PageControlMgr::setPageStatus(const unsigned char option)
    {
        pageState_ = option;
    }

    unsigned char PageControlMgr::getPageStatus(void)
    {
        return pageState_;
    }

    OSB_NUMS PageControlMgr::getButtonPressedData(void)
    {
        return buttonData_;
    }

    void PageControlMgr::setButtonPressedData(const int buttonData)
    {
        buttonData_ = static_cast<OSB_NUMS>(buttonData);
    }
} // namespace


#endif 
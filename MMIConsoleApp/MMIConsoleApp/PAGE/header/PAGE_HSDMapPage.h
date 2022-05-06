//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: PAGE_HSDMapPage.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file declaration
// entry point for HSD MAP Page
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#ifndef PAGE_HSDMAPPAGE_H
#define PAGE_HSDMAPPAGE_H

#include <../PAGE/header/PAGE_pageControlMgr.h>


extern int nInitialized;
extern int nRendering;
extern int nFrameWidth;
extern int nFrameHeight;
extern HDC hDevice;
extern HGLRC hContext;

namespace PAGE
{
    //*****************************************************************************
    // Class Definitions
    //*****************************************************************************
    class HSDMapPage : public PageControlMgr
    {
    public:
        //****************************************************************************
        //* Function Name  : void HSDMapPage()
        //* Purpose        : Constructor
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        HSDMapPage(void);

        //****************************************************************************
        //* Function Name  : void ~HSDMapPage()
        //* Purpose        : Destructor
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual ~HSDMapPage(void);

        //****************************************************************************
        //* Function Name  : void doEndInit()
        //* Purpose        : Do end of initialzation 
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
       //****************************************************************************
        virtual void doEndInit();

        //****************************************************************************
        //* Function Name  : void managePage()
        //* Purpose        : Manage Page refresh and rendering
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual void managePage();

        //****************************************************************************
        //* Function Name  : showRequiredWindows()
        //* Purpose        : Show/Hide required Windows
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual void showRequiredWindows();

        //****************************************************************************
        //* Function Name  : void displaySymbol()
        //* Purpose        : Redraw of symbols
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual void displaySymbol();

        virtual void displayStatus();

        //****************************************************************************
        //* Function Name  : BOOL handleR1()
        //* Purpose        : Handle OSB R1 functions, override Parent Class
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual BOOL handleR1();

        //****************************************************************************
        //* Function Name  : BOOL handleR2()
        //* Purpose        : Handle OSB R2 functions, override Parent Class
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual BOOL handleR2();

        //****************************************************************************
        //* Function Name  : BOOL handleR3()
        //* Purpose        : Handle OSB R3 functions, override Parent Class
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual BOOL handleR3();

        //****************************************************************************
        //* Function Name  : BOOL handleB1()
        //* Purpose        : Handle OSB B1 functions, override Parent Class
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual BOOL handleB1();

        //****************************************************************************
        //* Function Name  : BOOL handleB2()
        //* Purpose        : Handle OSB B2 functions, override Parent Class
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual BOOL handleB2();

        //****************************************************************************
        //* Function Name  : BOOL handleL1()
        //* Purpose        : Handle OSB L1 functions, override Parent Class
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual BOOL handleL1();

        //****************************************************************************
        //* Function Name  : BOOL handleL3()
        //* Purpose        : Handle OSB L3 functions, override Parent Class
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        virtual BOOL handleL3();

    private:

        void processOsb1Legend();  //check and show legend
        void processOsb2Legend();  //check and show legend
        void processOsb3Legend();  //check and show legend
        void processOsb4Legend();  //check and show legend
        void processOsb5Legend();  //check and show legend
        void processOsb6Legend();  //check and show legend
        void processOsb7Legend();  //check and show legend
        void processOsb8Legend();

        //check and show legend
        void processAndShowImportantStrings();
    };
}



#endif
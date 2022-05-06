//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved
//
// FILE NAME: Page_pageControlMgr.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// entry point for Page Control Manager (Parent Class of Pages)
//
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              :
//   MODIFIER          :
//   MODIFICATION      :
//
//******************************************************************************
#include <../PAGE/header/PAGE_pageControlMgr.h>
#include <../PAGE/header/handles.h>

extern DISPLAY_CONFIG sDisplay_config;

const wchar_t alphabet[] = L"Q\0W\0E\0R\0T\0Y\0U\0I\0O\0P\0A\0S\0D\0F\0G\0H\0J\0K\0L\0Z\0X\0C\0V\0B\0N\0M";
const wchar_t number[] = L"1\0002\0003\0004\0005\0006\0007\0008\0009\0000";

namespace PAGE {

    DcmFailure PageControlMgr::dcmFailureObject_;
    unsigned short int PageControlMgr::masterPageIndex_ = 0;
    unsigned char PageControlMgr::pageState_ = 0;
    OSB_NUMS PageControlMgr::buttonData_ = INVALID_OSB;

    //DISPLAY_CONFIG sDisplay_config;

    HINSTANCE hInstance{};
    //HINSTANCE hPrevInstance{};

    PageControlMgr::PageControlMgr(void)
    {
        getDisplayConfig();
        masterPageIndex_ = 0;
        pageState_ = 1;
        buttonData_ = INVALID_OSB;
    }

    PageControlMgr::~PageControlMgr(void)
    {
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
    void PageControlMgr::showRequiredWindows()
    {
        ShowWindow(BUTTON_BOTTOM[0], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[1], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[2], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[3], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[4], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[5], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[6], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[7], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[8], SW_SHOW);
        ShowWindow(BUTTON_BOTTOM[9], SW_SHOW);
    }

    void PageControlMgr::initializeMainWindowThread()
    {
        //Init Main Window
        HANDLE hThread = 0;

        // Spawn the task that creates the Window
        hThread = CreateThread(NULL, 40960, (LPTHREAD_START_ROUTINE)DrawMainWindow, 0, 0, NULL);

        if (hThread == 0)
        {
            printf("Unable to start Window Thread!\n");
            return;
        }
    }

    //****************************************************************************
    //* Function Name  : int DrawMainWindow(void* pParam)
    //* Purpose        : Draw the Main MMI Window
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    int PageControlMgr::DrawMainWindow(void* pParam)
    {
        // Register the window class.
        const wchar_t CLASS_NAME[] = L"MMIConsoleApp";

        WNDCLASS wc = { };

        wc.lpfnWndProc = PageControlMgr::WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;

        // Change main app background color
        wc.hbrBackground = CreateSolidBrush(RGB(sDisplay_config.BG_RED, sDisplay_config.BG_GREEN, sDisplay_config.BG_BLUE));

        RegisterClass(&wc);

        // Create the window.
        MAIN_WINDOW = CreateWindowEx(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            L"MMIConsoleApp",                    // Window text
            WS_POPUPWINDOW,     // Window style
            CW_USEDEFAULT, CW_USEDEFAULT,   // Position (x,y)
            sDisplay_config.WINDOW_WIDTH, sDisplay_config.WINDOW_HEIGHT, // Size
            NULL,                           // Parent window
            NULL,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );

        if (MAIN_WINDOW == NULL)
        {
            return 0;
        }

        ShowWindow(MAIN_WINDOW, SW_SHOWNORMAL);

        // Set app to always be top most layer
        SetWindowPos(
            MAIN_WINDOW,
            0,//HWND_TOPMOST,
            0, 0,
            sDisplay_config.WINDOW_WIDTH, sDisplay_config.WINDOW_HEIGHT,
            SWP_SHOWWINDOW | SWP_DRAWFRAME);

        for (INT i = 0; i < _countof(BUTTON_TOP); ++i)
        {
            BUTTON_TOP[i] = CreateWindow(
                WC_BUTTON,
                L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW | WS_CLIPSIBLINGS,
                sDisplay_config.BUTTON_TOP_POS[i].first, sDisplay_config.BUTTON_TOP_POS[i].second,
                sDisplay_config.OSB_SIZE.first, sDisplay_config.OSB_SIZE.second,
                MAIN_WINDOW,
                NULL,
                hInstance,
                NULL);

            SetWindowPos(
                BUTTON_TOP[i],
                HWND_TOPMOST,
                0, 0,
                0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }

        for (INT i = 0; i < _countof(BUTTON_LEFT); ++i)
        {
            BUTTON_LEFT[i] = CreateWindow(
                WC_BUTTON,
                L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW | WS_CLIPSIBLINGS,
                sDisplay_config.BUTTON_LEFT_POS[i].first, sDisplay_config.BUTTON_LEFT_POS[i].second,
                sDisplay_config.OSB_SIZE.first, sDisplay_config.OSB_SIZE.second,
                MAIN_WINDOW,
                NULL,
                hInstance,
                NULL);

            SetWindowPos(
                BUTTON_LEFT[i],
                HWND_TOPMOST,
                0, 0,
                0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }

        for (INT i = 0; i < _countof(BUTTON_RIGHT); ++i)
        {
            BUTTON_RIGHT[i] = CreateWindow(
                WC_BUTTON,
                L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW | WS_CLIPSIBLINGS,
                sDisplay_config.BUTTON_RIGHT_POS[i].first, sDisplay_config.BUTTON_RIGHT_POS[i].second,
                sDisplay_config.OSB_SIZE.first, sDisplay_config.OSB_SIZE.second,
                MAIN_WINDOW,
                NULL,
                hInstance,
                NULL);

            SetWindowPos(
                BUTTON_RIGHT[i],
                HWND_TOPMOST,
                0, 0,
                0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }

        for (INT i = 0; i < _countof(BUTTON_BOTTOM); ++i)
        {
            BUTTON_BOTTOM[i] = CreateWindow(
                WC_BUTTON,
                L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW | WS_CLIPSIBLINGS,
                sDisplay_config.BUTTON_BOTTOM_POS[i].first, sDisplay_config.BUTTON_BOTTOM_POS[i].second,
                sDisplay_config.OSB_SIZE.first, sDisplay_config.OSB_SIZE.second,
                MAIN_WINDOW,
                NULL,
                hInstance,
                NULL);

            SetWindowPos(
                BUTTON_BOTTOM[i],
                HWND_TOPMOST,
                0, 0,
                0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }

        DrawKeyboard();

        //// Start the Windows Message Pump
        MSG msg;
        printf("Windows thread complete.\n");

        // Main message loop:
        while (GetMessage(&msg, MAIN_WINDOW, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 0;
    }

    void PageControlMgr::DrawKeyboard(void)
    {
        INT pos_x = sDisplay_config.BUTTON_TOP_POS[0].first;
        INT pos_y = sDisplay_config.BUTTON_LEFT_POS[0].second;
        INT offset_x = 0;
        INT offset_y = 0;

        MSGBOX = CreateWindow(
            L"EDIT",
            L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            sDisplay_config.BUTTON_TOP_POS[1].first, sDisplay_config.BUTTON_TOP_POS[1].second,
            sDisplay_config.MSG_W, sDisplay_config.MSG_H,
            MAIN_WINDOW,
            0,
            NULL,
            0);

        // Set keyboard focus to Msg box
        SetFocus(MSGBOX);

        for (INT i = 0; i < BUTTON_KEYBOARD_NUMBERS.size(); ++i)
        {
            BUTTON_KEYBOARD_NUMBERS[i] = CreateWindow(
                WC_BUTTON,
                number + i + (i * 1),
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
                pos_x + offset_x, pos_y + offset_y,
                sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
                MAIN_WINDOW,
                0,
                NULL,
                NULL);
            offset_x += sDisplay_config.ALPHA_W;
        }

        // Draw Alphabet button
        offset_x = 0;
        offset_y = sDisplay_config.ALPHA_H;;
        for (INT i = 0; i < BUTTON_KEYBOARD_ALPHABET.size(); ++i)
        {
            BUTTON_KEYBOARD_ALPHABET[i] = CreateWindow(
                WC_BUTTON,
                alphabet + i + (i * 1),
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
                pos_x + offset_x, pos_y + offset_y,
                sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
                MAIN_WINDOW,
                0,
                NULL,
                NULL);
            if (i == 9) {
                offset_x = 0;
                offset_y += sDisplay_config.ALPHA_H;
            }
            else if (i == 18) {
                offset_x = 0;
                offset_y += sDisplay_config.ALPHA_H;
            }
            else {
                offset_x += sDisplay_config.ALPHA_W;
            }
        }

        // Draw backspace button
        offset_x = 9 * sDisplay_config.ALPHA_W;
        offset_y = 2 * sDisplay_config.ALPHA_H;
        BUTTON_KEYBOARD_BACKSPACE = CreateWindow(
            WC_BUTTON,
            L"BKSP",
            WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
            pos_x + offset_x, pos_y + offset_y,
            sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
            MAIN_WINDOW,
            0,
            NULL,
            NULL);

        // Draw Period button
        offset_x = 7 * sDisplay_config.ALPHA_W;
        offset_y = 3 * sDisplay_config.ALPHA_H;
        BUTTON_KEYBOARD_PERIOD = CreateWindow(
            WC_BUTTON,
            L".",
            WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
            pos_x + offset_x, pos_y + offset_y,
            sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
            MAIN_WINDOW,
            0,
            NULL,
            NULL);

        // Draw Space button
        offset_x = 8 * sDisplay_config.ALPHA_W;
        BUTTON_KEYBOARD_SPACE = CreateWindow(
            WC_BUTTON,
            L"SPC",
            WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
            pos_x + offset_x, pos_y + offset_y,
            sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
            MAIN_WINDOW,
            0,
            NULL,
            NULL);

        // Draw Enter button
        offset_x = 9 * sDisplay_config.ALPHA_W;
        BUTTON_KEYBOARD_ENTER = CreateWindow(
            WC_BUTTON,
            L"ENT",
            WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
            pos_x + offset_x, pos_y + offset_y,
            sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
            MAIN_WINDOW,
            0,
            NULL,
            NULL);
    }

    //****************************************************************************
    //* Function Name  : LRESULT CALLBACK PageMgr::WindowProc(HWND, UINT, WPARAM, LPARAM)
    //* Purpose        : Windows Form Callback function
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    LRESULT CALLBACK PageControlMgr::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_CREATE:
        {
            //HWND hwndStatic = CreateWindow(WC_STATIC, L"",
            //WS_CHILD | WS_VISIBLE | WS_BORDER,
            //100, 100, 100, 100,        // Position and dimensions; example only.
            //TAB_CTRL, NULL, hInstance,    // g_hInst is the global instance handle
            //NULL);
        }
        break;

        case WM_COMMAND:
        {
            if (HIWORD(wParam) == BN_CLICKED && checkWhetherToHandleOsb())
            {
                HWND button_handle = (HWND)lParam;
                bool flag = 0;
                for (INT i = 0; flag == 0 && i < _countof(BUTTON_TOP); ++i)
                {
                    if (button_handle == BUTTON_TOP[i])
                    {
                        flag = 1;
                    }
                }
                for (INT i = 0; flag == 0 && i < _countof(BUTTON_LEFT); ++i)
                {
                    if (button_handle == BUTTON_LEFT[i])
                    {
                        flag = 1;
                    }
                }
                for (INT i = 0; flag == 0 && i < _countof(BUTTON_RIGHT); ++i)
                {
                    if (button_handle == BUTTON_RIGHT[i])
                    {
                        flag = 1;
                    }
                }
                for (INT i = 0; flag == 0 && i < _countof(BUTTON_BOTTOM); ++i)
                {
                    if (button_handle == BUTTON_BOTTOM[i])
                    {
                        flag = 1;
                    }
                }
                if (flag == 1)
                {
                    // Handle button presses
                    handleOSB(button_handle);
                    //RedrawWindow(MAIN_WINDOW, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
                }

                else
                {
                    if (button_handle == BUTTON_KEYBOARD_BACKSPACE)
                    {
                        sendKey(8); // Ascii decimal value for backspace is 8
                    }
                    else if (button_handle == BUTTON_KEYBOARD_SPACE)
                    {
                        sendKey(32); // Ascii decimal value for space is 32
                    }
                    else if (button_handle == BUTTON_KEYBOARD_ENTER)
                    {
                        sendKey(10); // Ascii decimal value for enter is 10
                    }
                    else
                    {
                        CHAR text[2];
                        GetWindowTextA(button_handle, text, 2);
                        sendKey(text[0]);
                    }
                }
                flag = 0;
            }
        }
        break;

        case WM_CTLCOLORBTN:
        {
            // Change button text, fonts and background colors
            return DrawButtonTextAndColor((HWND)lParam);
        }
        break;

        case WM_CTLCOLOREDIT:
        {
            //// Change Msg box text and background colors
            HDC hdc = (HDC)wParam;
            SetTextColor(hdc, RGB(sDisplay_config.TEXT_RED, sDisplay_config.TEXT_GREEN, sDisplay_config.TEXT_BLUE));
            SetBkColor(hdc, RGB(sDisplay_config.BUTTON_RED, sDisplay_config.BUTTON_GREEN, sDisplay_config.BUTTON_BLUE));
            return (INT_PTR)CreateSolidBrush(RGB(sDisplay_config.BUTTON_RED, sDisplay_config.BUTTON_GREEN, sDisplay_config.BUTTON_BLUE));
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
        return 0;
        break;

        case WM_CHAR:
            break;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    HRESULT PageControlMgr::DrawButtonTextAndColor(HWND button_handle)
    {
        HDC hdc = GetDC(button_handle);
        HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        LOGFONT logfont;
        GetObject(hFont, sizeof(LOGFONT), &logfont);

        RECT crect;
        HBRUSH brush;
        COLORREF background_color = RGB(sDisplay_config.BUTTON_RED, sDisplay_config.BUTTON_GREEN, sDisplay_config.BUTTON_BLUE);
        COLORREF text_color = RGB(sDisplay_config.TEXT_RED, sDisplay_config.TEXT_GREEN, sDisplay_config.TEXT_BLUE);

        BOOL flag = 0;
        for (INT i = 0; flag == 0 && i < _countof(BUTTON_TOP); ++i)
        {
            if (button_handle == BUTTON_TOP[i])
            {
                flag = 1;
            }
        }
        for (INT i = 0; flag == 0 && i < _countof(BUTTON_LEFT); ++i)
        {
            if (button_handle == BUTTON_LEFT[i])
            {
                flag = 1;
            }
        }
        for (INT i = 0; flag == 0 && i < _countof(BUTTON_RIGHT); ++i)
        {
            if (button_handle == BUTTON_RIGHT[i])
            {
                flag = 1;
            }
        }
        for (INT i = 0; flag == 0 && i < _countof(BUTTON_BOTTOM); ++i)
        {
            if (button_handle == BUTTON_BOTTOM[i])
            {
                flag = 1;
            }
        }

        if (flag == 1)
        {
            if (button_handle == BUTTON_RIGHT[0] || button_handle == BUTTON_RIGHT[2] ||
                button_handle == BUTTON_LEFT[0] || button_handle == BUTTON_LEFT[2])
            {
                logfont.lfHeight = 2 * sDisplay_config.OSB_TEXT_SIZE;
            }
            else
            {
                logfont.lfHeight = sDisplay_config.OSB_TEXT_SIZE;
            }
        }
        else
        {
            logfont.lfHeight = sDisplay_config.KEYBOARD_TEXT_SIZE;
        }

        flag = 0;
        logfont.lfWeight = 400; // Font weight (100 - 900) in multiples of 100
        size_t newsize = strlen(sDisplay_config.TEXT_STYLE) + 1;
        wchar_t* wcstring = new wchar_t[newsize];
        // Convert char* string to a wchar_t* string.
        size_t convertedChars = 0;
        mbstowcs_s(&convertedChars, wcstring, newsize, sDisplay_config.TEXT_STYLE, _TRUNCATE);

        _tcscpy_s(logfont.lfFaceName, wcstring);
        HFONT hNewFont = CreateFontIndirect(&logfont);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont);

        GetClientRect(button_handle, &crect);
        SetBkColor(hdc, background_color);
        SetTextColor(hdc, text_color);

        WCHAR str[10] = L"";

        if (PageControlMgr::getMasterPageIndex() == static_cast<unsigned short>(HSDMAP_PAGE))
        {
            if (button_handle == BUTTON_BOTTOM[0])
            {
                wcscpy_s(str, L"HSD");
            }
            else if (button_handle == BUTTON_BOTTOM[1])
            {
                wcscpy_s(str, L"MAP");
            }
            else if (button_handle == BUTTON_BOTTOM[2])
            {
                wcscpy_s(str, L"DCLT");
            }
            else if (button_handle == BUTTON_BOTTOM[3])
            {
                wcscpy_s(str, L"NET");
            }
            else if (button_handle == BUTTON_BOTTOM[4])
            {
                wcscpy_s(str, L"SYS");
            }
            else if (button_handle == BUTTON_BOTTOM[5])
            {
                wcscpy_s(str, L"MSG");
            }
            else if (button_handle == BUTTON_BOTTOM[6])
            {
                wcscpy_s(str, L"EO");
            }
            else if (button_handle == BUTTON_BOTTOM[7])
            {
                wcscpy_s(str, L"TXT");
            }
            else if (button_handle == BUTTON_BOTTOM[8])
            {
                wcscpy_s(str, L"RPT");
            }
            else if (button_handle == BUTTON_RIGHT[0])
            {
                wcscpy_s(str, L"\U0001F845");
            }
            else if (button_handle == BUTTON_RIGHT[1])
            {
                wcscpy_s(str, L"RNG");
            }
            else if (button_handle == BUTTON_RIGHT[2])
            {
                wcscpy_s(str, L"\U0001F847");
            }
            else if (button_handle == BUTTON_LEFT[0])
            {
                wcscpy_s(str, L"+");
            }
            else if (button_handle == BUTTON_LEFT[1])
            {
                wcscpy_s(str, L"SCALE");
            }
            else if (button_handle == BUTTON_LEFT[2])
            {
                wcscpy_s(str, L"-");
            }
            else if (button_handle == BUTTON_TOP[0])
            {
                wcscpy_s(str, L"STATUS");
            }
            else if (button_handle == BUTTON_TOP[9])
            {
                wcscpy_s(str, L"PFL");
            }
        }
        else if (PageControlMgr::getMasterPageIndex() == static_cast<unsigned short>(TEXT_PAGE))
        {
            if (button_handle == BUTTON_BOTTOM[0])
            {
                wcscpy_s(str, L"RTN");
            }
            else if (button_handle == BUTTON_BOTTOM[8])
            {
                wcscpy_s(str, L"PAD");
            }
            else if (button_handle == BUTTON_BOTTOM[9])
            {
                wcscpy_s(str, L"SEND");
            }
            else if (button_handle == BUTTON_TOP[0])
            {
                wcscpy_s(str, L"STATUS");
            }
            else if (button_handle == BUTTON_TOP[9])
            {
                wcscpy_s(str, L"PFL");
            }
            else
            {
                GetWindowText(button_handle, str, 10);
            }
        }
        DrawText(hdc, str, wcslen(str), &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        brush = CreateSolidBrush(background_color);

        // Always select the old font back into the DC
        SelectObject(hdc, hOldFont);

        return (HRESULT)brush;
    }

    //****************************************************************************
    //* Function Name  : DISPLAY_CONFIG getDisplayConfig(void)
    //* Purpose        : Update struct with config information
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    DISPLAY_CONFIG PageControlMgr::getDisplayConfig(void)
    {
        std::string configfile = "MMI_Config.xml";

        // Get config info from XML file.
        sDisplay_config = XmlSerializer::parseDisplayConfigXml(XmlSerializer::readXml(configfile));

        return sDisplay_config;
    }

    //****************************************************************************
    //* Function Name  : handleOSB(int)
    //* Purpose        : Handle OSB presses and send to child page to process
    //*
    //* Pre-Condition  : None
    //* Post-Condition : None
    //* Access         : Public
    //* Note           :
    //****************************************************************************
    void  PageControlMgr::handleOSB(HWND button_handle)
    {
        if (button_handle == BUTTON_TOP[0])
            PageControlMgr::setButtonPressedData(T1);
        else if (button_handle == BUTTON_TOP[1])
            PageControlMgr::setButtonPressedData(T2);
        else if (button_handle == BUTTON_TOP[2])
            PageControlMgr::setButtonPressedData(T3);
        else if (button_handle == BUTTON_TOP[3])
            PageControlMgr::setButtonPressedData(T4);
        else if (button_handle == BUTTON_TOP[4])
            PageControlMgr::setButtonPressedData(T5);
        else if (button_handle == BUTTON_TOP[5])
            PageControlMgr::setButtonPressedData(T6);
        else if (button_handle == BUTTON_TOP[6])
            PageControlMgr::setButtonPressedData(T7);
        else if (button_handle == BUTTON_TOP[7])
            PageControlMgr::setButtonPressedData(T8);
        else if (button_handle == BUTTON_TOP[8])
            PageControlMgr::setButtonPressedData(T9);
        else if (button_handle == BUTTON_TOP[9])
            PageControlMgr::setButtonPressedData(T10);
        else if (button_handle == BUTTON_LEFT[0])
            PageControlMgr::setButtonPressedData(L1);
        else if (button_handle == BUTTON_LEFT[1])
            PageControlMgr::setButtonPressedData(L2);
        else if (button_handle == BUTTON_LEFT[2])
            PageControlMgr::setButtonPressedData(L3);
        else if (button_handle == BUTTON_LEFT[3])
            PageControlMgr::setButtonPressedData(L4);
        else if (button_handle == BUTTON_RIGHT[0])
            PageControlMgr::setButtonPressedData(R1);
        else if (button_handle == BUTTON_RIGHT[1])
            PageControlMgr::setButtonPressedData(R2);
        else if (button_handle == BUTTON_RIGHT[2])
            PageControlMgr::setButtonPressedData(R3);
        else if (button_handle == BUTTON_RIGHT[3])
            PageControlMgr::setButtonPressedData(R4);
        else if (button_handle == BUTTON_BOTTOM[0])
            PageControlMgr::setButtonPressedData(B1);
        else if (button_handle == BUTTON_BOTTOM[1])
            PageControlMgr::setButtonPressedData(B2);
        else if (button_handle == BUTTON_BOTTOM[2])
            PageControlMgr::setButtonPressedData(B3);
        else if (button_handle == BUTTON_BOTTOM[3])
            PageControlMgr::setButtonPressedData(B4);
        else if (button_handle == BUTTON_BOTTOM[4])
            PageControlMgr::setButtonPressedData(B5);
        else if (button_handle == BUTTON_BOTTOM[5])
            PageControlMgr::setButtonPressedData(B6);
        else if (button_handle == BUTTON_BOTTOM[6])
            PageControlMgr::setButtonPressedData(B7);
        else if (button_handle == BUTTON_BOTTOM[7])
            PageControlMgr::setButtonPressedData(B8);
        else if (button_handle == BUTTON_BOTTOM[8])
            PageControlMgr::setButtonPressedData(B9);
        else if (button_handle == BUTTON_BOTTOM[9])
            PageControlMgr::setButtonPressedData(B10);
        else
            PageControlMgr::setButtonPressedData(INVALID_OSB);
    }

    void PageControlMgr::processMessageFromPrimaryDisplay(void)
    {
        //background: original project reads RS422 data
        //and check the meaning of the messages
        //e.g. for OSB button press, what button was pressed

        //call API to get incoming data from Primary Display

        //Process
    }

    void PageControlMgr::sendMessageToScreenToDrawSymbols()
    {
        //common implmentation to draw symbols on screen

        //background: in original project,
        //we build an outgoing rs422 message
        //and call rs422 API to send to the hardware
    }

    void PageControlMgr::sendMessageToScreenToDrawOsbLegends()
    {
        //common implmentation to draw legends on screen

        //background: in original project,
        //we build an outgoing rs422 message
        //and call rs422 API to send to the hardware
    }

    void PageControlMgr::initializeComplete()
    {
        if (pageState_ == INITIALIZATION_STATE)
        {
            //if successful, set to Operational state
            //to shift this logic somewhere else if required
            pageState_ = OPERATIONAL_STATE;
        }
    }

    void PageControlMgr::hideAllWindows(void)
    {
        for (int i = 0; i < 10; i++)
        {
            ShowWindow(BUTTON_TOP[i], SW_HIDE);
            ShowWindow(BUTTON_BOTTOM[i], SW_HIDE);
        }

        for (int i = 0; i < 4; i++)
        {
            ShowWindow(BUTTON_LEFT[i], SW_HIDE);
            ShowWindow(BUTTON_RIGHT[i], SW_HIDE);
        }

        ShowWindow(MSGBOX, SW_HIDE);
        ShowWindow(DMM_WINDOW, SW_HIDE);
    }

    bool PageControlMgr::checkWhetherToHandleOsb(void)
    {
        bool returnValue = false;

        //return true if Display(s) is operational
        if (pageState_ == OPERATIONAL_STATE)
        {
            returnValue = true;
        }
        else
        {
            returnValue = false;
        }

        return returnValue;
    }

    void PageControlMgr::manageOsb()
    {
        BOOL requiredPageChange = FALSE;
        //Handle Button Press and set Button status to default(invalid)
        switch (PageControlMgr::getButtonPressedData())
        {
        case static_cast<unsigned int>(B1):
            requiredPageChange = handleB1();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B2):
            requiredPageChange = handleB2();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B3):
            requiredPageChange = handleB3();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B4):
            requiredPageChange = handleB4();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B5):
            requiredPageChange = handleB5();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B6):
            requiredPageChange = handleB6();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B7):
            requiredPageChange = handleB7();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B8):
            requiredPageChange = handleB8();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B9):
            requiredPageChange = handleB9();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(B10):
            requiredPageChange = handleB10();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T1):
            requiredPageChange = handleT1();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T2):
            requiredPageChange = handleT2();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T3):
            requiredPageChange = handleT3();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T4):
            requiredPageChange = handleT4();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T5):
            requiredPageChange = handleT5();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T6):
            requiredPageChange = handleT6();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T7):
            requiredPageChange = handleT7();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T8):
            requiredPageChange = handleT8();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T9):
            requiredPageChange = handleT9();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(T10):
            requiredPageChange = handleT10();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(R1):
            requiredPageChange = handleR1();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(R2):
            requiredPageChange = handleR2();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(R3):
            requiredPageChange = handleR3();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(R4):
            requiredPageChange = handleR4();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(L1):
            requiredPageChange = handleL1();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(L2):
            requiredPageChange = handleL2();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(L3):
            requiredPageChange = handleL3();
            setButtonPressedData(INVALID_OSB);
            break;
        case static_cast<unsigned int>(L4):
            requiredPageChange = handleL4();
            setButtonPressedData(INVALID_OSB);
            break;
        default:// Invalid OSB
            //PageControlMgr::getDcmFailureObject().handleInvalidOsb();
            break;
        }

        if (requiredPageChange)
        {
            RedrawWindow(MAIN_WINDOW, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        }
    }

    BOOL PageControlMgr::handleB1()
    {
        //switch to HSD page
        PageControlMgr::setMasterPageIndex(static_cast<unsigned short>(HSDMAP_PAGE));
        return TRUE;
    }

    BOOL PageControlMgr::handleB2()
    {
        //switch to MAP page
        PageControlMgr::setMasterPageIndex(static_cast<unsigned short>(HSDMAP_PAGE));
        return TRUE;
    }

    BOOL PageControlMgr::handleB7()
    {
        //switch to EO page
        PageControlMgr::setMasterPageIndex(static_cast<unsigned short>(EO_PAGE)); 
        return TRUE;
    }

    BOOL PageControlMgr::handleB8()
    {
        //switch to TEXT page
        PageControlMgr::setMasterPageIndex(static_cast<unsigned short>(TEXT_PAGE));
        return TRUE;
    }

    void PageControlMgr::sendKey(CHAR c)
    {
        HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        LOGFONT logfont;
        GetObject(hFont, sizeof(LOGFONT), &logfont);
        HDC hdc = GetDC(MSGBOX);

        logfont.lfHeight = sDisplay_config.KEYBOARD_TEXT_SIZE;
        logfont.lfWeight = 400; // Font weight (100 - 900) in multiples of 100
        size_t newsize = strlen(sDisplay_config.TEXT_STYLE) + 1;
        wchar_t* wcstring = new wchar_t[newsize];
        // Convert char* string to a wchar_t* string.
        size_t convertedChars = 0;
        mbstowcs_s(&convertedChars, wcstring, newsize, sDisplay_config.TEXT_STYLE, _TRUNCATE);

        _tcscpy_s(logfont.lfFaceName, wcstring);
        HFONT hNewFont = CreateFontIndirect(&logfont);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont);

        SendMessage(MSGBOX, WM_SETFONT, (WPARAM)hNewFont, TRUE);
        PostMessage(MSGBOX, WM_CHAR, c, 0);
        SetFocus(MSGBOX);

        // Always select the old font back into the DC
        SelectObject(hdc, hOldFont);
    }
} // namespace
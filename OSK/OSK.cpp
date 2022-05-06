#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <TCHAR.H>
#include "structs.h"
#include "XmlSerializer.h"

// Update struct with config information
int getDisplayConfig(void);
void sendKey(char c);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND MsgBox;
HWND alphabet_buttons[26];
HWND number_buttons[10];
HWND period_button;
HWND enter_button;
HWND space_button;
HWND backspace_button;
HFONT hNewFont;
HFONT hOldFont;

const wchar_t alphabet[] = L"Q\0W\0E\0R\0T\0Y\0U\0I\0O\0P\0A\0S\0D\0F\0G\0H\0J\0K\0L\0Z\0X\0C\0V\0B\0N\0M";
const wchar_t number[] = L"1\0002\0003\0004\0005\0006\0007\0008\0009\0000";

DISPLAY_CONFIG sDisplay_config;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Main App";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    // Update struct with config information
    getDisplayConfig();

    // Change main app background color
    wc.hbrBackground = CreateSolidBrush(RGB(sDisplay_config.BG_RED, sDisplay_config.BG_GREEN, sDisplay_config.BG_BLUE));

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Main App",                    // Window text
        WS_SYSMENU | WS_EX_OVERLAPPEDWINDOW,     // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position (x,y)
        sDisplay_config.WINDOW_W, sDisplay_config.WINDOW_H, // Size
        NULL,                           // Parent window    
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    if (hwnd == 0)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int pos_x = 0,
        pos_y = 0;
    int offset_x = 0,
        offset_y = 0;

    switch (uMsg)
    {
        case WM_CREATE:
        {
            // Set app to always be top most layer
            SetWindowPos(
                hwnd,
                static_cast<HWND>(HWND_TOPMOST),
                0, 0,
                sDisplay_config.WINDOW_W, sDisplay_config.WINDOW_H,
                SWP_SHOWWINDOW | SWP_DRAWFRAME);

            // Shift offset and draw number keys
            offset_x = sDisplay_config.SPACE_W;
            offset_y = 2 * sDisplay_config.SPACE_H + sDisplay_config.MSG_H;
            for (int i = 0; i < 10; ++i) {
                number_buttons[i] = CreateWindow(
                    L"BUTTON",
                    number + i + (i * 1),
                    WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
                    pos_x + offset_x, pos_y + offset_y,
                    sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
                    hwnd,
                    0,
                    NULL,
                    NULL);
                offset_x += sDisplay_config.ALPHA_W + sDisplay_config.SPACE_W;
            }

            // Shift offset and draw alphabet keys
            offset_x = sDisplay_config.SPACE_W;
            offset_y = 1 * sDisplay_config.ALPHA_H + 3 * sDisplay_config.SPACE_H + sDisplay_config.MSG_H;
            for (int i = 0; i < 26; ++i) {
                alphabet_buttons[i] = CreateWindow(
                    L"BUTTON",
                    alphabet + i + (i * 1),
                    WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
                    pos_x + offset_x, pos_y + offset_y,
                    sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
                    hwnd,
                    0,
                    NULL,
                    NULL);
                if (i == 9) {
                    offset_x = sDisplay_config.SPACE_W + 0.5 * sDisplay_config.ALPHA_W;
                    offset_y += sDisplay_config.ALPHA_H + sDisplay_config.SPACE_H;
                }
                else if (i == 18) {
                    offset_x = 2 * sDisplay_config.SPACE_W + 1.5 * sDisplay_config.ALPHA_W;
                    offset_y += sDisplay_config.ALPHA_H + sDisplay_config.SPACE_H;
                }
                else {
                    offset_x += sDisplay_config.ALPHA_W + sDisplay_config.SPACE_W;
                }
            }

            // Shift offset and draw period symbol
            offset_x = sDisplay_config.SPACE_W + 0.5 * sDisplay_config.ALPHA_W;
            offset_y = 3 * sDisplay_config.ALPHA_H + 5 * sDisplay_config.SPACE_H + sDisplay_config.MSG_H;
            period_button = CreateWindow(
                L"BUTTON",
                L".",
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
                pos_x + offset_x, pos_y + offset_y,
                sDisplay_config.ALPHA_W, sDisplay_config.ALPHA_H,
                hwnd,
                NULL,
                NULL,
                0);

            // Shift offset and draw backspace key
            offset_x = 9 * sDisplay_config.SPACE_W + 8.5 * sDisplay_config.ALPHA_W;
            offset_y = 3 * sDisplay_config.ALPHA_H + 5 * sDisplay_config.SPACE_H + sDisplay_config.MSG_H;
            backspace_button = CreateWindow(
                L"BUTTON",
                L"Backspace",
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
                pos_x + offset_x, pos_y + offset_y,
                1.5 * sDisplay_config.ALPHA_W + sDisplay_config.SPACE_W, sDisplay_config.ALPHA_H,
                hwnd,
                0,
                NULL,
                0);

            // Shift offset and draw space key
            offset_x = 2 * sDisplay_config.SPACE_W + 1.5 * sDisplay_config.ALPHA_W;
            offset_y = 4 * sDisplay_config.ALPHA_H + 6 * sDisplay_config.SPACE_H + sDisplay_config.MSG_H;
            space_button = CreateWindow(
                L"BUTTON",
                L"Space",
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
                pos_x + offset_x, pos_y + offset_y,
                7 * sDisplay_config.ALPHA_W + 6 * sDisplay_config.SPACE_W, sDisplay_config.ALPHA_H,
                hwnd,
                0,
                NULL,
                NULL);

            // Shift offset and draw enter key
            offset_x = 9 * sDisplay_config.SPACE_W + 8.5 * sDisplay_config.ALPHA_W;
            offset_y = 4 * sDisplay_config.ALPHA_H + 6 * sDisplay_config.SPACE_H + sDisplay_config.MSG_H;
            enter_button = CreateWindow(
                L"BUTTON",
                L"Enter",
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
                pos_x + offset_x, pos_y + offset_y,
                1.5 * sDisplay_config.ALPHA_W + sDisplay_config.SPACE_W, sDisplay_config.ALPHA_H,
                hwnd,
                0,
                NULL,
                0);

            // Shift offset and draw message box
            offset_x = sDisplay_config.SPACE_W;
            offset_y = sDisplay_config.SPACE_H;
            MsgBox = CreateWindow(
                L"EDIT",
                L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                pos_x + offset_x, pos_y + offset_y,
                sDisplay_config.MSG_W, sDisplay_config.MSG_H,
                hwnd,
                0,
                NULL,
                0);

            // Set keyboard focus to Msg box
            SetFocus(MsgBox);

            SendMessage(number_buttons[0], WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        }
            break;

        case WM_COMMAND:
        {
            if (HIWORD(wParam) == BN_CLICKED)
            {
                if (lParam == reinterpret_cast<LPARAM>(backspace_button)) 
                {
                    sendKey(8); // Ascii decimal value for backspace is 8
                }
                else if (lParam == reinterpret_cast<LPARAM>(space_button))
                {
                    sendKey(32); // Ascii decimal value for space is 32
                }
                else if (lParam == reinterpret_cast<LPARAM>(enter_button))
                {
                    sendKey(10); // Ascii decimal value for enter is 10
                }
                else
                {
                    CHAR text[2];
                    GetWindowTextA((HWND)lParam, text, 2);
                    //::MessageBoxA(hwnd, text, text, MB_OK);
                    sendKey(text[0]);
                }
            }
        }
            break;

        case WM_CTLCOLORBTN:
        {
            // Change button text, fonts and background colors
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            LOGFONT logfont;
            GetObject(hFont, sizeof(LOGFONT), &logfont);
            
            RECT crect;
            HBRUSH brush;
            COLORREF background_color = RGB(sDisplay_config.BUTTON_RED, sDisplay_config.BUTTON_GREEN, sDisplay_config.BUTTON_BLUE);
            HDC hdc = (HDC)wParam;
            HWND button_handle = (HWND)lParam;
            
            logfont.lfHeight = sDisplay_config.TEXT_SIZE;
            logfont.lfWeight = 400; // Font weight (100 - 900) in multiples of 100
            size_t newsize = strlen(sDisplay_config.TEXT_STYLE) + 1;
            wchar_t* wcstring = new wchar_t[newsize];
            // Convert char* string to a wchar_t* string.
            size_t convertedChars = 0;
            mbstowcs_s(&convertedChars, wcstring, newsize, sDisplay_config.TEXT_STYLE, _TRUNCATE);

            _tcscpy_s(logfont.lfFaceName, wcstring);
            hNewFont = CreateFontIndirect(&logfont);
            hOldFont = (HFONT)SelectObject(hdc, hNewFont);

            GetClientRect(button_handle, &crect);
            SetBkColor(hdc, background_color);
            SetTextColor(hdc, RGB(sDisplay_config.TEXT_RED, sDisplay_config.TEXT_GREEN, sDisplay_config.TEXT_BLUE));

            if (button_handle == backspace_button) DrawText(hdc, L"Backspace", _countof(L"Backspace") - 1, &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            else if (button_handle==space_button) DrawText(hdc, L"Space", _countof(L"Space") - 1, &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            else if (button_handle==enter_button) DrawText(hdc, L"Enter", _countof(L"Enter") - 1, &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            else
            {   
                CHAR text[2];
                GetWindowTextA((HWND)lParam, text, 2);
                DrawText(hdc, (LPCWSTR)text, _countof(text) - 1, &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            }

            brush = CreateSolidBrush(background_color);

            // Always select the old font back into the DC
            SelectObject(hdc, hOldFont);

            return (HRESULT)brush;
        }
            break;

        case WM_CTLCOLOREDIT:
        {
            // Change Msg box text and background colors
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

            EndPaint(hwnd, &ps);
        }
        return 0;
        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Update struct with config information
int getDisplayConfig(void) {
    std::string configfile = "Keyboard_Config.xml";

    // Get config info from XML file.    
    sDisplay_config = XmlSerializer::parseDisplayConfigXml(XmlSerializer::readXml(configfile));

    return 1;
}

void sendKey(char c)
{   
    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    LOGFONT logfont;
    GetObject(hFont, sizeof(LOGFONT), &logfont);
    HDC hdc = GetDC(MsgBox);

    logfont.lfHeight = sDisplay_config.TEXT_SIZE;
    logfont.lfWeight = 400; // Font weight (100 - 900) in multiples of 100
	size_t newsize = strlen(sDisplay_config.TEXT_STYLE) + 1;
    wchar_t* wcstring = new wchar_t[newsize];
    // Convert char* string to a wchar_t* string.
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, sDisplay_config.TEXT_STYLE, _TRUNCATE);

    _tcscpy_s(logfont.lfFaceName, wcstring);
    hNewFont = CreateFontIndirect(&logfont);
    hOldFont = (HFONT)SelectObject(hdc, hNewFont);

    SendMessage(MsgBox, WM_SETFONT, (WPARAM)hNewFont, TRUE);
    PostMessage(MsgBox, WM_CHAR, c, 0);
    SetFocus(MsgBox);

    // Always select the old font back into the DC
    SelectObject(hdc, hOldFont);
}
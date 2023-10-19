#include "practice.h"

namespace practice
{
    

    LRESULT CALLBACK HelpWindow(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) // функция окна помощи
    {
        static HFONT hfont;
        static HWND htext;

        static HDC hdc;
        static PAINTSTRUCT ps;

        switch (message)
        {
            case WM_CREATE:
            {
                hfont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS, TEXT("Segoe UI"));


                HWND htext = CreateWindow( // простое отображение текста
                                        TEXT("EDIT"), 
                                        TEXT("Doctor's Handbook.\r\nBase of diseases: name, symptoms, procedures,"
                                          "a list of recommended medicines with the amount required.\r\n"
                                          "Base of medicines in stock: name, quantity, interchangeability.\r\n"
                                          "The program for the implementation of the prescription after examining the patient,\r\n"
                                          "checking the availability of medicines, adjusting stocks.\r\n\r\n"
                                        "Gumarov V.R. KE-203 gumarovvr@susu.ru"), 
                                        WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE | ES_LEFT, 
                                        10,
                                        10,
                                        270,
                                        245, 
                                        hwnd, 
                                        NULL, 
                                        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), 
                                        NULL);

                SendMessage(htext, WM_SETFONT, (WPARAM) hfont, TRUE);
                UpdateWindow(htext);

                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_CLOSE:
                ShowWindow(hwnd, SW_HIDE); // при закрытии скрывается
                break;
            case WM_DESTROY:
                DeleteObject(hfont);
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

    HWND CreateWindowHelp(HINSTANCE This, HWND hWnd)
    {
        WNDCLASSEX wcHelp;
        HWND hwnd;
        TCHAR HelpName[] = TEXT("HelpFrame");

        int x = 300;
        int y = 300;
        int pos_x = 0;
        int pos_y = 0;

        RECT main_pos;
        if (GetWindowRect(hWnd, &main_pos))
        {
            pos_x = main_pos.left + (main_pos.right - main_pos.left) / 2 - x / 2;
            pos_y = main_pos.top + (main_pos.bottom - main_pos.top) / 2 - y / 2;  
        }

        wcHelp.cbSize       = sizeof(WNDCLASSEX);
        wcHelp.style      = CS_HREDRAW | CS_VREDRAW;
        wcHelp.lpfnWndProc = HelpWindow;
        wcHelp.cbClsExtra = 0;
        wcHelp.cbWndExtra = 0;
        wcHelp.hInstance  = This;
        wcHelp.hIcon        = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32, 32, 0); //LoadIcon (NULL, IDI_APPLICATION);
        wcHelp.hIconSm      = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, 0);
        wcHelp.hCursor    = LoadCursor (NULL, IDC_ARROW);
        wcHelp.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wcHelp.lpszMenuName = NULL;
        wcHelp.lpszClassName = HelpName;

        if (!RegisterClassEx(&wcHelp))
        {
            MessageBox (NULL, TEXT ("Can't register help window!"),
                        HelpName, MB_ICONERROR);
            return 0;
        }

        hwnd = CreateWindowEx(
                            WS_EX_OVERLAPPEDWINDOW,
                            HelpName,        
                            TEXT("Help"), 
                            WS_CAPTION | WS_SYSMENU,  
                            pos_x,      
                            pos_y,      
                            x,        
                            y,        
                            hWnd,               
                            NULL,               
                            This,          
                            NULL);

        return hwnd;
    }
}
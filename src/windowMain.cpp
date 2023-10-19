#include "practice.h"

namespace practice
{
    DeseaseDB db;
    
    int WINAPI Main(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int mode)
    {
        AllocConsole(); // открывать консоль при запуске

        db.recover(); // восстановить базу данных
        freopen("CONOUT$", "w", stdout); // перенеправление вывода в консоль 

        MSG msg;
        HWND hWnd;
        HWND hMenu;
        BOOL bRet;

        TCHAR AppName[] = TEXT("MainFrame");
        TCHAR ChildName[] = TEXT("MenuFrame");

        if (hWnd = CreateWindowMain(This))
        {
            ShowWindow(hWnd, mode);
            UpdateWindow(hWnd);
        }
        else
        {
            MessageBox (NULL, TEXT ("Can't create main window!"),
                        AppName, MB_ICONERROR);
            return 0;
        }

        if (hMenu = CreateWindowMenu(This, hWnd))
        {
            ShowWindow(hMenu, mode);
            UpdateWindow(hMenu);
        }
        else
        {
            MessageBox (NULL, TEXT ("Can't create menu window!"),
                        ChildName, MB_ICONERROR);
            return 0;
        }
        
        
        while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
        {
            if (bRet == -1)
            {

            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        return msg.wParam;
    }

    #define BHELP 1001
    #define BEXIT 101

    LRESULT CALLBACK MainWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // функция главного окна
    {
        static HWND buttonHelp;
        static HWND buttonExit;
        static HWND hHelp;
        static int main_pos_x;
        static int main_pos_y;
        static int main_size_x = 600;
        static int main_size_y = 600;
        static HFONT hfont;

        switch(message)
        {
            case WM_CREATE:
            {
                hfont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS, TEXT("Segoe UI"));

                int main_x = 600;
                int main_y = 600;
                HINSTANCE This = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

                buttonHelp = CreateWindow(
                            TEXT("BUTTON"),
                            TEXT("Help"),
                            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                            main_x - 120,  
                            main_y - 90,
                            100,
                            50,
                            hWnd,
                            (HMENU) BHELP,
                            This, 
                            NULL
                );
                buttonExit = CreateWindow(
                            TEXT("BUTTON"),
                            TEXT("Exit"),
                            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                            main_x - 345,  
                            main_y - 90,
                            100,
                            30,
                            hWnd,
                            (HMENU) BEXIT,
                            This, 
                            NULL
                );

                ShowWindow(buttonHelp, SW_SHOWNORMAL);
                ShowWindow(buttonExit, SW_SHOWNORMAL);

                hHelp = CreateWindowHelp(This, hWnd);

                SendMessage(buttonHelp, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(buttonExit, WM_SETFONT, (WPARAM) hfont, TRUE);
                UpdateWindow(buttonHelp);
                UpdateWindow(buttonExit);

                SendMessage(hHelp, WM_SETFONT, (WPARAM) hfont, TRUE);

                break;
            }
            case WM_COMMAND:
            {
                if (LOWORD(wParam) == BHELP) // если нажата кнопка помощи
                {
                    if (!IsWindowVisible(hHelp))
                    {
                        int pos_x = main_pos_x + main_size_x / 2 - 300 / 2;
                        int pos_y = main_pos_y + main_size_y / 2 - 300 / 2;
                        if (!IsWindowVisible(hHelp))
                        {
                            SetWindowPos(
                                    hHelp,
                                    HWND_NOTOPMOST,
                                    pos_x,
                                    pos_y,
                                    300,
                                    300,
                                    SWP_NOREDRAW
                            );
                        }
                        ShowWindow(hHelp, SW_SHOWNORMAL);
                    }
                    
                }
                if (LOWORD(wParam) == BEXIT) // если нажата кнопка выхода
                {
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                }
                break;

            }
            case WM_MOVE:
            {
                main_pos_x = (int) LOWORD(lParam);
                main_pos_y = (int) HIWORD(lParam);
                break;
            }
            case WM_DESTROY:
                db.dump();
                DeleteObject(hfont);
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }

    #define BSEARCH     1002
    #define BEDIT       1003
    #define BTHREAT     1004

    LRESULT CALLBACK MenuWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // функция окна меню
    {
        static HWND buttonSearch;
        static HWND buttonEdit;
        static HWND buttonThreat;
        static HWND buttonExit;
        static HWND hEdit;
        static HWND hSearch;
        static HWND hThreat;
        
        static int main_pos_x;
        static int main_pos_y;
        static RECT main_pos;
        static int pos_x;
        static int pos_y;

        static HFONT hfont;

        switch(message)
        {
            case WM_CREATE:
            {
                hfont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS, TEXT("Segoe UI"));

                HINSTANCE This = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
                buttonSearch = CreateWindow(
                            TEXT("BUTTON"),
                            TEXT("Search"),
                            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                            50,  
                            20,
                            200,
                            50,
                            hWnd,
                            (HMENU) BSEARCH,
                            This, 
                            NULL
                );

                buttonEdit = CreateWindow(
                            TEXT("BUTTON"),
                            TEXT("Edit"),
                            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                            50,  
                            90,
                            200,
                            50,
                            hWnd,
                            (HMENU) BEDIT,
                            This, 
                            NULL
                );

                buttonThreat = CreateWindow(
                            TEXT("BUTTON"),
                            TEXT("Generate recipe"),
                            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                            50,  
                            160,
                            200,
                            50,
                            hWnd,
                            (HMENU) BTHREAT,
                            This, 
                            NULL
                );

                

                ShowWindow(buttonSearch, SW_SHOWNORMAL);
                ShowWindow(buttonEdit, SW_SHOWNORMAL);
                ShowWindow(buttonThreat, SW_SHOWNORMAL);


                hEdit = CreateWindowEdit(This, hWnd);
                hSearch = CreateWindowSearch(This, hWnd);
                hThreat = CreateWindowThreat(This, hWnd);

                SendMessage(buttonSearch, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(buttonEdit, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(buttonThreat, WM_SETFONT, (WPARAM) hfont, TRUE);
                
                UpdateWindow(buttonSearch);
                UpdateWindow(buttonEdit);
                UpdateWindow(buttonThreat);
                
                
                break;
            }
            case WM_COMMAND:
            {
                if (LOWORD(wParam) == BSEARCH)
                {
                    if (!IsWindowVisible(hSearch) && GetWindowRect(hWnd, &main_pos))
                    {
                        pos_x = main_pos.left + (main_pos.right - main_pos.left) / 2 - 500 / 2;
                        pos_y = main_pos.top + (main_pos.bottom - main_pos.top) / 2 - 600 / 2;
                        if (!IsWindowVisible(hSearch) || main_pos_x != pos_x || main_pos_y != pos_y)
                        {
                            main_pos_x = pos_x;
                            main_pos_y = pos_y;
                            SetWindowPos( // maybe you should change flags
                                    hSearch,
                                    HWND_NOTOPMOST,
                                    main_pos_x,
                                    main_pos_y,
                                    500,
                                    600,
                                    SWP_NOREDRAW
                            );
                        }
                        ShowWindow(hSearch, SW_SHOWNORMAL);
                    }
                    
                }
                if (LOWORD(wParam) == BEDIT)
                {
                    if (!IsWindowVisible(hEdit) && GetWindowRect(hWnd, &main_pos))
                    {
                        pos_x = main_pos.left + (main_pos.right - main_pos.left) / 2 - 500 / 2;
                        pos_y = main_pos.top + (main_pos.bottom - main_pos.top) / 2 - 500 / 2;
                        if (!IsWindowVisible(hEdit) || main_pos_x != pos_x || main_pos_y != pos_y)
                        {
                            main_pos_x = pos_x;
                            main_pos_y = pos_y;
                            SetWindowPos( // maybe you should change flags
                                    hEdit,
                                    HWND_NOTOPMOST,
                                    main_pos_x,
                                    main_pos_y,
                                    500,
                                    500,
                                    SWP_NOREDRAW
                            );
                        }
                        ShowWindow(hEdit, SW_SHOWNORMAL);
                    }
                    
                    
                }
                if (LOWORD(wParam) == BTHREAT)
                {
                    if (!IsWindowVisible(hThreat) && GetWindowRect(hWnd, &main_pos))
                    {
                        pos_x = main_pos.left + (main_pos.right - main_pos.left) / 2 - 500 / 2;
                        pos_y = main_pos.top + (main_pos.bottom - main_pos.top) / 2 - 500 / 2;
                        if (!IsWindowVisible(hThreat) || main_pos_x != pos_x || main_pos_y != pos_y)
                        {
                            main_pos_x = pos_x;
                            main_pos_y = pos_y;
                            SetWindowPos( // maybe you should change flags
                                    hThreat,
                                    HWND_NOTOPMOST,
                                    main_pos_x,
                                    main_pos_y,
                                    500,
                                    500,
                                    SWP_NOREDRAW
                            );
                        }
                        ShowWindow(hThreat, SW_SHOWNORMAL);
                    }
                }
            }
            case WM_SYSCOMMAND:
                break;
            case WM_DESTROY:
                DeleteObject(hfont);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }

    HWND CreateWindowMain(HINSTANCE This) // создание и регистрация главного окна
    {
        WNDCLASSEX wcMain;
        HWND hwnd;
        TCHAR AppName[] = TEXT("MainFrame");
        int main_x = 600;
        int main_y = 600;

        int xc = GetSystemMetrics(SM_CXSCREEN) / 2;
        int yc = GetSystemMetrics(SM_CYSCREEN) / 2;
        
        wcMain.cbSize       = sizeof(WNDCLASSEX);
        wcMain.style      = CS_HREDRAW | CS_VREDRAW;
        wcMain.lpfnWndProc = MainWindow;
        wcMain.cbClsExtra = 0;
        wcMain.cbWndExtra = 0;
        wcMain.hInstance  = This;
        wcMain.hIcon        = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32, 32, 0); //LoadIcon (NULL, IDI_APPLICATION);
        wcMain.hIconSm      = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, 0);
        wcMain.hCursor    = LoadCursor (NULL, IDC_ARROW);
        wcMain.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wcMain.lpszMenuName = NULL;
        wcMain.lpszClassName = AppName;

        if (!RegisterClassEx(&wcMain))
        {
            MessageBox (NULL, TEXT ("Can't register main window!"),
                        AppName, MB_ICONERROR);
            return 0;
        }

        hwnd = CreateWindowEx(
                            WS_EX_APPWINDOW,
                            AppName,      
                            TEXT("DeseaseDB"), 
                            WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,    
                            xc - (main_x / 2),      
                            yc - (main_x / 2),      
                            main_x,      
                            main_y,      
                            NULL,               
                            NULL,               
                            This,          
                            NULL); 

        return hwnd;
    }

    HWND CreateWindowMenu(HINSTANCE This, HWND hWnd) // создание и регистрация окна меню
    {
        WNDCLASS wcMenu;
        HWND hwnd;
        TCHAR ChildName[] = TEXT("MenuFrame");
        int main_x = 600;
        int main_y = 600;

        wcMenu.style        = CS_HREDRAW | CS_VREDRAW;
        wcMenu.lpfnWndProc = MenuWindow;
        wcMenu.cbClsExtra   = 0;
        wcMenu.cbWndExtra = sizeof(long);
        wcMenu.hInstance    = This;
        wcMenu.hIcon        = LoadIcon (NULL, IDI_APPLICATION);
        wcMenu.hCursor  = LoadCursor (NULL, IDC_ARROW);
        wcMenu.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wcMenu.lpszMenuName = NULL;
        wcMenu.lpszClassName = ChildName;

        if (!RegisterClass(&wcMenu))
        {
            MessageBox (NULL, TEXT ("Can't register menu window!"),
                        ChildName, MB_ICONERROR);
            return 0;
        }

        hwnd = CreateWindow(ChildName,        
                            TEXT("Menu"), 
                            WS_CHILD | WS_VISIBLE | WS_CAPTION,  
                            (main_x / 2) - (300 / 2),      
                            (main_y / 2) - (300 / 2),      
                            300,        
                            300,        
                            hWnd,               
                            NULL,               
                            This,          
                            NULL);

        
        return hwnd;
    }


}

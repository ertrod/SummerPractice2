#include "practice.h"

namespace practice
{
    extern DeseaseDB db;

#define ID_THREAT           1063
#define ID_THREAT_BUTTON    1064
#define ID_THREAT_TEXT      1065
#define ID_THREAT_LIST      1066

    LRESULT CALLBACK ThreatWindow(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) // окно генерации рецепта
    {
        static HWND hText; 
        static HWND hButton;
        static HWND hList;

        static HFONT hfont;
        static HFONT hfonttext;

        static HDC hdc;
        static PAINTSTRUCT ps;

        switch (message)
        {
            case WM_CREATE:
            {
                hfont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS, TEXT("Segoe UI"));

                hfonttext = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS, TEXT("Segoe UI"));

                hButton = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Find treatment"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                325,
                                50,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_THREAT_BUTTON,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hText = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                35,
                                50,
                                200,
                                100,
                                hwnd,
                                (HMENU) ID_THREAT_TEXT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hList = CreateWindow(
                                TEXT("LISTBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_WANTKEYBOARDINPUT,
                                35,
                                115,
                                420,
                                335,
                                hwnd,
                                (HMENU) ID_THREAT_LIST,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                // init combobox
                for (TObj<DeseaseName>* r = db.names_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hText, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                SendMessage(hButton, WM_SETFONT, (WPARAM) hfont, TRUE);

                SendMessage(hText, WM_SETFONT, (WPARAM) hfont, TRUE);

                SendMessage(hList, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hButton);

                UpdateWindow(hText);

                UpdateWindow(hList);


                break;
            }
            case WM_COMMAND:
            {
                int i;
                SendMessage(hText, LB_RESETCONTENT, 0, 0);

                if ((i = LOWORD(wparam)) == ID_THREAT_BUTTON) // одна кнопка для поиска
                {
                    std::vector<std::string> res;
                    SendMessage(hList, LB_RESETCONTENT, 0, 0);
                    int id = SendMessage(hText, CB_GETCURSEL, 0, 0);
                    std::vector<TObj<Threatment>*>* v = 0;

                    TObj<DeseaseName>* n = db.names_table()->at_pos(id);
                    if (n)
                        v = db.find_desease_threatment_by_name(n->obj->to_string());
                    if (v)
                    {
                        std::string meaning = "Finding recipes for " + n->obj->to_string();
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>(meaning.c_str()));
                        for (std::vector<TObj<Threatment>*>::iterator i = v->begin(); i != v->end(); i++)
                        {
                            std::cout << (*i)->obj->to_string() << std::endl;
                            res.push_back((*i)->obj->to_string());
                        }
                        delete v;
                    }

                    if (res.size()) // вывод результата в список
                    {
                        for (std::vector<std::string>::iterator i = res.begin(); i != res.end(); i++)
                        {
                            SendMessage(hList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>((*i).c_str()));
                        }
                    }
                }
                break;
            }
            case WM_ACTIVATE: // переинициализация комбобокса
            {
                if (wparam)
                {
                    std::cout << "threat: focus\n";
                    std::cout << "updating combobox\n";
                    SendMessage(hText, CB_RESETCONTENT, 0, 0);

                    for (TObj<DeseaseName>* r = db.names_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hText, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }
                }
                break;
            }
                break;
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 30, 10, TEXT("Find medicine"), 13);
                TextOut(hdc, 35, 34, TEXT("Name of disease"), 15);
                TextOut(hdc, 30, 94, TEXT("Result"), 6);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_CLOSE:
                ShowWindow(hwnd, SW_HIDE);
                break;
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

    HWND CreateWindowThreat(HINSTANCE This, HWND hWnd)
    {
        WNDCLASSEX wcMenu;
        HWND hwnd;
        TCHAR ThreatName[] = TEXT("ThreatFrame");

        int x = 500;
        int y = 500;
        int pos_x = 0;
        int pos_y = 0;

        RECT main_pos;
        if (GetWindowRect(hWnd, &main_pos))
        {
            pos_x = main_pos.left + (main_pos.right - main_pos.left) / 2 - x / 2;
            pos_y = main_pos.top + (main_pos.bottom - main_pos.top) / 2 - y / 2;  
        }

        wcMenu.cbSize       = sizeof(WNDCLASSEX);
        wcMenu.style      = CS_HREDRAW | CS_VREDRAW;
        wcMenu.lpfnWndProc = ThreatWindow;
        wcMenu.cbClsExtra = 0;
        wcMenu.cbWndExtra = 0;
        wcMenu.hInstance  = This;
        wcMenu.hIcon        = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32, 32, 0); //LoadIcon (NULL, IDI_APPLICATION);
        wcMenu.hIconSm      = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, 0);
        wcMenu.hCursor    = LoadCursor (NULL, IDC_ARROW);
        wcMenu.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wcMenu.lpszMenuName = NULL;
        wcMenu.lpszClassName = ThreatName;

        if (!RegisterClassEx(&wcMenu))
        {
            MessageBox (NULL, TEXT ("Can't register menu window!"),
                        ThreatName, MB_ICONERROR);
            return 0;
        }

        hwnd = CreateWindowEx(
                            WS_EX_OVERLAPPEDWINDOW,          
                            ThreatName,        
                            TEXT("Generating recipes"), 
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
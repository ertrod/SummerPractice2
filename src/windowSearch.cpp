#include "practice.h"

namespace practice
{
    extern DeseaseDB db;

#define ID_SEARCH                       1050   //??
#define ID_SEARCH_BUTTON_NAMES          1051
#define ID_SEARCH_BUTTON_SYMPTOMES      1052
#define ID_SEARCH_BUTTON_PROCEDURES     1053
#define ID_SEARCH_BUTTON_THREAT         1054
#define ID_SEARCH_BUTTON_MEDICINE       1055
#define ID_SEARCH_BUTTON_ANALOG         1056

#define ID_SEARCH_TEXT_NAMES            1057
#define ID_SEARCH_TEXT_SYMPTOMES        1058
#define ID_SEARCH_TEXT_PROCEDURES       1059
#define ID_SEARCH_TEXT_THREAT           1060
#define ID_SEARCH_TEXT_MEDICINE         1061
#define ID_SEARCH_TEXT_ANALOG           1062

#define ID_SEARCH_LIST_RESULT            1063


    LRESULT CALLBACK SearchWindow(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        static HWND hbuttonNames;
        static HWND hbuttonSymptomes;
        static HWND hbuttonProcedures;
        static HWND hbuttonThreat;

        static HWND hbuttonMedicine;
        static HWND hbuttonAnalog;

        static HWND hsearchNames;
        static HWND hsearchSymptomes;
        static HWND hsearchProcedures;
        static HWND hsearchThreat;

        static HWND hsearchMedicine;

        static HWND hsearchList;

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


                hbuttonNames = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Find by name"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                325,
                                50,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_SEARCH_BUTTON_NAMES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hbuttonSymptomes = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Find by symptome"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                325,
                                90,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_SEARCH_BUTTON_SYMPTOMES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hbuttonProcedures = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Find by procedure"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                325,
                                130,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_SEARCH_BUTTON_PROCEDURES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hbuttonThreat = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Find by recipe"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                325,
                                170,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_SEARCH_BUTTON_THREAT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hbuttonMedicine = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Check availability"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                325,
                                250,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_SEARCH_BUTTON_MEDICINE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hbuttonAnalog = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Find analogs"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                325,
                                290,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_SEARCH_BUTTON_ANALOG,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hsearchNames = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                35,
                                50,
                                200,
                                100,
                                hwnd,
                                (HMENU) ID_SEARCH_TEXT_NAMES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);


                hsearchSymptomes = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                35,
                                90,
                                200,
                                100,
                                hwnd,
                                (HMENU) ID_SEARCH_TEXT_SYMPTOMES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hsearchProcedures = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                35,
                                130,
                                200,
                                100,
                                hwnd,
                                (HMENU) ID_SEARCH_TEXT_PROCEDURES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hsearchThreat =CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                35,
                                170,
                                200,
                                100,
                                hwnd,
                                (HMENU) ID_SEARCH_TEXT_THREAT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hsearchMedicine = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                35,
                                250,
                                200,
                                100,
                                hwnd,
                                (HMENU) ID_SEARCH_TEXT_MEDICINE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hsearchList = CreateWindow(
                                TEXT("LISTBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL  | LBS_STANDARD | LBS_WANTKEYBOARDINPUT,
                                35,
                                350,
                                420,
                                200,
                                hwnd,
                                (HMENU) ID_SEARCH_LIST_RESULT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                //init comboboxes;
                for (TObj<DeseaseName>* r = db.names_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hsearchNames, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                for (TObj<DeseaseName>* r = db.symptomes_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hsearchSymptomes, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                for (TObj<DeseaseName>* r = db.procedures_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hsearchProcedures, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                for (TObj<Threatment>* r = db.threatment_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hsearchThreat, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hsearchMedicine, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                SendMessage(hsearchList, WM_SETFONT, (WPARAM) hfont, TRUE);

                SendMessage(hbuttonNames, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hbuttonSymptomes, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hbuttonProcedures, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hbuttonThreat, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hbuttonAnalog, WM_SETFONT, (WPARAM) hfont, TRUE);
                
                SendMessage(hbuttonMedicine, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hbuttonNames);
                UpdateWindow(hbuttonSymptomes);
                UpdateWindow(hbuttonProcedures);
                UpdateWindow(hbuttonThreat);

                UpdateWindow(hbuttonMedicine);
                UpdateWindow(hbuttonAnalog);

                SendMessage(hsearchNames, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hsearchSymptomes, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hsearchProcedures, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hsearchThreat, WM_SETFONT, (WPARAM) hfont, TRUE);
                
                SendMessage(hsearchMedicine, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hsearchNames);
                UpdateWindow(hsearchSymptomes);
                UpdateWindow(hsearchProcedures);
                UpdateWindow(hsearchThreat);

                UpdateWindow(hsearchMedicine);

                break;
            }

            case WM_COMMAND:
            {
                int i;
                if ((i = LOWORD(wparam)) > ID_SEARCH  && i <= ID_SEARCH_BUTTON_ANALOG )
                {
                    std::vector<std::string> res;
                    std::string meaning;

                    SendMessage(hsearchList, LB_RESETCONTENT, 0, 0);
                    switch (i)
                    {
                        case ID_SEARCH_BUTTON_NAMES:
                        {
                            int id = SendMessage(hsearchNames, CB_GETCURSEL, 0, 0);

                            if (id > -1)
                            {
                                std::vector<TObj<DeseaseDBEntry>*>* v = 0;

                                TObj<DeseaseName>* n = db.names_table()->at_pos(id);

                                if (n)
                                    v = db.find_desease_by_name(n->obj->to_string());
                                if (v)
                                {
                                    meaning = "Diseases by name " + n->obj->to_string();
                                    SendMessage(hsearchList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>(meaning.c_str()));
                                    for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                                    {
                                        res.push_back((*i)->obj->to_string());
                                    }
                                    delete v;
                                }
                            }

                            break;
                        }
                        case ID_SEARCH_BUTTON_SYMPTOMES:
                        {
                            int id = SendMessage(hsearchSymptomes, CB_GETCURSEL, 0, 0);

                            if (id > -1)
                            {
                                std::vector<TObj<DeseaseDBEntry>*>* v = 0;
                                TObj<DeseaseName>* n = db.symptomes_table()->at_pos(id);
                                if (n)
                                    v = db.find_desease_by_symptome(n->obj->to_string());
                                if (v)
                                {
                                    meaning = "Diseases by symptome " + n->obj->to_string();
                                    SendMessage(hsearchList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>(meaning.c_str()));
                                    for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                                    {
                                        res.push_back((*i)->obj->to_string());
                                    }
                                    delete v;
                                }
                            }

                            break;
                        }
                        case ID_SEARCH_BUTTON_PROCEDURES:
                        {
                            int id = SendMessage(hsearchProcedures, CB_GETCURSEL, 0, 0);

                            if (id > -1)
                            {
                                std::vector<TObj<DeseaseDBEntry>*>* v = 0;

                                TObj<DeseaseName>* n = db.procedures_table()->at_pos(id);
                                if (n)
                                    v = db.find_desease_by_procedure(n->obj->to_string());
                                if (v)
                                {
                                    meaning = "Diseases by procedure " + n->obj->to_string();
                                    SendMessage(hsearchList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>(meaning.c_str()));
                                    for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                                    {
                                        res.push_back((*i)->obj->to_string());
                                    }
                                    delete v;
                                }
                            }

                            break;
                        }
                        case ID_SEARCH_BUTTON_THREAT:
                        {
                            int id = SendMessage(hsearchThreat, CB_GETCURSEL, 0, 0);

                            if (id > -1)
                            {
                                std::vector<TObj<DeseaseDBEntry>*>* v = 0;
                                TObj<Threatment>* n = db.threatment_table()->at_pos(id);

                                if (n)
                                    v = db.find_desease_by_threatment(n);
                                if (v)
                                {
                                    meaning = "Diseases by recipe " + n->obj->to_string();
                                    SendMessage(hsearchList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>(meaning.c_str()));
                                    for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                                    {
                                        res.push_back((*i)->obj->to_string());
                                    }
                                    delete v;
                                }
                            }

                            break;
                        }
                        case ID_SEARCH_BUTTON_MEDICINE:
                        {
                            
                            int id = SendMessage(hsearchMedicine, CB_GETCURSEL, 0, 0);

                            if (id > -1)
                            {
                                TObj<MedicineDBEntry>* s = 0;
                                TObj<MedicineName>* m = db.medicines_table()->at_pos(id);

                                if (m)
                                    s = db.find_stock(m);
                                if (s)
                                {
                                    meaning = "Availability of medicine " + m->obj->to_string();
                                    SendMessage(hsearchList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>(meaning.c_str()));
                                    res.push_back(s->obj->to_string());
                                }
                            }

                            break;
                        }
                        case ID_SEARCH_BUTTON_ANALOG:
                        {
                            int id = SendMessage(hsearchMedicine, CB_GETCURSEL, 0, 0);

                            if (id > -1)
                            {
                                std::vector<TObj<MedicineAnalog>*>* v = 0;
                                TObj<MedicineName>* m = db.medicines_table()->at_pos(id);

                                if (m)
                                    v = db.find_analog_name(m);
                                if (v)
                                {
                                    meaning = "Analogs of medicine " + m->obj->to_string();
                                    SendMessage(hsearchList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>(meaning.c_str()));
                                    for (std::vector<TObj<MedicineAnalog>*>::iterator i = v->begin(); i != v->end(); i++)
                                    {
                                        res.push_back((*i)->obj->to_string());
                                    }
                                    delete v;
                                }
                            }

                            break;
                        }
                    }

                    if (res.size()) // показать результат поиска в листбоксе
                    {
                        for (std::vector<std::string>::iterator i = res.begin(); i != res.end(); i++)
                        {
                            SendMessage(hsearchList, LB_ADDSTRING, 0, (LPARAM) const_cast<char*>((*i).c_str()));
                        }
                    }
                }
                break;
            }
            case WM_ACTIVATE: // переинициализация всех комбобоксов 
            {
                if (wparam)
                {
                    std::cout << "search: focus\n";
                    std::cout << "updating comboboxes\n";
                    SendMessage(hsearchNames, CB_RESETCONTENT, 0, 0);
                    SendMessage(hsearchSymptomes, CB_RESETCONTENT, 0, 0);
                    SendMessage(hsearchProcedures, CB_RESETCONTENT, 0, 0);
                    SendMessage(hsearchThreat, CB_RESETCONTENT, 0, 0);
                    SendMessage(hsearchMedicine, CB_RESETCONTENT, 0, 0);

                    for (TObj<DeseaseName>* r = db.names_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hsearchNames, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }

                    for (TObj<DeseaseName>* r = db.symptomes_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hsearchSymptomes, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }

                    for (TObj<DeseaseName>* r = db.procedures_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hsearchProcedures, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }

                    for (TObj<Threatment>* r = db.threatment_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hsearchThreat, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }

                    for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hsearchMedicine, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }
                }
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 30, 10, TEXT("Table of diseases"), 17);
                TextOut(hdc, 35, 34, TEXT("Name of disease"), 15);
                TextOut(hdc, 35, 74, TEXT("Symptome"), 8);
                TextOut(hdc, 35, 114, TEXT("Procedure"), 9);
                TextOut(hdc, 35, 154, TEXT("Treatment"), 10);
                TextOut(hdc, 30, 214, TEXT("Medicine"), 8);
                TextOut(hdc, 35, 234, TEXT("Name of medicine"), 16);    
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

    HWND CreateWindowSearch(HINSTANCE This, HWND hWnd)
    {
        WNDCLASSEX wcMenu;
        HWND hwnd;
        TCHAR SearchName[] = TEXT("SearchFrame");

        int x = 500;
        int y = 600;
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
        wcMenu.lpfnWndProc = SearchWindow;
        wcMenu.cbClsExtra = 0;
        wcMenu.cbWndExtra = 0;
        wcMenu.hInstance  = This;
        wcMenu.hIcon        = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32, 32, 0); //LoadIcon (NULL, IDI_APPLICATION);
        wcMenu.hIconSm      = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, 0);
        wcMenu.hCursor    = LoadCursor (NULL, IDC_ARROW);
        wcMenu.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wcMenu.lpszMenuName = NULL;
        wcMenu.lpszClassName = SearchName;

        if (!RegisterClassEx(&wcMenu))
        {
            MessageBox (NULL, TEXT ("Can't register search window!"),
                        SearchName, MB_ICONERROR);
            return 0;
        }

        hwnd = CreateWindowEx(
                            WS_EX_OVERLAPPEDWINDOW,
                            SearchName,        
                            TEXT("Find"), 
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
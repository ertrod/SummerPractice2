#include "practice.h"


namespace practice
{
    extern DeseaseDB db;

    LRESULT CALLBACK EditWindow(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) // функция окна редактироавния
    {
        static HWND hTab;
        static HWND hCurrentTab;
        static HFONT hfont;

        static HWND hTDeseaseNames;
        static HWND hTSymptomes;
        static HWND hTProcedures;
        static HWND hTThreatment;
        static HWND hTDeseaseTable;
        static HWND hTMedicine;
        static HWND hTStock;
        static HWND hTAnalogs;

        static int currTab;

        switch (message)
        {
            case WM_CREATE:
            {
                HINSTANCE This = (HINSTANCE)GetWindowLongPtr(hTab, GWLP_HINSTANCE);
                hfont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS, TEXT("Segoe UI"));

                RECT rParent;
                INITCOMMONCONTROLSEX icex;
                TCITEM ti;

                icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
                icex.dwICC = ICC_TAB_CLASSES;
                InitCommonControlsEx(&icex);

                GetClientRect(hwnd, &rParent);
                hTab = CreateWindow(
                                    WC_TABCONTROL,
                                    TEXT(""),
                                    WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                    0,
                                    0,
                                    490,
                                    468,
                                    hwnd,
                                    NULL,
                                    This,
                                    NULL);

                ti.mask = TCIF_TEXT; // инициализация вкладок
                ti.pszText = TEXT(const_cast<char *>("Disease"));
                TabCtrl_InsertItem(hTab, 0, &ti);
                ti.pszText = TEXT(const_cast<char *>("Symptomes"));
                TabCtrl_InsertItem(hTab, 1, &ti);
                ti.pszText = TEXT(const_cast<char *>("Procedures"));
                TabCtrl_InsertItem(hTab, 2, &ti);
                ti.pszText = TEXT(const_cast<char *>("Treatment"));
                TabCtrl_InsertItem(hTab, 3, &ti);
                ti.pszText = TEXT(const_cast<char *>("Table of diseases"));
                TabCtrl_InsertItem(hTab, 4, &ti);
                ti.pszText = TEXT(const_cast<char *>("Medicine"));
                TabCtrl_InsertItem(hTab, 5, &ti);
                ti.pszText = TEXT(const_cast<char *>("Stock"));
                TabCtrl_InsertItem(hTab, 6, &ti);
                ti.pszText = TEXT(const_cast<char *>("Analogs"));
                TabCtrl_InsertItem(hTab, 7, &ti);

                SendMessage(hTab, WM_SETFONT, (WPARAM) hfont, TRUE);
                UpdateWindow(hTab);



                TCHAR dn[] = TEXT("EditDN");
                TCHAR s[] = TEXT("EditS");
                TCHAR p[] = TEXT("EditP");
                TCHAR t[] = TEXT("EditT");
                TCHAR dt[] = TEXT("EditDT");
                TCHAR m[] = TEXT("EditM");
                TCHAR st[] = TEXT("EditST");
                TCHAR a[] = TEXT("EditA");
                // создание и регистрация окон вкладок
                hTDeseaseNames = CreateWindowEditTable(This, hTab, EditDNames, dn);
                hTSymptomes = CreateWindowEditTable(This, hTab, EditSymptomes, s);
                hTProcedures = CreateWindowEditTable(This, hTab, EditProcedures, p);
                hTThreatment = CreateWindowEditTable(This, hTab, EditThreatment, t);
                hTDeseaseTable = CreateWindowEditTable(This, hTab, EditDTable, dt);
                hTMedicine = CreateWindowEditTable(This, hTab, EditMedicine, m);
                hTStock = CreateWindowEditTable(This, hTab, EditStock, st);
                hTAnalogs = CreateWindowEditTable(This, hTab, EditAnalogs, a);

                currTab = 0;
                break;
            }
            case WM_SHOWWINDOW:
            {// здесь открывается вкладка которая была выбрана перед закрытием окна
                TabCtrl_SetCurSel(hTab, currTab);
                switch (currTab)
                {
                    case 0:
                        ShowWindow(hTDeseaseNames, SW_SHOW);
                        break;
                    case 1:
                        ShowWindow(hTSymptomes, SW_SHOW);
                        break;
                    case 2:
                        ShowWindow(hTProcedures, SW_SHOW);
                        break;
                    case 3:
                        ShowWindow(hTThreatment, SW_SHOW);
                        break;
                    case 4:
                        ShowWindow(hTDeseaseTable, SW_SHOW);
                        break;
                    case 5:
                        ShowWindow(hTMedicine, SW_SHOW);
                        break;
                    case 6:
                        ShowWindow(hTStock, SW_SHOW);
                        break;
                    case 7:
                        ShowWindow(hTAnalogs, SW_SHOW);
                        break;
                }
                break;
            }
            case WM_NOTIFY:
            {   // здесь скрывается предыдущее окно вкладки и показывается выбранная вкладка
                if (((LPNMHDR)lparam)->code == TCN_SELCHANGE)
                {
                    switch (currTab)
                    {
                        case 0:
                            ShowWindow(hTDeseaseNames, SW_HIDE);
                            break;
                        case 1:
                            ShowWindow(hTSymptomes, SW_HIDE);
                            break;
                        case 2:
                            ShowWindow(hTProcedures, SW_HIDE);
                            break;
                        case 3:
                            ShowWindow(hTThreatment, SW_HIDE);
                            break;
                        case 4:
                            ShowWindow(hTDeseaseTable, SW_HIDE);
                            break;
                        case 5:
                            ShowWindow(hTMedicine, SW_HIDE);
                            break;
                        case 6:
                            ShowWindow(hTStock, SW_HIDE);
                            break;
                        case 7:
                            ShowWindow(hTAnalogs, SW_HIDE);
                            break;
                    }
                    int tabID = TabCtrl_GetCurSel(hTab);
                    switch (tabID)
                    {
                        case 0: // desease names
                        {
                            currTab = 0;

                            ShowWindow(hTDeseaseNames, SW_SHOW);

                            break;
                        }
                        case 1: // symptome names
                        {
                            currTab = 1;

                            ShowWindow(hTSymptomes, SW_SHOW);
                            
                            break;
                        }
                        case 2: // procedures
                        {
                            currTab = 2;

                            ShowWindow(hTProcedures, SW_SHOW);
                            
                            break;
                        } 
                        case 3: // threatment
                        {
                            currTab = 3;

                            ShowWindow(hTThreatment, SW_SHOW);
                            
                            break;
                        }
                        case 4: // desease table
                        {
                            currTab = 4;

                            ShowWindow(hTDeseaseTable, SW_SHOW);
                            
                            break;
                        }
                        case 5: // threats
                        {
                            currTab = 5;

                            ShowWindow(hTMedicine, SW_SHOW);
                            
                            break;
                        }
                        case 6: // stock
                        {
                            currTab = 6;

                            ShowWindow(hTStock, SW_SHOW);
                            
                            break;
                        }
                        case 7: // analogs
                        {
                            currTab = 7;

                            ShowWindow(hTAnalogs, SW_SHOW);
                            
                            break;
                        }
                        default:
                            break;
                    }
                }
                break;
            }
            case WM_CLOSE:
            {   // в случае закрытия окна мы обязаны скрыть открытую вкладку
                switch (currTab)
                {
                    case 0:
                        ShowWindow(hTDeseaseNames, SW_HIDE);
                        break;
                    case 1:
                        ShowWindow(hTSymptomes, SW_HIDE);
                        break;
                    case 2:
                        ShowWindow(hTProcedures, SW_HIDE);
                        break;
                    case 3:
                        ShowWindow(hTThreatment, SW_HIDE);
                        break;
                    case 4:
                        ShowWindow(hTDeseaseTable, SW_HIDE);
                        break;
                    case 5:
                        ShowWindow(hTMedicine, SW_HIDE);
                        break;
                    case 6:
                        ShowWindow(hTStock, SW_HIDE);
                        break;
                    case 7:
                        ShowWindow(hTAnalogs, SW_HIDE);
                        break;
                }
                ShowWindow(hwnd, SW_HIDE);
                break;
            }
            case WM_DESTROY:
            {
                DeleteObject(hfont);
                break;
            }
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

// далее идет восемь подобных функций для вкладок

#define ID_LIST_NAMES                1005   
#define ID_LIST_NAMES_BUTTON_ADD     1006 
#define ID_LIST_NAMES_BUTTON_DELETE  1007
#define ID_LIST_NAMES_BUTTON_CHANGE  1008
#define ID_LIST_NAMES_TEXT           1009

    LRESULT CALLBACK EditDNames(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) // функция вкладки редактирования названия
    {
        static HWND hlistBox;
        static LV_COLUMN colNames;
        static LV_ITEM itemNames;

        static HWND hlistButtonAdd;
        static HWND hlistButtonDelete;
        static HWND hlistButtonChange;

        static HWND hlistText;
        static int counter;

        static HFONT hfont;
        static HFONT hfonttext;
        static HDC hdc;
        static PAINTSTRUCT ps;

        static int textlenght;

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
                textlenght = 128;
                counter = 0;

                RECT rParent;

                GetClientRect(hwnd, &rParent);
                hlistBox = CreateWindowEx(
                                0L,
                                WC_LISTVIEW,
                                TEXT(""),
                                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                                35,
                                40,
                                300,
                                375,
                                hwnd,
                                (HMENU) ID_LIST_NAMES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonAdd = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Add"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                100,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_NAMES_BUTTON_ADD,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonDelete = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Delete"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                300,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_NAMES_BUTTON_DELETE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonChange = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Change"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                340,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_NAMES_BUTTON_CHANGE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistText = CreateWindow(
                                TEXT("EDIT"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                                345,
                                55,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_NAMES_TEXT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);
                
                Edit_LimitText(hlistText, textlenght);
                // инициализация списка таблицы
                colNames = { 0 };
                colNames.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
                colNames.fmt = LVCFMT_LEFT;
                colNames.cx = 250;

                colNames.iSubItem = 0;
                colNames.pszText = TEXT(const_cast<char*>("Names"));
                ListView_InsertColumn(hlistBox, 0, &colNames); 

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                itemNames = { 0 };
                itemNames.mask = LVIF_TEXT;

                // проход по списку имен и заполнение таблицы имен
                for (TObj<DeseaseName>* r = db.names_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());   
                    std::string name(str.begin(), str.end());
                    itemNames.iItem = counter++;
                    itemNames.pszText = const_cast<char*>(name.c_str());
                    ListView_InsertItem(hlistBox, &itemNames);
                }
                // изменение шрифта на кнопках
                SendMessage(hlistButtonAdd, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonDelete, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonChange, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hlistBox);

                UpdateWindow(hlistButtonAdd);
                UpdateWindow(hlistButtonDelete);
                UpdateWindow(hlistButtonChange);
                // изменение шрифта в окне редактирования
                SendMessage(hlistText, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                UpdateWindow(hlistText);

                break;
            }
            case WM_COMMAND:
            {   
                int i;
                if ((i = LOWORD(wparam)) > ID_LIST_NAMES && i < ID_LIST_NAMES_TEXT)
                { // check if buttons
                    int len = GetWindowTextLength(hlistText) + 1; 
                    TCHAR buf[textlenght + 1];

                    GetWindowText(hlistText, buf, len); // получаем введенное название

                    std::string str(buf);
                    switch(i)
                    { 
                        case ID_LIST_NAMES_BUTTON_ADD: // нажата кнопка добавления
                        {  
                            int id;

                            if (!str.empty() && ((id = db.add_name(str)) != -1)) // добавлаем в список 
                            {
                                std::string name(str.begin(), str.end());
                                itemNames.iItem = counter++;
                                itemNames.pszText = const_cast<char*>(name.c_str());
                                ListView_InsertItem(hlistBox, &itemNames); // добавляем в таблицу
                                db.dump(); // сохраняем список в файл
                            }
                            SetWindowText(hlistText, TEXT(""));

                            
                            break;
                        }
                        case ID_LIST_NAMES_BUTTON_DELETE: // нажата кнопка удаления
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                            
                            if (id > -1)
                            {
                                if (db.remove_name(id)) // удалаем из списка имен
                                    SendMessage(hlistBox, LVM_DELETEITEM, id, 0); // удалаем из таблицы
                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                            }

                            break;
                        }
                        case ID_LIST_NAMES_BUTTON_CHANGE: // нажата кнопка изменения
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED); // получаем выделенный элемент
                            
                            if (id > -1)
                            {
                                std::string name(str.begin(), str.end());
                                TObj<DeseaseName>* o = db.names_table()->at_pos(id);
                                if (o) // если такой элемент есть на позиции
                                {
                                    if (db.change_name(o, str) != -1) // изменяем элемент в списке
                                        ListView_SetItemText(hlistBox, id, 0, const_cast<char*>(name.c_str())); // изменяем в таблице
                                }

                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                                SetWindowText(hlistText, TEXT(""));
                            }

                            break;
                        }
                    }
                    break;
                }

                break;
            }
            case WM_SHOWWINDOW:
            {
                if (wparam)
                    std::cout << "names: focus\n";
                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 35, 20, TEXT("Names of diseases"), 17);
                TextOut(hdc, 345, 40, TEXT("Name"), 4);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

#define ID_LIST_SYMPTOMES                   1010   
#define ID_LIST_SYMPTOMES_BUTTON_ADD        1011 
#define ID_LIST_SYMPTOMES_BUTTON_DELETE     1012
#define ID_LIST_SYMPTOMES_BUTTON_CHANGE     1013
#define ID_LIST_SYMPTOMES_TEXT              1014

    LRESULT CALLBACK EditSymptomes(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        static HWND hlistBox;
        static LV_COLUMN colNames;
        static LV_ITEM itemNames;

        static HWND hlistButtonAdd;
        static HWND hlistButtonDelete;
        static HWND hlistButtonChange;

        static HWND hlistText;
        static int counter;

        static HFONT hfont;
        static HFONT hfonttext;
        static HDC hdc;
        static PAINTSTRUCT ps;

        static int textlenght;

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
                textlenght = 128;
                counter = 0;

                RECT rParent;

                GetClientRect(hwnd, &rParent);
                hlistBox = CreateWindowEx(
                                0L,
                                WC_LISTVIEW,
                                TEXT(""),
                                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                                35,
                                40,
                                300,
                                375,
                                hwnd,
                                (HMENU) ID_LIST_SYMPTOMES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonAdd = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Add"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                100,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_SYMPTOMES_BUTTON_ADD,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonDelete = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Delete"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                300,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_SYMPTOMES_BUTTON_DELETE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonChange = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Change"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                340,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_SYMPTOMES_BUTTON_CHANGE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistText = CreateWindow(
                                TEXT("EDIT"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                                345,
                                55,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_SYMPTOMES_TEXT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);
                
                Edit_LimitText(hlistText, textlenght);
                // инициализация таблицы
                colNames = { 0 };
                colNames.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
                colNames.fmt = LVCFMT_LEFT;
                colNames.cx = 250;

                colNames.iSubItem = 0;
                colNames.pszText = TEXT(const_cast<char*>("Names"));
                ListView_InsertColumn(hlistBox, 0, &colNames); 

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                itemNames = { 0 };
                itemNames.mask = LVIF_TEXT;
                // инициализируем таблицу перед открытием 
                for (TObj<DeseaseName>* r = db.symptomes_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());   
                    std::string name(str.begin(), str.end());
                    itemNames.iItem = counter++;
                    itemNames.pszText = const_cast<char*>(name.c_str());
                    ListView_InsertItem(hlistBox, &itemNames);
                }
                // изменяем шрифт
                SendMessage(hlistButtonAdd, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonDelete, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonChange, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hlistBox);

                UpdateWindow(hlistButtonAdd);
                UpdateWindow(hlistButtonDelete);
                UpdateWindow(hlistButtonChange);

                SendMessage(hlistText, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                UpdateWindow(hlistText);

                break;
            }
            case WM_COMMAND:
            {   
                int i;
                if ((i = LOWORD(wparam)) > ID_LIST_SYMPTOMES && i < ID_LIST_SYMPTOMES_TEXT)
                { // check if buttons
                    int len = GetWindowTextLength(hlistText) + 1;
                    TCHAR buf[textlenght + 1];

                    GetWindowText(hlistText, buf, len); // получаем текст из окна редактирования

                    std::string str(buf);
                    switch(i)
                    { 
                        case ID_LIST_SYMPTOMES_BUTTON_ADD: // нажата кнопка добавления
                        {  
                            int id;

                            if (!str.empty() && ((id = db.add_symptome(str)) != -1)) // если добавили
                            {
                                std::string name(str.begin(), str.end());
                                itemNames.iItem = counter++;
                                itemNames.pszText = const_cast<char*>(name.c_str());
                                ListView_InsertItem(hlistBox, &itemNames); // добавляем в таблицу
                                db.dump();
                            }
                            SetWindowText(hlistText, TEXT(""));

                            
                            break;
                        }
                        case ID_LIST_SYMPTOMES_BUTTON_DELETE: // нажата кнопка удаления
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED); // получем выделенный элемент
                            
                            if (id > -1)
                            {
                                if (db.remove_symptome(id)) // удаляем из списка
                                    SendMessage(hlistBox, LVM_DELETEITEM, id, 0); // удаляем из таблицы
                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++) // обновляем таблицу
                                    ListView_Update(hlistBox,i);
                            }

                            break;
                        }
                        case ID_LIST_SYMPTOMES_BUTTON_CHANGE: // нажата кнопка изменения
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED); // получаем выделенный элемент
                            
                            if (id > -1)
                            {
                                std::string name(str.begin(), str.end());
                                TObj<DeseaseName>* o = db.symptomes_table()->at_pos(id);
                                if (o) // если такой элемент присутствует
                                {
                                    if (db.change_symptome(o, str) != -1) // изменяем 
                                        ListView_SetItemText(hlistBox, id, 0, const_cast<char*>(name.c_str())); // изменяем в таблице
                                }

                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                                SetWindowText(hlistText, TEXT(""));
                            }

                            break;
                        }
                    }
                    break;
                }


                break;
            }
            case WM_SHOWWINDOW:
            {
                if (wparam)
                    std::cout << "symptomes: focus\n";
                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 35, 20, TEXT("Symptomes"), 9);
                TextOut(hdc, 345, 40, TEXT("Name"), 4);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

#define ID_LIST_PROCEDURES                  1015   
#define ID_LIST_PROCEDURES_BUTTON_ADD       1016 
#define ID_LIST_PROCEDURES_BUTTON_DELETE    1017
#define ID_LIST_PROCEDURES_BUTTON_CHANGE    1018
#define ID_LIST_PROCEDURES_TEXT             1019

    LRESULT CALLBACK EditProcedures(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        static HWND hlistBox;
        static LV_COLUMN colNames;
        static LV_ITEM itemNames;

        static HWND hlistButtonAdd;
        static HWND hlistButtonDelete;
        static HWND hlistButtonChange;

        static HWND hlistText;
        static int counter;

        static HFONT hfont;
        static HFONT hfonttext;
        static HDC hdc;
        static PAINTSTRUCT ps;

        static int textlenght;

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
                textlenght = 128;
                counter = 0;

                RECT rParent;

                GetClientRect(hwnd, &rParent);
                hlistBox = CreateWindowEx(
                                0L,
                                WC_LISTVIEW,
                                TEXT(""),
                                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                                35,
                                40,
                                300,
                                375,
                                hwnd,
                                (HMENU) ID_LIST_PROCEDURES,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonAdd = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Add"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                100,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_PROCEDURES_BUTTON_ADD,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonDelete = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Delete"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                300,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_PROCEDURES_BUTTON_DELETE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonChange = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Change"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                340,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_PROCEDURES_BUTTON_CHANGE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistText = CreateWindow(
                                TEXT("EDIT"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                                345,
                                55,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_PROCEDURES_TEXT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);
                
                Edit_LimitText(hlistText, textlenght);
                // инициализация таблицы
                colNames = { 0 };
                colNames.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
                colNames.fmt = LVCFMT_LEFT;
                colNames.cx = 250;

                colNames.iSubItem = 0;
                colNames.pszText = TEXT(const_cast<char*>("Names"));
                ListView_InsertColumn(hlistBox, 0, &colNames); 

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                itemNames = { 0 };
                itemNames.mask = LVIF_TEXT;

                // добавляем элементы в таблицу перед открытием окна
                for (TObj<DeseaseName>* r = db.procedures_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());   
                    std::string name(str.begin(), str.end());
                    itemNames.iItem = counter++;
                    itemNames.pszText = const_cast<char*>(name.c_str());
                    ListView_InsertItem(hlistBox, &itemNames);
                }

                SendMessage(hlistButtonAdd, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonDelete, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonChange, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hlistBox);

                UpdateWindow(hlistButtonAdd);
                UpdateWindow(hlistButtonDelete);
                UpdateWindow(hlistButtonChange);

                SendMessage(hlistText, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                UpdateWindow(hlistText);

                break;
            }
            case WM_COMMAND:
            {   
                int i;
                if ((i = LOWORD(wparam)) > ID_LIST_PROCEDURES && i < ID_LIST_PROCEDURES_TEXT)
                { // check if buttons
                    int len = GetWindowTextLength(hlistText) + 1;
                    TCHAR buf[textlenght + 1];

                    GetWindowText(hlistText, buf, len); // получаем текст из окна редактирования

                    std::string str(buf);
                    switch(i)
                    { 
                        case ID_LIST_PROCEDURES_BUTTON_ADD: // кнопка добавления
                        {  
                            int id;

                            if (!str.empty() && ((id = db.add_procedure(str)) != -1)) // если добавили
                            {
                                std::string name(str.begin(), str.end());
                                itemNames.iItem = counter++;
                                itemNames.pszText = const_cast<char*>(name.c_str());
                                ListView_InsertItem(hlistBox, &itemNames); // добавляем в таблицу
                                db.dump();
                            }
                            SetWindowText(hlistText, TEXT(""));

                            
                            break;
                        }
                        case ID_LIST_PROCEDURES_BUTTON_DELETE: // кнопка удаления
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED); // получаем выделенный элемени
                            
                            if (id > -1)
                            {
                                if (db.remove_procedure(id)) // удаляем из списка
                                    SendMessage(hlistBox, LVM_DELETEITEM, id, 0); // удаляем из таблицы
                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                            }

                            break;
                        }
                        case ID_LIST_PROCEDURES_BUTTON_CHANGE: // кнопка изменения
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED); // получаем выделенный элемент
                            
                            if (id > -1)
                            {
                                std::string name(str.begin(), str.end());
                                TObj<DeseaseName>* o = db.procedures_table()->at_pos(id);
                                if (o) // если элемент есть
                                {
                                    if (db.change_procedure(o, str) != -1) // изменяем элемент
                                        ListView_SetItemText(hlistBox, id, 0, const_cast<char*>(name.c_str())); // изменяем элемент в таблице
                                }

                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                                SetWindowText(hlistText, TEXT(""));
                            }

                            break;
                        }
                    }
                    break;
                }

                break;
            }
            case WM_SHOWWINDOW:
            {
                if (wparam)
                    std::cout << "procedures: focus\n";
                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 35, 20, TEXT("Procedure"), 9);
                TextOut(hdc, 345, 40, TEXT("Name"), 4);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

#define ID_LIST_THREATMENT                  1020   
#define ID_LIST_THREATMENT_BUTTON_ADD       1021
#define ID_LIST_THREATMENT_BUTTON_DELETE    1022
#define ID_LIST_THREATMENT_BUTTON_CHANGE    1023
#define ID_LIST_THREATMENT_TEXT_NAME        1024
#define ID_LIST_THREATMENT_TEXT_AMOUNT      1025


    LRESULT CALLBACK EditThreatment(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        static HWND hlistBox;
        static LV_COLUMN colNames;
        static LV_ITEM itemNames;
        static int counter;
        
        static HWND hlistButtonAdd;
        static HWND hlistButtonDelete;
        static HWND hlistButtonChange;

        static HWND hlistTextName;
        static HWND hlistTextAmount;

        static HFONT hfont;
        static HFONT hfonttext;
        static HDC hdc;
        static PAINTSTRUCT ps;

        static int textlenght;

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
                textlenght = 128;
                counter = 0;

                RECT rParent;

                GetClientRect(hwnd, &rParent);
                hlistBox = CreateWindowEx(
                                0L,
                                WC_LISTVIEW,
                                TEXT(""),
                                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                                35,
                                40,
                                300,
                                375,
                                hwnd,
                                (HMENU) ID_LIST_THREATMENT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonAdd = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Add"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                150,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_THREATMENT_BUTTON_ADD,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonDelete = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Delete"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                300,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_THREATMENT_BUTTON_DELETE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonChange = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Change"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                340,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_THREATMENT_BUTTON_CHANGE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextName = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                345,
                                55,
                                130,
                                100,
                                hwnd,
                                (HMENU) ID_LIST_THREATMENT_TEXT_NAME,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextAmount = CreateWindow(
                                TEXT("EDIT"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                                345,
                                100,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_THREATMENT_TEXT_AMOUNT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);
                
                Edit_LimitText(hlistTextAmount, 4);
                // инициализация тиблицы
                colNames = { 0 };
                colNames.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                colNames.fmt = LVCFMT_LEFT;
                colNames.cx = 120;

                colNames.iSubItem = 0;
                colNames.pszText = TEXT(const_cast<char*>("Names"));
                ListView_InsertColumn(hlistBox, 0, &colNames);

                colNames.iSubItem = 1;
                colNames.cx = 90;
                colNames.pszText = TEXT(const_cast<char*>("Amount"));
                ListView_InsertColumn(hlistBox, 1, &colNames);

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                itemNames = { 0 };
                itemNames.mask = LVIF_TEXT;
                
                // добавляем элементы в таблицу
                for (TObj<Threatment>* r = db.threatment_table()->root(); r; r = r->next)
                {
                    std::string strName(r->obj->name()->obj->to_string());  
                    std::string strAmount(std::to_string(r->obj->amount()));

                    std::string name(strName.begin(), strName.end());
                    std::string amount(strAmount.begin(), strAmount.end());

                    itemNames.iItem = counter;
                    itemNames.iSubItem = 0;
                    itemNames.pszText = const_cast<char*>(name.c_str());
                    ListView_InsertItem(hlistBox, &itemNames);

                    itemNames.iItem = counter++;
                    itemNames.iSubItem = 1;
                    itemNames.pszText = const_cast<char*>(amount.c_str());
                    ListView_SetItem(hlistBox, &itemNames);

                }

                // инициализация комбобоксов
                for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hlistTextName, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str())); 
                }
                // изменение шрифтов
                SendMessage(hlistButtonAdd, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonDelete, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonChange, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hlistBox);

                UpdateWindow(hlistButtonAdd);
                UpdateWindow(hlistButtonDelete);
                UpdateWindow(hlistButtonChange);

                SendMessage(hlistTextName, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                SendMessage(hlistTextAmount, WM_SETFONT, (WPARAM) hfonttext, TRUE);

                UpdateWindow(hlistTextName);
                UpdateWindow(hlistTextAmount);

                break;
            }
            case WM_COMMAND:
            {   
                int i;
                if ((i = LOWORD(wparam)) > ID_LIST_THREATMENT && i < ID_LIST_THREATMENT_TEXT_NAME)
                { // check if buttons
                    int chosenMedicine = SendMessage(hlistTextName, CB_GETCURSEL, 0, 0); // получаем выбранный элемент из лекарств
                    std::string amount;
                    int am = 0;
                    int len = GetWindowTextLength(hlistTextAmount) + 1;

                    TCHAR buf[textlenght + 1];

                    GetWindowText(hlistTextAmount, buf, len); // получаем текст количества
                    LPSTR ptr = buf;
                    if (len - 1) // проверяем введенное количество на введенное число
                    {
                        std::string amount;
                        int end = len - 1;
                        int i = 0;
                        for (; i < end; i++)
                        {
                            if (!isdigit(buf[i]))
                            {
                                MessageBox(hlistTextAmount, TEXT("Amount is not a number!"),
                                    TEXT("Warning"), MB_OK | MB_ICONERROR);
                                len = 0;
                                break;
                            }
                            
                        }
                        if (len && i)
                        {
                            am = std::atoi(buf);
                            if (am <= 0)
                            {
                                MessageBox(hlistTextAmount, TEXT("Amount can't be 0 or less!"),
                                    TEXT("Warning"), MB_OK | MB_ICONERROR);
                                len = 0;
                                SetWindowText(hlistTextAmount, TEXT(""));
                            }
                        }
                        else
                            SetWindowText(hlistTextAmount, TEXT(""));
                    }
                    

                    switch(i)
                    { 
                        case ID_LIST_THREATMENT_BUTTON_ADD: // кнопка добавления
                        {  
                            if (len)
                            {
                                TObj<MedicineName>* o = db.medicines_table()->at_pos(chosenMedicine); // получаем лекарство

                                if (o && ((db.add_threatment(o, am) != -1))) // добавляем в список
                                { // затем в таблицу
                                    std::string str(o->obj->to_string());
                                    std::string name(str.begin(), str.end());
                                    std::string a(std::to_string(am));

                                    itemNames.iItem = counter;
                                    itemNames.iSubItem = 0;
                                    itemNames.pszText = const_cast<char*>(name.c_str());
                                    ListView_InsertItem(hlistBox, &itemNames);

                                    itemNames.iItem = counter++;
                                    itemNames.iSubItem = 1;
                                    itemNames.pszText = const_cast<char*>(a.c_str());
                                    ListView_SetItem(hlistBox, &itemNames);

                                    db.dump(); // сохраняем в файл
                                }
                                SetWindowText(hlistTextAmount, TEXT(""));
                                SendMessage(hlistTextName, CB_SETCURSEL, -1, 0);    

                            }
                            break;
                        }
                        case ID_LIST_THREATMENT_BUTTON_DELETE: // кнопка удаления
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED); // получаем выделенный элемент
                            
                            if (id > -1)
                            {
                                if (db.remove_threatment(id))
                                {
                                    SendMessage(hlistBox, LVM_DELETEITEM, id, 0);
                                    counter--;
                                }

                                
                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                            }
                            break;
                        }
                        case ID_LIST_THREATMENT_BUTTON_CHANGE: // кнопка изменения
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                            
                            if (id > -1)
                            {
                                TObj<MedicineName>* o = db.medicines_table()->at_pos(chosenMedicine);
                                
                                TObj<Threatment>* t = db.threatment_table()->at_pos(id);
                                if (o && t)
                                {
                                    if (db.change_threatment(t, o, am) != -1)
                                    {
                                        std::string str(o->obj->to_string());
                                        std::string name(str.begin(), str.end());
                                        std::string a(std::to_string(am));

                                        itemNames.iItem = id;
                                        itemNames.iSubItem = 0;
                                        itemNames.pszText = const_cast<char*>(name.c_str());
                                        ListView_SetItem(hlistBox, &itemNames);

                                        itemNames.iItem = id;
                                        itemNames.iSubItem = 1;
                                        itemNames.pszText = const_cast<char*>(a.c_str());
                                        ListView_SetItem(hlistBox, &itemNames);
                                        
                                    }
                                }

                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);

                                SetWindowText(hlistTextAmount, TEXT(""));
                            }
                            break;
                        }
                    }
                    break;
                }

                break;
            }
            case WM_SHOWWINDOW: // переинициализация всех элементов при открытии окна
            {
                if (wparam)
                {
                    std::cout << "threat: focus\n";
                    std::cout << "updating combobox\n";
                    SendMessage(hlistTextName, CB_RESETCONTENT, 0, 0);
                    for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hlistTextName, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str())); 
                    }
                    std::cout << "updating list\n";
                    SendMessage(hlistBox, LVM_DELETEALLITEMS, 0, 0);
                    counter = 0;
                    for (TObj<Threatment>* r = db.threatment_table()->root(); r; r = r->next)
                    {
                        std::string strName(r->obj->name()->obj->to_string());  
                        std::string strAmount(std::to_string(r->obj->amount()));

                        std::string name(strName.begin(), strName.end());
                        std::string amount(strAmount.begin(), strAmount.end());

                        itemNames.iItem = counter;
                        itemNames.iSubItem = 0;
                        itemNames.pszText = const_cast<char*>(name.c_str());
                        ListView_InsertItem(hlistBox, &itemNames);

                        itemNames.iItem = counter++;
                        itemNames.iSubItem = 1;
                        itemNames.pszText = const_cast<char*>(amount.c_str());
                        ListView_SetItem(hlistBox, &itemNames);
                    }
                }
                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 35, 20, TEXT("List of recipes"), 15);
                TextOut(hdc, 345, 40, TEXT("Name"), 4);
                TextOut(hdc, 345, 85, TEXT("Amount"), 6);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

// дальше все буквально так же

#define ID_LIST_DESEASE                     1026   
#define ID_LIST_DESEASE_BUTTON_ADD          1027
#define ID_LIST_DESEASE_BUTTON_DELETE       1028
#define ID_LIST_DESEASE_BUTTON_CHANGE       1029
#define ID_LIST_DESEASE_TEXT_NAME           1030
#define ID_LIST_DESEASE_TEXT_SYMPTOME       1031
#define ID_LIST_DESEASE_TEXT_PROCEDURE      1032
#define ID_LIST_DESEASE_TEXT_THREAT         1033

    LRESULT CALLBACK EditDTable(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        static HWND hlistBox;
        static LV_COLUMN colNames;
        static LV_ITEM itemNames;
        static int counter;

        static HWND hlistButtonAdd;
        static HWND hlistButtonDelete;
        static HWND hlistButtonChange;

        static HWND hlistTextName;
        static HWND hlistTextSymptome;
        static HWND hlistTextProcedure;
        static HWND hlistTextThreat;

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
                counter = 0;

                RECT rParent;

                GetClientRect(hwnd, &rParent);
                hlistBox = CreateWindowEx(
                                0L,
                                WC_LISTVIEW,
                                TEXT(""),
                                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                                35,
                                40,
                                300,
                                375,
                                hwnd,
                                (HMENU) ID_LIST_DESEASE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonAdd = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Add"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                240,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_DESEASE_BUTTON_ADD,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonDelete = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Delete"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                300,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_DESEASE_BUTTON_DELETE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonChange = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Change"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                340,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_DESEASE_BUTTON_CHANGE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextName = CreateWindow( 
                                TEXT("COMBOBOX"),
                                NULL,
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                345,
                                55,
                                130,
                                100,
                                hwnd,
                                (HMENU) ID_LIST_DESEASE_TEXT_NAME,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextSymptome = CreateWindow(
                                TEXT("COMBOBOX"),
                                NULL,
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                345,
                                100,
                                130,
                                100,
                                hwnd,
                                (HMENU) ID_LIST_DESEASE_TEXT_SYMPTOME,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);
                hlistTextProcedure = CreateWindow(
                                TEXT("COMBOBOX"),
                                NULL,
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                345,
                                145,
                                130,
                                100,
                                hwnd,
                                (HMENU) ID_LIST_DESEASE_TEXT_PROCEDURE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextThreat = CreateWindow(
                                TEXT("COMBOBOX"),
                                NULL,
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                345,
                                190,
                                130,
                                100,
                                hwnd,
                                (HMENU) ID_LIST_DESEASE_TEXT_THREAT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                colNames = { 0 };
                colNames.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                colNames.fmt = LVCFMT_LEFT;
                colNames.cx = 80;

                colNames.iSubItem = 0;
                colNames.pszText = TEXT(const_cast<char*>("Name"));
                ListView_InsertColumn(hlistBox, 0, &colNames);

                colNames.iSubItem = 1;
                colNames.cx = 80;
                colNames.pszText = TEXT(const_cast<char*>("Symptome"));
                ListView_InsertColumn(hlistBox, 1, &colNames);

                colNames.iSubItem = 2;
                colNames.cx = 80;
                colNames.pszText = TEXT(const_cast<char*>("Procedure"));
                ListView_InsertColumn(hlistBox, 2, &colNames);

                colNames.iSubItem = 3;
                colNames.cx = 80;
                colNames.pszText = TEXT(const_cast<char*>("Threat"));
                ListView_InsertColumn(hlistBox, 3, &colNames);

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                itemNames = { 0 };
                itemNames.mask = LVIF_TEXT;
                
                // add items;
                for (TObj<DeseaseDBEntry>* r = db.deseasedb_table()->root(); r; r = r->next)
                {
                    std::string strName(r->obj->name->obj->to_string());  
                    std::string strSymptome(r->obj->symptome->obj->to_string());
                    std::string strProcedure(r->obj->procedure->obj->to_string());
                    std::string strThreat(r->obj->threatment->obj->name()->obj->to_string());

                    std::string name(strName.begin(), strName.end());
                    std::string symptome(strSymptome.begin(), strSymptome.end());
                    std::string procedure(strProcedure.begin(), strProcedure.end());
                    std::string threat(strThreat.begin(), strThreat.end());

                    itemNames.iItem = counter;
                    itemNames.iSubItem = 0;
                    itemNames.pszText = const_cast<char*>(name.c_str());
                    ListView_InsertItem(hlistBox, &itemNames);

                    itemNames.iItem = counter;
                    itemNames.iSubItem = 1;
                    itemNames.pszText = const_cast<char*>(symptome.c_str());
                    ListView_SetItem(hlistBox, &itemNames);

                    itemNames.iItem = counter;
                    itemNames.iSubItem = 2;
                    itemNames.pszText = const_cast<char*>(procedure.c_str());
                    ListView_SetItem(hlistBox, &itemNames);

                    itemNames.iItem = counter++;
                    itemNames.iSubItem = 3;
                    itemNames.pszText = const_cast<char*>(threat.c_str());
                    ListView_SetItem(hlistBox, &itemNames);

                }

                //init comboboxes;
                for (TObj<DeseaseName>* r = db.names_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hlistTextName, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                for (TObj<DeseaseName>* r = db.symptomes_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hlistTextSymptome, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                for (TObj<DeseaseName>* r = db.procedures_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hlistTextProcedure, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                for (TObj<Threatment>* r = db.threatment_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hlistTextThreat, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                SendMessage(hlistButtonAdd, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonDelete, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonChange, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hlistBox);

                UpdateWindow(hlistButtonAdd);
                UpdateWindow(hlistButtonDelete);
                UpdateWindow(hlistButtonChange);

                SendMessage(hlistTextName, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                SendMessage(hlistTextSymptome, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                SendMessage(hlistTextProcedure, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                SendMessage(hlistTextThreat, WM_SETFONT, (WPARAM) hfonttext, TRUE);

                UpdateWindow(hlistTextName);
                UpdateWindow(hlistTextSymptome);
                UpdateWindow(hlistTextProcedure);
                UpdateWindow(hlistTextThreat);

                break;
            }
            case WM_COMMAND:
            {   
                int i;
                if ((i = LOWORD(wparam)) > ID_LIST_DESEASE && i < ID_LIST_DESEASE_TEXT_SYMPTOME)
                { // check if buttons
                    int chosenN = SendMessage(hlistTextName, CB_GETCURSEL, 0, 0);
                    int chosenS = SendMessage(hlistTextSymptome, CB_GETCURSEL, 0, 0);
                    int chosenP = SendMessage(hlistTextProcedure, CB_GETCURSEL, 0, 0);
                    int chosenT = SendMessage(hlistTextThreat, CB_GETCURSEL, 0, 0);
                    
                    switch(i)
                    { 
                        case ID_LIST_DESEASE_BUTTON_ADD:
                        {  
                            if (chosenN >= 0 && chosenS >= 0 && chosenP >= 0 && chosenT >= 0)
                            {
                                TObj<DeseaseName>* n = db.names_table()->at_pos(chosenN);
                                TObj<DeseaseName>* s = db.symptomes_table()->at_pos(chosenS);
                                TObj<DeseaseName>* p = db.procedures_table()->at_pos(chosenP);
                                TObj<Threatment>* t = db.threatment_table()->at_pos(chosenT);

                                if (n && s && p && t && ((db.add_desease(n, s, p, t) != -1))) // добавление да
                                {
                                    std::string strn(n->obj->to_string());
                                    std::string strs(s->obj->to_string());
                                    std::string strp(p->obj->to_string());
                                    std::string strt(t->obj->name()->obj->to_string());

                                    std::string name(strn.begin(), strn.end());
                                    std::string symptome(strs.begin(), strs.end());
                                    std::string procedure(strp.begin(), strp.end());
                                    std::string threatment(strt.begin(), strt.end());

                                    itemNames.iItem = counter;
                                    itemNames.iSubItem = 0;
                                    itemNames.pszText = const_cast<char*>(name.c_str());
                                    ListView_InsertItem(hlistBox, &itemNames);

                                    itemNames.iItem = counter;
                                    itemNames.iSubItem = 1;
                                    itemNames.pszText = const_cast<char*>(symptome.c_str());
                                    ListView_SetItem(hlistBox, &itemNames);

                                    itemNames.iItem = counter;
                                    itemNames.iSubItem = 2;
                                    itemNames.pszText = const_cast<char*>(procedure.c_str());
                                    ListView_SetItem(hlistBox, &itemNames);

                                    itemNames.iItem = counter++;
                                    itemNames.iSubItem = 3;
                                    itemNames.pszText = const_cast<char*>(threatment.c_str());
                                    ListView_SetItem(hlistBox, &itemNames);

                                    db.dump();
                                }
                                SendMessage(hlistTextName, CB_SETCURSEL, -1, 0);
                                SendMessage(hlistTextSymptome, CB_SETCURSEL, -1, 0);
                                SendMessage(hlistTextProcedure, CB_SETCURSEL, -1, 0);
                                SendMessage(hlistTextThreat, CB_SETCURSEL, -1, 0);

                            }
                            break;
                        }
                        case ID_LIST_DESEASE_BUTTON_DELETE:
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                            
                            if (id > -1)
                            {
                                if (db.remove_desease(id))
                                {
                                    SendMessage(hlistBox, LVM_DELETEITEM, id, 0);
                                    counter--;
                                }

                                
                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                            }

                            break;
                        }
                        case ID_LIST_DESEASE_BUTTON_CHANGE:
                        {
                            if (chosenN >= 0 && chosenS >= 0 && chosenP >= 0 && chosenT >= 0)
                            {
                                int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                                
                                if (id > -1)
                                {
                                    TObj<DeseaseName>* n = db.names_table()->at_pos(chosenN);
                                    TObj<DeseaseName>* s = db.symptomes_table()->at_pos(chosenS);
                                    TObj<DeseaseName>* p = db.procedures_table()->at_pos(chosenP);
                                    TObj<Threatment>* t = db.threatment_table()->at_pos(chosenT);
                                    
                                    TObj<DeseaseDBEntry>* d = db.deseasedb_table()->at_pos(id);
                                    if (d)
                                    {
                                        if (db.change_desease(d, n, s, p, t) != -1)
                                        {
                                            std::string strn(n->obj->to_string());
                                            std::string strs(s->obj->to_string());
                                            std::string strp(p->obj->to_string());
                                            std::string strt(t->obj->name()->obj->to_string());

                                            std::string name(strn.begin(), strn.end());
                                            std::string symptome(strs.begin(), strs.end());
                                            std::string procedure(strp.begin(), strp.end());
                                            std::string threatment(strt.begin(), strt.end());

                                            itemNames.iItem = id;
                                            itemNames.iSubItem = 0;
                                            itemNames.pszText = const_cast<char*>(name.c_str());
                                            ListView_SetItem(hlistBox, &itemNames);

                                            itemNames.iItem = id;
                                            itemNames.iSubItem = 1;
                                            itemNames.pszText = const_cast<char*>(symptome.c_str());
                                            ListView_SetItem(hlistBox, &itemNames);

                                            itemNames.iItem = id;
                                            itemNames.iSubItem = 2;
                                            itemNames.pszText = const_cast<char*>(procedure.c_str());
                                            ListView_SetItem(hlistBox, &itemNames);

                                            itemNames.iItem = id;
                                            itemNames.iSubItem = 3;
                                            itemNames.pszText = const_cast<char*>(threatment.c_str());
                                            ListView_SetItem(hlistBox, &itemNames);
                                        }
                                    }

                                    int len = ListView_GetItemCount(hlistBox);
                                    for (int i = 0; i < len; i++)
                                        ListView_Update(hlistBox,i);

                                    SendMessage(hlistTextName, CB_SETCURSEL, -1, 0);
                                    SendMessage(hlistTextSymptome, CB_SETCURSEL, -1, 0);
                                    SendMessage(hlistTextProcedure, CB_SETCURSEL, -1, 0);
                                    SendMessage(hlistTextThreat, CB_SETCURSEL, -1, 0);
                                }
                            }
                            std::cout << "-----\n";
                            for (TObj<DeseaseDBEntry>* r = db.deseasedb_table()->root(); r; r = r->next)
                                std::cout << r->obj->to_string() << std::endl;
                            std::cout << "-----\n";
                            break;
                        }
                    }
                    break;
                }

                break;
            }
            case WM_SHOWWINDOW:
            {
                if (wparam)
                {
                    std::cout << "analog: focus\n";
                    std::cout << "updating comboboxes\n";
                    SendMessage(hlistTextName, CB_RESETCONTENT, 0, 0);
                    SendMessage(hlistTextSymptome, CB_RESETCONTENT, 0, 0);
                    SendMessage(hlistTextProcedure, CB_RESETCONTENT, 0, 0);
                    SendMessage(hlistTextThreat, CB_RESETCONTENT, 0, 0);
                    for (TObj<DeseaseName>* r = db.names_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hlistTextName, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }

                    for (TObj<DeseaseName>* r = db.symptomes_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hlistTextSymptome, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }

                    for (TObj<DeseaseName>* r = db.procedures_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hlistTextProcedure, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }

                    for (TObj<Threatment>* r = db.threatment_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hlistTextThreat, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }
                    std::cout << "updating list\n";
                    SendMessage(hlistBox, LVM_DELETEALLITEMS, 0, 0);
                    counter = 0;
                    for (TObj<DeseaseDBEntry>* r = db.deseasedb_table()->root(); r; r = r->next)
                    {
                        std::string strName(r->obj->name->obj->to_string());  
                        std::string strSymptome(r->obj->symptome->obj->to_string());
                        std::string strProcedure(r->obj->procedure->obj->to_string());
                        std::string strThreat(r->obj->threatment->obj->name()->obj->to_string());

                        std::string name(strName.begin(), strName.end());
                        std::string symptome(strSymptome.begin(), strSymptome.end());
                        std::string procedure(strProcedure.begin(), strProcedure.end());
                        std::string threat(strThreat.begin(), strThreat.end());

                        itemNames.iItem = counter;
                        itemNames.iSubItem = 0;
                        itemNames.pszText = const_cast<char*>(name.c_str());
                        ListView_InsertItem(hlistBox, &itemNames);

                        itemNames.iItem = counter;
                        itemNames.iSubItem = 1;
                        itemNames.pszText = const_cast<char*>(symptome.c_str());
                        ListView_SetItem(hlistBox, &itemNames);

                        itemNames.iItem = counter;
                        itemNames.iSubItem = 2;
                        itemNames.pszText = const_cast<char*>(procedure.c_str());
                        ListView_SetItem(hlistBox, &itemNames);

                        itemNames.iItem = counter++;
                        itemNames.iSubItem = 3;
                        itemNames.pszText = const_cast<char*>(threat.c_str());
                        ListView_SetItem(hlistBox, &itemNames);

                    }
                }
                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 35, 20, TEXT("Table of diseases"), 17);
                TextOut(hdc, 345, 40, TEXT("Disease"), 7);
                TextOut(hdc, 345, 85, TEXT("Symptome"), 8);
                TextOut(hdc, 345, 130, TEXT("Procedure"), 9);
                TextOut(hdc, 345, 175, TEXT("Treatment"), 10);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

#define ID_LIST_MEDICINE                    1034   
#define ID_LIST_MEDICINE_BUTTON_ADD         1035
#define ID_LIST_MEDICINE_BUTTON_DELETE      1036
#define ID_LIST_MEDICINE_BUTTON_CHANGE      1037
#define ID_LIST_MEDICINE_TEXT               1038

    LRESULT CALLBACK EditMedicine(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        static HWND hlistBox;
        static LV_COLUMN colNames;
        static LV_ITEM itemNames;

        static HWND hlistButtonAdd;
        static HWND hlistButtonDelete;
        static HWND hlistButtonChange;

        static HWND hlistText;
        static int counter;

        static HFONT hfont;
        static HFONT hfonttext;
        static HDC hdc;
        static PAINTSTRUCT ps;

        static int textlenght;

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
                textlenght = 128;
                counter = 0;

                RECT rParent;

                GetClientRect(hwnd, &rParent);
                hlistBox = CreateWindowEx(
                                0L,
                                WC_LISTVIEW,
                                TEXT(""),
                                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                                35,
                                40,
                                300,
                                375,
                                hwnd,
                                (HMENU) ID_LIST_MEDICINE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonAdd = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Add"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                100,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_MEDICINE_BUTTON_ADD,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonDelete = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Delete"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                300,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_MEDICINE_BUTTON_DELETE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonChange = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Change"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                340,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_MEDICINE_BUTTON_CHANGE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistText = CreateWindow(
                                TEXT("EDIT"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                                345,
                                55,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_MEDICINE_TEXT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);
                
                Edit_LimitText(hlistText, textlenght);

                colNames = { 0 };
                colNames.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
                colNames.fmt = LVCFMT_LEFT;
                colNames.cx = 250;

                colNames.iSubItem = 0;
                colNames.pszText = TEXT(const_cast<char*>("Names"));
                ListView_InsertColumn(hlistBox, 0, &colNames); 

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                itemNames = { 0 };
                itemNames.mask = LVIF_TEXT;


                for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());   
                    std::string name(str.begin(), str.end());
                    itemNames.iItem = counter++;
                    itemNames.pszText = const_cast<char*>(name.c_str());
                    ListView_InsertItem(hlistBox, &itemNames);
                }

                SendMessage(hlistButtonAdd, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonDelete, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonChange, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hlistBox);

                UpdateWindow(hlistButtonAdd);
                UpdateWindow(hlistButtonDelete);
                UpdateWindow(hlistButtonChange);

                SendMessage(hlistText, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                UpdateWindow(hlistText);

                break;
            }
            case WM_COMMAND:
            {   
                int i;
                if ((i = LOWORD(wparam)) > ID_LIST_MEDICINE && i < ID_LIST_MEDICINE_TEXT)
                { // check if buttons
                    int len = GetWindowTextLength(hlistText) + 1;
                    TCHAR buf[textlenght + 1];

                    GetWindowText(hlistText, buf, len);

                    std::string str(buf);
                    switch(i)
                    { 
                        case ID_LIST_MEDICINE_BUTTON_ADD:
                        {  
                            int id;

                            if (!str.empty() && ((id = db.add_medicine(str)) != -1)) // 
                            {
                                std::string name(str.begin(), str.end());
                                itemNames.iItem = counter++;
                                itemNames.pszText = const_cast<char*>(name.c_str());
                                ListView_InsertItem(hlistBox, &itemNames);
                                db.dump();
                            }
                            SetWindowText(hlistText, TEXT(""));

                            
                            break;
                        }
                        case ID_LIST_MEDICINE_BUTTON_DELETE:
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

                            if (id > -1)
                            {
                                if (db.remove_medicine(id))
                                    SendMessage(hlistBox, LVM_DELETEITEM, id, 0);
                      
                                for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
     
                                int len = ListView_GetItemCount(hlistBox);
                                
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                            }
                            

                            break;
                        }
                        case ID_LIST_MEDICINE_BUTTON_CHANGE:
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                            
                            if (id > -1)
                            {
                                std::string name(str.begin(), str.end());
                                TObj<MedicineName>* o = db.medicines_table()->at_pos(id);
                                if (o)
                                {
                                    if (db.change_medicine(o, str) != -1)
                                        ListView_SetItemText(hlistBox, id, 0, const_cast<char*>(name.c_str()));
                                }

                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                                SetWindowText(hlistText, TEXT(""));
                            }

                            break;
                        }
                    }
                    break;
                }
                if ((i = LOWORD(wparam)) == ID_LIST_MEDICINE)
                {
                    //std::cout << "listbox '" << SendMessage(hlistBox, LB_GETCURSEL, 0, 0) << "'\n";
                }
                if ((i = LOWORD(wparam)) == ID_LIST_MEDICINE_TEXT)
                {

                    //std::cout << "edit: '" << GetWindowTextLength(hlistText) << std::endl;
                }

                break;
            }
            case WM_SHOWWINDOW:
            {
                if (wparam)
                    std::cout << "medicines: focus\n";
                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 35, 20, TEXT("Medicines"), 9);
                TextOut(hdc, 345, 40, TEXT("Name"), 4);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

#define ID_LIST_STOCK                  1039   
#define ID_LIST_STOCK_BUTTON_ADD       1040
#define ID_LIST_STOCK_BUTTON_DELETE    1041
#define ID_LIST_STOCK_BUTTON_CHANGE    1042
#define ID_LIST_STOCK_TEXT_NAME        1043
#define ID_LIST_STOCK_TEXT_AMOUNT      1044

    LRESULT CALLBACK EditStock(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        static HWND hlistBox;
        static LV_COLUMN colNames;
        static LV_ITEM itemNames;
        static int counter;
        
        static HWND hlistButtonAdd;
        static HWND hlistButtonDelete;
        static HWND hlistButtonChange;

        static HWND hlistTextName;
        static HWND hlistTextAmount;

        static HFONT hfont;
        static HFONT hfonttext;
        static HDC hdc;
        static PAINTSTRUCT ps;

        static int textlenght;

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
                textlenght = 128;
                counter = 0;

                RECT rParent;

                GetClientRect(hwnd, &rParent);
                hlistBox = CreateWindowEx(
                                0L,
                                WC_LISTVIEW,
                                TEXT(""),
                                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                                35,
                                40,
                                300,
                                375,
                                hwnd,
                                (HMENU) ID_LIST_STOCK,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonAdd = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Add"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                150,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_STOCK_BUTTON_ADD,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonDelete = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Delete"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                300,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_STOCK_BUTTON_DELETE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonChange = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Change"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                340,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_STOCK_BUTTON_CHANGE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextName = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                345,
                                55,
                                130,
                                100,
                                hwnd,
                                (HMENU) ID_LIST_STOCK_TEXT_NAME,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextAmount = CreateWindow(
                                TEXT("EDIT"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                                345,
                                100,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_STOCK_TEXT_AMOUNT,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                Edit_LimitText(hlistTextAmount, 4);

                colNames = { 0 };
                colNames.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                colNames.fmt = LVCFMT_LEFT;
                colNames.cx = 120;

                colNames.iSubItem = 0;
                colNames.pszText = TEXT(const_cast<char*>("Names"));
                ListView_InsertColumn(hlistBox, 0, &colNames);

                colNames.iSubItem = 1;
                colNames.cx = 90;
                colNames.pszText = TEXT(const_cast<char*>("Amount"));
                ListView_InsertColumn(hlistBox, 1, &colNames);

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                itemNames = { 0 };
                itemNames.mask = LVIF_TEXT;
                
                // add items;
                for (TObj<MedicineDBEntry>* r = db.stock_table()->root(); r; r = r->next)
                {
                    std::string strName(r->obj->name()->obj->to_string());  
                    std::string strAmount(std::to_string(r->obj->amount()));

                    std::string name(strName.begin(), strName.end());
                    std::string amount(strAmount.begin(), strAmount.end());

                    itemNames.iItem = counter;
                    itemNames.iSubItem = 0;
                    itemNames.pszText = const_cast<char*>(name.c_str());
                    ListView_InsertItem(hlistBox, &itemNames);

                    itemNames.iItem = counter++;
                    itemNames.iSubItem = 1;
                    itemNames.pszText = const_cast<char*>(amount.c_str());
                    ListView_SetItem(hlistBox, &itemNames);

                }

                //init combobox;
                for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hlistTextName, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str())); 
                }

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                SendMessage(hlistButtonAdd, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonDelete, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonChange, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hlistBox);

                UpdateWindow(hlistButtonAdd);
                UpdateWindow(hlistButtonDelete);
                UpdateWindow(hlistButtonChange);

                SendMessage(hlistTextName, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                SendMessage(hlistTextAmount, WM_SETFONT, (WPARAM) hfonttext, TRUE);

                UpdateWindow(hlistTextName);
                UpdateWindow(hlistTextAmount);

                break;
            }
            case WM_COMMAND:
            {   
                int i;
                if ((i = LOWORD(wparam)) > ID_LIST_STOCK && i < ID_LIST_STOCK_TEXT_NAME)
                { // check if buttons
                    int chosenMedicine = SendMessage(hlistTextName, CB_GETCURSEL, 0, 0);
                    std::string amount;
                    int am = 0;
                    int len = GetWindowTextLength(hlistTextAmount) + 1;

                    TCHAR buf[textlenght + 1];

                    GetWindowText(hlistTextAmount, buf, len);
                    LPSTR ptr = buf;
                    if (len)
                    {
                        std::string amount;
                        int end = len - 1;
                        int i = 0;
                        for (; i < end; i++)
                        {
                            if (!isdigit(buf[i]))
                            {
                                MessageBox(hlistTextAmount, TEXT("Amount is not a number!"),
                                    TEXT("Warning"), MB_OK | MB_ICONERROR);
                                len = 0;
                                break;
                            }
                            
                        }
                        if (len && i)
                        {
                            am = std::atoi(buf);
                            if (am <= 0)
                            {
                                MessageBox(hlistTextAmount, TEXT("Amount can't be 0 or less!"),
                                    TEXT("Warning"), MB_OK | MB_ICONERROR);
                                len = 0;
                            }
                        }
                        SetWindowText(hlistTextAmount, TEXT(""));
                    }

                    switch(i)
                    { 
                        case ID_LIST_STOCK_BUTTON_ADD:
                        {  
                            if (len)
                            {
                                TObj<MedicineName>* o = db.medicines_table()->at_pos(chosenMedicine);

                                if (o && ((db.add_to_stock(o, am) != -1))) // добавление да
                                {
                                    std::string str(o->obj->to_string());
                                    std::string name(str.begin(), str.end());
                                    std::string a(std::to_string(am));

                                    itemNames.iItem = counter;
                                    itemNames.iSubItem = 0;
                                    itemNames.pszText = const_cast<char*>(name.c_str());
                                    ListView_InsertItem(hlistBox, &itemNames);

                                    itemNames.iItem = counter++;
                                    itemNames.iSubItem = 1;
                                    itemNames.pszText = const_cast<char*>(a.c_str());
                                    ListView_SetItem(hlistBox, &itemNames);

                                    db.dump();
                                }
                                SetWindowText(hlistTextAmount, TEXT(""));
                                SendMessage(hlistTextName, CB_SETCURSEL, -1, 0);    

                            }
                            break;
                        }
                        case ID_LIST_STOCK_BUTTON_DELETE:
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                            
                            if (id > -1)
                            {
                                if (db.remove_from_stock(id))
                                {
                                    SendMessage(hlistBox, LVM_DELETEITEM, id, 0);
                                    counter--;
                                }

                                
                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                            }
                            break;
                        }
                        case ID_LIST_STOCK_BUTTON_CHANGE:
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                            
                            if (id > -1 && len)
                            {
                                TObj<MedicineName>* o = db.medicines_table()->at_pos(chosenMedicine);
                                
                                TObj<MedicineDBEntry>* m = db.stock_table()->at_pos(id);
                                if (o && m)
                                {
                                    if (db.change_stock(m, o, am) != -1)
                                    {
                                        std::string str(o->obj->to_string());
                                        std::string name(str.begin(), str.end());
                                        std::string a(std::to_string(am));

                                        itemNames.iItem = id;
                                        itemNames.iSubItem = 0;
                                        itemNames.pszText = const_cast<char*>(name.c_str());
                                        ListView_SetItem(hlistBox, &itemNames);

                                        itemNames.iItem = id;
                                        itemNames.iSubItem = 1;
                                        itemNames.pszText = const_cast<char*>(a.c_str());
                                        ListView_SetItem(hlistBox, &itemNames);
                                        
                                    }
                                }

                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);

                                SetWindowText(hlistTextAmount, TEXT(""));
                            }
                            break;
                        }
                    }
                    break;
                }

                break;
            }
            case WM_SHOWWINDOW:
            {
                if (wparam)
                {
                    std::cout << "stock: focus\n";
                    std::cout << "updating combobox\n";
                    SendMessage(hlistTextName, CB_RESETCONTENT, 0, 0);
                    for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hlistTextName, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str())); 
                    }
                    std::cout << "updating list\n";
                    SendMessage(hlistBox, LVM_DELETEALLITEMS, 0, 0);
                    counter = 0;
                    for (TObj<MedicineDBEntry>* r = db.stock_table()->root(); r; r = r->next)
                    {
                        std::string strName(r->obj->name()->obj->to_string());  
                        std::string strAmount(std::to_string(r->obj->amount()));

                        std::string name(strName.begin(), strName.end());
                        std::string amount(strAmount.begin(), strAmount.end());

                        itemNames.iItem = counter;
                        itemNames.iSubItem = 0;
                        itemNames.pszText = const_cast<char*>(name.c_str());
                        ListView_InsertItem(hlistBox, &itemNames);

                        itemNames.iItem = counter++;
                        itemNames.iSubItem = 1;
                        itemNames.pszText = const_cast<char*>(amount.c_str());
                        ListView_SetItem(hlistBox, &itemNames);
                    }
                }
                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 35, 20, TEXT("Stock"), 5);
                TextOut(hdc, 345, 40, TEXT("Name"), 4);
                TextOut(hdc, 345, 85, TEXT("Amount"), 6);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

#define ID_LIST_ANALOG                  1045   
#define ID_LIST_ANALOG_BUTTON_ADD       1046
#define ID_LIST_ANALOG_BUTTON_DELETE    1047
#define ID_LIST_ANALOG_BUTTON_CHANGE    1048
#define ID_LIST_ANALOG_TEXT_NAME        1049
#define ID_LIST_ANALOG_TEXT_ANALOG      1050

    LRESULT CALLBACK EditAnalogs(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        static HWND hlistBox;
        static LV_COLUMN colNames;
        static LV_ITEM itemNames;
        static int counter;

        static HWND hlistButtonAdd;
        static HWND hlistButtonDelete;
        static HWND hlistButtonChange;

        static HWND hlistTextName;
        static HWND hlistTextAnalog;

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
                counter = 0;    

                RECT rParent;

                GetClientRect(hwnd, &rParent);
                hlistBox = CreateWindowEx(
                                0L,
                                WC_LISTVIEW,
                                TEXT(""),
                                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                                35,
                                40,
                                300,
                                375,
                                hwnd,
                                (HMENU) ID_LIST_ANALOG,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonAdd = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Add"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                150,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_ANALOG_BUTTON_ADD,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonDelete = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Delete"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                300,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_ANALOG_BUTTON_DELETE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistButtonChange = CreateWindow(
                                TEXT("BUTTON"),
                                TEXT("Change"),
                                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                345,
                                340,
                                130,
                                30,
                                hwnd,
                                (HMENU) ID_LIST_ANALOG_BUTTON_CHANGE,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextName = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                345,
                                55,
                                130,
                                100,
                                hwnd,
                                (HMENU) ID_LIST_ANALOG_TEXT_NAME,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                hlistTextAnalog = CreateWindow(
                                TEXT("COMBOBOX"),
                                TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_NOINTEGRALHEIGHT,
                                345,
                                100,
                                130,
                                100,
                                hwnd,
                                (HMENU) ID_LIST_ANALOG_TEXT_ANALOG,
                                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                NULL);

                colNames = { 0 };
                colNames.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                colNames.fmt = LVCFMT_LEFT;
                colNames.cx = 120;

                colNames.iSubItem = 0;
                colNames.pszText = TEXT(const_cast<char*>("Names"));
                ListView_InsertColumn(hlistBox, 0, &colNames);

                colNames.iSubItem = 1;
                colNames.cx = 120;
                colNames.pszText = TEXT(const_cast<char*>("Analog"));
                ListView_InsertColumn(hlistBox, 1, &colNames);

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                itemNames = { 0 };
                itemNames.mask = LVIF_TEXT;
                
                // add items;
                for (TObj<MedicineAnalog>* r = db.analogs_table()->root(); r; r = r->next)
                {
                    std::string strName(r->obj->name()->obj->to_string());  
                    std::string strAnalog(r->obj->analog()->obj->to_string());

                    std::string name(strName.begin(), strName.end());
                    std::string analog(strAnalog.begin(), strAnalog.end());

                    itemNames.iItem = counter;
                    itemNames.iSubItem = 0;
                    itemNames.pszText = const_cast<char*>(name.c_str());
                    ListView_InsertItem(hlistBox, &itemNames);

                    itemNames.iItem = counter++;
                    itemNames.iSubItem = 1;
                    itemNames.pszText = const_cast<char*>(analog.c_str());
                    ListView_SetItem(hlistBox, &itemNames);

                }

                //init comboboxes;
                for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                {
                    std::string str(r->obj->to_string());
                    std::string name(str.begin(), str.end());
                    SendMessage(hlistTextName, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    SendMessage(hlistTextAnalog, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                }

                SendMessage(hlistBox, WM_SETFONT, (WPARAM) hfont, TRUE);

                SendMessage(hlistButtonAdd, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonDelete, WM_SETFONT, (WPARAM) hfont, TRUE);
                SendMessage(hlistButtonChange, WM_SETFONT, (WPARAM) hfont, TRUE);

                UpdateWindow(hlistBox);

                UpdateWindow(hlistButtonAdd);
                UpdateWindow(hlistButtonDelete);
                UpdateWindow(hlistButtonChange);

                SendMessage(hlistTextName, WM_SETFONT, (WPARAM) hfonttext, TRUE);
                SendMessage(hlistTextAnalog, WM_SETFONT, (WPARAM) hfonttext, TRUE);

                UpdateWindow(hlistTextName);
                UpdateWindow(hlistTextAnalog);

                break;
            }
            case WM_COMMAND:
            {   
                int i;
                if ((i = LOWORD(wparam)) > ID_LIST_ANALOG && i < ID_LIST_ANALOG_TEXT_ANALOG)
                { // check if buttons
                    int chosenMed = SendMessage(hlistTextName, CB_GETCURSEL, 0, 0);
                    int chosenAnalog = SendMessage(hlistTextAnalog, CB_GETCURSEL, 0, 0);

                    
                    switch(i)
                    { 
                        case ID_LIST_ANALOG_BUTTON_ADD:
                        {  
                            if ((chosenMed != chosenAnalog) && chosenMed >= 0 && chosenAnalog >= 0)
                            {
                                TObj<MedicineName>* n = db.medicines_table()->at_pos(chosenMed);
                                TObj<MedicineName>* a = db.medicines_table()->at_pos(chosenAnalog);

                                if (n && a && ((db.add_analog(n, a) != -1))) // добавление да
                                {
                                    std::string strn(n->obj->to_string());
                                    std::string stra(a->obj->to_string());

                                    std::string name(strn.begin(), strn.end());
                                    std::string analog(stra.begin(), stra.end());

                                    itemNames.iItem = counter;
                                    itemNames.iSubItem = 0;
                                    itemNames.pszText = const_cast<char*>(name.c_str());
                                    ListView_InsertItem(hlistBox, &itemNames);

                                    itemNames.iItem = counter++;
                                    itemNames.iSubItem = 1;
                                    itemNames.pszText = const_cast<char*>(analog.c_str());
                                    ListView_SetItem(hlistBox, &itemNames);

                                    db.dump();
                                }
                                SendMessage(hlistTextName, CB_SETCURSEL, -1, 0);
                                SendMessage(hlistTextAnalog, CB_SETCURSEL, -1, 0);
                            }
                            break;
                        }
                        case ID_LIST_ANALOG_BUTTON_DELETE:
                        {
                            int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                            
                            if (id > -1)
                            {
                                if (db.remove_analog(id))
                                {
                                    SendMessage(hlistBox, LVM_DELETEITEM, id, 0);
                                    counter--;
                                }

                                
                                int len = ListView_GetItemCount(hlistBox);
                                for (int i = 0; i < len; i++)
                                    ListView_Update(hlistBox,i);
                            }

                            break;
                        }
                        case ID_LIST_ANALOG_BUTTON_CHANGE:
                        {
                            if ((chosenMed != chosenAnalog) && chosenMed >= 0 && chosenAnalog >= 0)
                            {
                                int id = SendMessage(hlistBox, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                                
                                if (id > -1)
                                {
                                    TObj<MedicineName>* n = db.medicines_table()->at_pos(chosenMed);
                                    TObj<MedicineName>* a = db.medicines_table()->at_pos(chosenAnalog);
                                    
                                    TObj<MedicineAnalog>* m = db.analogs_table()->at_pos(id);
                                    if (m && n && a)
                                    {
                                        if (db.change_analog(m, n, a) != -1)
                                        {
                                            std::string strn(n->obj->to_string());
                                            std::string stra(a->obj->to_string());

                                            std::string name(strn.begin(), strn.end());
                                            std::string analog(stra.begin(), stra.end());

                                            itemNames.iItem = id;
                                            itemNames.iSubItem = 0;
                                            itemNames.pszText = const_cast<char*>(name.c_str());
                                            ListView_SetItem(hlistBox, &itemNames);

                                            itemNames.iItem = id;
                                            itemNames.iSubItem = 1;
                                            itemNames.pszText = const_cast<char*>(analog.c_str());
                                            ListView_SetItem(hlistBox, &itemNames);
                                            
                                        }
                                    }

                                    int len = ListView_GetItemCount(hlistBox);
                                    for (int i = 0; i < len; i++)
                                        ListView_Update(hlistBox,i);

                                    SendMessage(hlistTextName, CB_SETCURSEL, -1, 0);
                                    SendMessage(hlistTextAnalog, CB_SETCURSEL, -1, 0);

                                    
                                }
                            }
                            break;
                        }
                    }
                    break;
                }

                break;
            }
            case WM_SHOWWINDOW:
            {
                if (wparam)
                {
                    std::cout << "analog: focus\n";
                    std::cout << "updating comboboxes\n";
                    SendMessage(hlistTextName, CB_RESETCONTENT, 0, 0);
                    SendMessage(hlistTextAnalog, CB_RESETCONTENT, 0, 0);
                    for (TObj<MedicineName>* r = db.medicines_table()->root(); r; r = r->next)
                    {
                        std::string str(r->obj->to_string());
                        std::string name(str.begin(), str.end());
                        SendMessage(hlistTextName, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                        SendMessage(hlistTextAnalog, CB_ADDSTRING, 0, (LPARAM) const_cast<char*>(name.c_str()));
                    }
                    std::cout << "updating list\n";
                    SendMessage(hlistBox, LVM_DELETEALLITEMS, 0, 0);
                    counter = 0;
                    for (TObj<MedicineAnalog>* r = db.analogs_table()->root(); r; r = r->next)
                    {
                        std::string strName(r->obj->name()->obj->to_string());  
                        std::string strAnalog(r->obj->analog()->obj->to_string());

                        std::string name(strName.begin(), strName.end());
                        std::string analog(strAnalog.begin(), strAnalog.end());

                        itemNames.iItem = counter;
                        itemNames.iSubItem = 0;
                        itemNames.pszText = const_cast<char*>(name.c_str());
                        ListView_InsertItem(hlistBox, &itemNames);

                        itemNames.iItem = counter++;
                        itemNames.iSubItem = 1;
                        itemNames.pszText = const_cast<char*>(analog.c_str());
                        ListView_SetItem(hlistBox, &itemNames);

                    }
                }
                break;
            }
            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                SelectObject(ps.hdc, hfont);
                TextOut(hdc, 35, 20, TEXT("Table of analogs"), 16);
                TextOut(hdc, 345, 40, TEXT("Medicine"), 8);
                TextOut(hdc, 345, 85, TEXT("Analog"), 6);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                DeleteObject(hfont);
                DeleteObject(hfonttext);
                break;
            default:
                return DefWindowProc(hwnd, message, wparam, lparam);
        }

        return 0;
    }

    HWND CreateWindowEdit(HINSTANCE This, HWND hWnd)
    {
        WNDCLASSEX wcMenu;
        HWND hwnd;
        TCHAR EditName[] = TEXT("EditFrame");

        int x = 500;
        int y = 500;
        int pos_x = 0;
        int pos_y = 0;

        RECT main_pos;
        if (GetClientRect(hWnd, &main_pos))
        {
            pos_x = main_pos.left + (main_pos.right - main_pos.left) / 2 - x / 2;
            pos_y = main_pos.top + (main_pos.bottom - main_pos.top) / 2 - y / 2;  
        }
        
        wcMenu.cbSize       = sizeof(WNDCLASSEX);
        wcMenu.style      = CS_HREDRAW | CS_VREDRAW;
        wcMenu.lpfnWndProc = EditWindow;
        wcMenu.cbClsExtra = 0;
        wcMenu.cbWndExtra = 0;
        wcMenu.hInstance  = This;
        wcMenu.hIcon        = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32, 32, 0); //LoadIcon (NULL, IDI_APPLICATION);
        wcMenu.hIconSm      = (HICON)LoadImage(This, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, 0);
        wcMenu.hCursor    = LoadCursor (NULL, IDC_ARROW);
        wcMenu.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wcMenu.lpszMenuName = NULL;
        wcMenu.lpszClassName = EditName;

        if (!RegisterClassEx(&wcMenu))
        {
            MessageBox (NULL, TEXT ("Can't register edit window!"),
                        EditName, MB_ICONERROR);
            return 0;
        }

        hwnd = CreateWindowEx(
                            WS_EX_OVERLAPPEDWINDOW,
                            EditName,        
                            TEXT("Edit"), 
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

    HWND CreateWindowEditTable(HINSTANCE This, HWND hWnd, WNDPROC proc, TCHAR* EditName)
    {
        WNDCLASS wcMenu;
        HWND hwnd;
        RECT rParent;

        int x = 490;
        int y = 444;//444
        int pos_x = 0;
        int pos_y = 23;
        
        wcMenu.style        = CS_HREDRAW | CS_VREDRAW;
        wcMenu.lpfnWndProc = proc;
        wcMenu.cbClsExtra   = 0;
        wcMenu.cbWndExtra = sizeof(long);
        wcMenu.hInstance    = This;
        wcMenu.hIcon        = LoadIcon (NULL, IDI_APPLICATION);
        wcMenu.hCursor  = LoadCursor (NULL, IDC_ARROW);
        wcMenu.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wcMenu.lpszMenuName = NULL;
        wcMenu.lpszClassName = EditName;

        if (!RegisterClass (&wcMenu))
        {
            MessageBox (NULL, TEXT ("Can't register EditT window!"),
                        EditName, MB_ICONERROR);
            return 0;
        }

        hwnd = CreateWindow(EditName,        
                            TEXT("Edit"),
                            WS_CHILD | WS_BORDER,  
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
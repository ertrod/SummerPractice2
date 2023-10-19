#ifndef WEDIT
#define WEDIT

#include "practice.h"

namespace practice
{
    LRESULT CALLBACK EditWindow(HWND, UINT, WPARAM, LPARAM); // главная функция окна редактирования

    // функции редактирования для каждой из таблиц
    LRESULT CALLBACK EditDNames(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK EditSymptomes(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK EditProcedures(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK EditThreatment(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK EditDTable(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK EditMedicine(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK EditStock(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK EditAnalogs(HWND, UINT, WPARAM, LPARAM);

    HWND CreateWindowEdit(HINSTANCE, HWND); // создание окна редактирования

    HWND CreateWindowEditTable(HINSTANCE, HWND, WNDPROC, TCHAR*); // окна для вкладок
}

#endif
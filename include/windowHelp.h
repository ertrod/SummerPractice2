#ifndef WHELP
#define WHELP

#include "practice.h"

namespace practice
{
    LRESULT CALLBACK HelpWindow(HWND, UINT, WPARAM, LPARAM); // главная функция окна помощи

    HWND CreateWindowHelp(HINSTANCE, HWND); // создание окна помощи
}

#endif
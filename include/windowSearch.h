#ifndef WSEARCH
#define WSEARCH

#include "practice.h"

namespace practice
{  
    LRESULT CALLBACK SearchWindow(HWND, UINT, WPARAM, LPARAM); // окно поиска

    HWND CreateWindowSearch(HINSTANCE, HWND); // создание окна поиска

}

#endif  
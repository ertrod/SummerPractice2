#ifndef WMAIN
#define WMAIN

#include "practice.h"

namespace practice
{
    LRESULT CALLBACK MenuWindow(HWND, UINT, WPARAM, LPARAM); // функция меню
    LRESULT CALLBACK MainWindow(HWND, UINT, WPARAM,LPARAM); // функция главного окна

    HWND CreateWindowMain(HINSTANCE); // создание главного окна
    HWND CreateWindowMenu(HINSTANCE, HWND); // создание дочернего окна меню
    
    // функция для бесконечного цикла(winmain по сути, только в первом winmain у меня лишь мьютекс)
    int WINAPI Main(HINSTANCE, HINSTANCE, LPSTR, int); 
}

#endif
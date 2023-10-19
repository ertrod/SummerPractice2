#ifndef WTHREAT
#define WTHREAT

#include "practice.h"

namespace practice
{
    LRESULT CALLBACK ThreatWindow(HWND, UINT, WPARAM, LPARAM); // окно генерации рецепта

    HWND CreateWindowThreat(HINSTANCE, HWND); // создание окна генерации
}

#endif
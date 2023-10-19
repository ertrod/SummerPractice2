#include "practice.h"

using namespace practice;

// change to winmain in future
int WINAPI WinMain (HINSTANCE This, 
                    HINSTANCE Prev,
                    LPSTR cmd, 
                    int mode)
{
    HANDLE mutex; // мутекс необходим для запуска единственного экземпляра приложения
    setlocale(LC_ALL, "ALL"); //??

    mutex = CreateMutex(
        NULL,
        FALSE,
        TEXT("Desease")
    );

    if (mutex == NULL) 
    {
        std::cout << ("CreateMutex error: %d\n", GetLastError());
        return 1;
    }

    DWORD dwLastError = GetLastError();

    if (dwLastError == ERROR_ALREADY_EXISTS) // если экземпляр запущен закрыть приложение
    {
        MessageBox(NULL, TEXT("Экземпляр приложения уже запущен!"), NULL, MB_OK | MB_ICONERROR);
        // Process already running.
        CloseHandle(mutex);
        mutex = NULL;
        return 0;
    }

    int res = Main(This, Prev, cmd, mode);

    CloseHandle(mutex);

    return res;
}
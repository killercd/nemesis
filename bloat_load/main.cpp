#include "main.h"

// a sample exported function
void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

    MessageBoxA(0, "Test", "DLL Message", MB_OK | MB_ICONINFORMATION);

    /*
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(0, "Test", "DLL Message", MB_OK | MB_ICONINFORMATION);
            break;

        case DLL_PROCESS_DETACH:
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;
    }
    */
    return TRUE; // succesful
}

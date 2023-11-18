#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HMODULE kernel_lib = GetModuleHandle("Kernel32.dll");
    VOID *load_lib_f = GetProcAddress(kernel_lib, "LoadLibraryA");
    LPVOID proc_buffer;
    char dll_name[] = "D:\\bloat_load.dll";
    unsigned int dll_size = sizeof(dll_name) + 1;

    //LoadLibrary("D:\\bloat_load.dll");
    //return 0;

    int prod_id = 7768;
    HANDLE dest_proc = OpenProcess(PROCESS_ALL_ACCESS,
                                   FALSE,
                                   prod_id);

    proc_buffer = VirtualAllocEx(dest_proc,
                                NULL,
                                dll_name,
                                (MEM_RESERVE | MEM_COMMIT),
                                PAGE_EXECUTE_READWRITE);

    WriteProcessMemory(dest_proc, proc_buffer, dll_name, dll_size, NULL);
    HANDLE rt = CreateRemoteThread(dest_proc, NULL, 0, (LPTHREAD_START_ROUTINE)load_lib_f, proc_buffer, 0, NULL);



    CloseHandle(dest_proc);
    return 0;
}



#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <wininet.h>


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{


    HINTERNET hInternet, hConnect;
    hInternet = InternetOpen("Git checker",
                             INTERNET_OPEN_TYPE_DIRECT,
                             NULL,
                             NULL,
                             0);
    if (hInternet == NULL) {
        return 1;
    }


    hConnect = InternetOpenUrl(hInternet,
                               "https://raw.githubusercontent.com/killercd/pyssh/main/README.md",
                               NULL,
                               0,
                               INTERNET_FLAG_RELOAD,
                               0);
    if (hConnect == NULL) {
        InternetCloseHandle(hInternet);
        return 1;
    }

    HANDLE hFile = CreateFile("rdm.txt",
                              GENERIC_WRITE,
                              0,
                              NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 1;
    }

    char buffer[1024];
    DWORD bytesRead;
    while (InternetReadFile(hConnect,
                            buffer,
                            sizeof(buffer),
                            &bytesRead) && bytesRead > 0) {
        DWORD bytesWritten;
        WriteFile(hFile,
                  buffer,
                  bytesRead,
                  &bytesWritten,
                  NULL);
    }

    CloseHandle(hFile);


    return 0;
}



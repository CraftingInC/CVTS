
// Console Virtual Terminal Sequences
/* gcc -Wall -m64 -Os -static main.c -o test -s */

#define UNICODE
#include <errno.h>
#ifdef _WIN64
#include <windows.h>
#include <fcntl.h>
#include <stdio.h>
#else
#include <wchar.h>
#include <locale.h>
#endif


int initConsoleColors();

int main()
{
    if(initConsoleColors())
    {
        wprintf(L"\x1b[102m\x1b[94mHello Made it\x1b[0m\n");
        wprintf(L"\x1b[105m\u2591\u2592\x1b[40m\u2593\u2593\x1b[0m\u2592\u2591\n\x1b[102m\u03A6\u03A6\u03A6\u03A6\x1b[0m");
    }

    return errno;
}

int initConsoleColors()
{
#ifdef _WIN64
    _setmode(_fileno(stdout), _O_U8TEXT);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if(GetConsoleMode(hOut, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        } else {
            wprintf(L"ERROR : Unable to get console Mode.\n");
            return -1;
        }
    } else {
        wprintf(L"ERROR : Unable to get console Handle.\n");
        return -1;
    }
#else
    setlocale(LC_ALL, "en_US.utf8");   // This sets up unicode for linux in XTERM
#endif
    return 1;
}

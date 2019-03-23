//aplikacja serwera

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

int main()
{
	//WinSock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup error", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	SOCKET socketS;

	struct sockaddr_in local;
	struct sockaddr_in from;
	int fromlen = sizeof(from);
	local.sin_family = AF_INET;
	local.sin_port = htons(1234);
	local.sin_addr.s_addr = INADDR_ANY;

	socketS = socket(AF_INET, SOCK_DGRAM, 0);
	bind(socketS, (sockaddr*)&local, sizeof(local));
	int L1, L3;
	ZeroMemory((void*)&L1, sizeof(L1));
	ZeroMemory((void*)&L3, sizeof(L3));
	while (L3 == 0)
	{
		std::cout << "Wprowadz liczbe L1: ";
		std::cin >> L1;
		sendto(socketS, (char*)&L1, sizeof(L1), 0, (sockaddr*)&from, fromlen);
		std::cout << "Wyslano liczbe L1" << std::endl;
		std::cout << "Czekam..." << std::endl;
		recvfrom(socketS, (char*)&L3, sizeof(L3), 0, (sockaddr*)&from, &fromlen);
		std::cout << "Odebrano liczbe L3" << std::endl;
		std::cout << "L3 = " << L3 << std::endl;
		Sleep(500);
	}

	closesocket(socketS);
	system("pause");
	return 0;
}
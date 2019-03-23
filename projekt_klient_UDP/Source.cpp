//aplikacja klienta

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main()
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "Winsock startup error", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKET socketC;

	struct sockaddr_in serverInfo;
	int len = sizeof(serverInfo);
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(1234);
	serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");

	socketC = socket(AF_INET, SOCK_DGRAM, 0);
	srand(time(NULL));
	int L1, L2, L3;
	ZeroMemory((void*)&L1, sizeof(L1));
	ZeroMemory((void*)&L3, sizeof(L3));
	while (L1 == 0)
	{
		recvfrom(socketC, (char*)&L1, sizeof(L1), 0, (sockaddr*)&serverInfo, &len);
		std::cout << "Odebrano liczbe L1" << std::endl;
		std::cout << "L1 = " << L1 << std::endl;
		L2 = rand() % 10 + 1;
		std::cout << "L2 = " << L2 << std::endl;
		L3 = L1 * L2;
		std::cout << "L3 = L1 * L2 = " << L3 << std::endl;
		sendto(socketC, (char*)&L3, sizeof(L3), 0, (sockaddr*)&serverInfo, len);
		std::cout << "Wyslano liczbe L3" << std::endl;
	}
	// cleanup
	closesocket(socketC);
	WSACleanup();
	return 0;
}


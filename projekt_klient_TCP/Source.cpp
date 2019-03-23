//aplikacja klienta w TCP

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main()
{
	//Wystartowanie Winsocka
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //Jesli WSAStartup zwraca cos innego niz 0, to znaczy, ze wystapil blad przy starcie Winsocka
	{
		MessageBoxA(NULL, "Winsock startup error", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr; //Adres przypisany do socketu Connection
	int sizeofaddr = sizeof(addr); //Rozmiar adresu
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Addres = localhost (tylko przesylanie lokalne na tym PC)
	addr.sin_port = htons(1111); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL); //Ustawianie socketu Connection
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //Wykonywane jesli nie nawiazemy polaczenia
	{
		MessageBoxA(NULL, "Blad polaczenia", "Error", MB_OK | MB_ICONERROR);
		return 0; //Blad polaczenia
	}
	std::cout << "Polaczono!" << std::endl;

	srand(time(NULL));

	int L1, L2, L3;
	recv(Connection, (char*)&L1, sizeof(L1), NULL); //Otrzymanie L1
	std::cout << "Odebrano liczbe L1 = " << L1 << std::endl;
	L2 = rand() % 10 + 1;
	std::cout << "Wylosowano liczbe L2." << std::endl << "L2 = " << L2 << std::endl;
	L3 = L1 * L2;
	std::cout << "L3 = L1 * L2 = " << L3 << std::endl;
	send(Connection, (char*)&L3, sizeof(L3), NULL); //Wysylanie L3
	std::cout << "Wyslano L3" << std::endl;
	//cleanup
	closesocket(Connection);
	WSACleanup();
	return 0;
}


//aplikacja serwera

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>

int main()
{
	//Wystartowanie Winsocka
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //Jesli WSAStartup zwraca cos innego niz 0, to znaczy, ze wystapil blad przy starcie Winsocka
	{
		MessageBoxA(NULL, "WinSock startup error", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	SOCKADDR_IN addr; //Adres przypisany do socketu nasluchujacego
	int addrlen = sizeof(addr); //Dlugosc adresu
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Nadawanie lokalnie na tym PC
	addr.sin_port = htons(1111); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //Tworzenie socketu do nasluchiwania na nowe polaczenie
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Przypisanie adresu do socketa
	listen(sListen, SOMAXCONN); //Stawianie socketu nasluchujacego w stanie, w ktorym nasluchuje na polaczenie przychodzace

	int L1, L3;
	SOCKET newConnection; //Socket do podtrzymywania polaczenia z klientem
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Zaakceptowanie nowego polaczenia
	if (newConnection == 0) //Wyswietlanie bledu w przypadku braku polaczenia
	{
		std::cout << "Blad zatwierdzenia polaczenia z klientem." << std::endl;
	}
	else //Jesli klient sie polaczy
	{
		std::cout << "Klient polaczony!" << std::endl;
		std::cout << "Podaj liczbe L1: ";
		std::cin >> L1;
		send(newConnection, (char*)&L1, sizeof(L1), NULL); //Wysylanie L1
		std::cout << "Wyslano liczbe L1" << std::endl;
		recv(newConnection, (char*)&L3, sizeof(L3), NULL); //Otrzymanie L3
		std::cout << "Odebrano liczbe L3" << std::endl;
		std::cout << "L3 = " << L3 << std::endl;
	}
	//cleanup
	closesocket(newConnection);
	WSACleanup();
	return 0;
}
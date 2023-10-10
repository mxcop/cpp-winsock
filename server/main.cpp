#include <iostream>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

void on_client_connect(SOCKET client);

int main()
{
	WSADATA wsa_data;
	SOCKADDR_IN server_addr, client_addr;

	WSAStartup(MAKEWORD(2, 2), &wsa_data);
	const auto server = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5555);

	::bind(server, reinterpret_cast<SOCKADDR *>(&server_addr), sizeof(server_addr));
	listen(server, 0);

	std::cout << "Listening for incoming connections..." << std::endl;

	int client_addr_size = sizeof(client_addr);

	for (;;)
	{
		SOCKET client;

		if ((client = accept(server, reinterpret_cast<SOCKADDR *>(&client_addr), &client_addr_size)) != INVALID_SOCKET)
		{
			on_client_connect(client);
		}

		const auto last_error = WSAGetLastError();
		
		if(last_error > 0)
		{
			std::cout << "Error: " << last_error << std::endl;
		}
	}
}

void on_client_connect(SOCKET client)
{
	char buffer[1024];

	std::cout << "Client connected!" << std::endl;
	recv(client, buffer, sizeof(buffer), 0);

	std::cout << "Client says: " << buffer << std::endl;
	memset(buffer, 0, sizeof(buffer));

	closesocket(client);
	std::cout << "Client disconnected." << std::endl;
}

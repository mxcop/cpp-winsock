#include <iostream>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

extern "C" {
   WINSOCK_API_LINKAGE  INT WSAAPI inet_pton( INT Family, PCSTR pszAddrString, PVOID pAddrBuf);
   WINSOCK_API_LINKAGE  PCSTR WSAAPI inet_ntop(INT  Family, PVOID pAddr, PSTR pStringBuf, size_t StringBufSize);
}

int main(int argc, char *argv[])
{
	const char* serve_addr = "127.0.0.1";
	if(argc > 1)
	{
		serve_addr = argv[1];
	}

	const char* serve_port = "5555";
	if(argc > 2)
	{
		serve_port = argv[2];
	}

	const char* buffer = "hello.";
	if(argc > 3)
	{
		buffer = argv[3];
	}

	WSADATA wsa_data;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 0), &wsa_data);
	const auto server = socket(AF_INET, SOCK_STREAM, 0);

	inet_pton(AF_INET, serve_addr, &addr.sin_addr.s_addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(serve_port));

	int err = connect(server, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));

	if (err == -1) {
		std::cout << "Failed to connect to server!" << std::endl;

		closesocket(server);
		WSACleanup();
		return -1;
	}

	std::cout << "Connected to server!" << std::endl;
	send(server, buffer, strlen(buffer) + 1, 0);
	std::cout << "Message sent!" << std::endl;

	closesocket(server);
	WSACleanup();
	std::cout << "Socket closed." << std::endl << std::endl;
}

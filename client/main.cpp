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
	std::string buffer = "hello.";

	if(argc > 1)
	{
		buffer = argv[1];
	}

	WSADATA wsa_data;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 0), &wsa_data);
	const auto server = socket(AF_INET, SOCK_STREAM, 0);

	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);

	connect(server, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));
	std::cout << "Connected to server!" << std::endl;

	send(server, buffer.c_str(), buffer.length(), 0);
	std::cout << "Message sent!" << std::endl;

	closesocket(server);
	WSACleanup();
	std::cout << "Socket closed." << std::endl << std::endl;
}

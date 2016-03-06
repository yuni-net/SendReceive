#include <WinSock2.h>
#pragma comment(lib, "ws2_32")
#include <iostream>
#include <string>
#pragma warning(disable:4996)

static const unsigned short port = 9696;

std::string get_my_addr()
{
	const int buffersize = 256;
	char buffer[buffersize];
	gethostname(buffer, buffersize);

	HOSTENT * host = gethostbyname(buffer);

	const char * address = host->h_addr_list[0];

	if (address == nullptr)
	{
		std::string("自身のアドレスの取得に失敗しました");
	}

	const in_addr * inaddr = reinterpret_cast<const in_addr *>(address);
	const char * name = inet_ntoa(*inaddr);
	return std::string(name);

}

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in recv_addr;
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(port);
	recv_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	int result = bind(sock, reinterpret_cast<sockaddr *>(&recv_addr), sizeof(recv_addr));

	std::cout << "myaddr:" << get_my_addr() << std::endl;
	std::cout << "port: " << port << std::endl;

	if (result == -1)
	{
		std::cout << "failed to bind port" << std::endl;
		return -1;
	}

	char data[256] = "";
	sockaddr_in cliant_addr;
	int addr_len = sizeof(sockaddr_in);

	while (true)
	{

		int rec_size = recvfrom(sock, data, 256, 0, reinterpret_cast<sockaddr *>(&cliant_addr), &addr_len);

		if (rec_size == -1)
		{
			std::cout << "failed to recvfrom" << std::endl;
			int e = WSAGetLastError();
			std::cout << "error_code:" << e << std::endl;
			return -1;
		}

		if (rec_size >= 256)
		{
			rec_size = 255;
		}
		data[rec_size] = '\0';

		std::cout << "received:" << data << std::endl;
	}

	closesocket(sock);

	WSACleanup();

	return 0;
}
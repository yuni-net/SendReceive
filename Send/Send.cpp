#include <WinSock2.h>
#pragma comment(lib, "ws2_32")
#include <iostream>

#pragma warning(disable:4996)

static const unsigned short port = 9696;

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in sendaddr;
	memset(&sendaddr, 0, sizeof(sendaddr));

	char data[256] = "";

	sendaddr.sin_family = AF_INET;

	while (true)
	{

		std::cout << "宛先のIPアドレスを入力してください(例　172.26.17.38)" << std::endl;
		scanf("%s", data);
		sendaddr.sin_addr.s_addr = inet_addr(data);
		//	std::cout << "sendaddr.sin_addr.s_addr:" << std::endl;

		std::cout << "宛先のポート番号を入力してください" << std::endl;
		int port_num;
		scanf("%d", &port_num);
		sendaddr.sin_port = htons(port_num);

		std::cout << "送信したいテキスト(～255文字)を入力すると送信されます" << std::endl;
		scanf("%s", data);
		int send_res = sendto(sock, data, strlen(data) + 1, 0, (sockaddr *) &sendaddr, sizeof(sendaddr));
		if (send_res == -1)
		{
			std::cout << "failed to send" << std::endl;
		}
		else
		{
			std::cout << "送信しました。" << std::endl;
		}
	}


	closesocket(sock);


	WSACleanup();

	return 0;
}
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

		std::cout << "�����IP�A�h���X����͂��Ă�������(��@172.26.17.38)" << std::endl;
		scanf("%s", data);
		sendaddr.sin_addr.s_addr = inet_addr(data);
		//	std::cout << "sendaddr.sin_addr.s_addr:" << std::endl;

		std::cout << "����̃|�[�g�ԍ�����͂��Ă�������" << std::endl;
		int port_num;
		scanf("%d", &port_num);
		sendaddr.sin_port = htons(port_num);

		std::cout << "���M�������e�L�X�g(�`255����)����͂���Ƒ��M����܂�" << std::endl;
		scanf("%s", data);
		int send_res = sendto(sock, data, strlen(data) + 1, 0, (sockaddr *) &sendaddr, sizeof(sendaddr));
		if (send_res == -1)
		{
			std::cout << "failed to send" << std::endl;
		}
		else
		{
			std::cout << "���M���܂����B" << std::endl;
		}
	}


	closesocket(sock);


	WSACleanup();

	return 0;
}
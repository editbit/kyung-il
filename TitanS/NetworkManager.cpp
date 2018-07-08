#include "stdafx.h"
#include "NetworkManager.h"


NetworkManager::NetworkManager()
{
	_ip[0] = _port[0] = 0;
}


NetworkManager::~NetworkManager()
{
}

HRESULT NetworkManager::init()
{
	//SOCKADDR_IN servAdr, clntAdr;

	/*if (_ip[0] == 0 || _port[0] == 0)
	{
		strcpy_s(_ip, "192.168.1.2");
		strcpy_s(_port, "8080");
	}*/

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
	}


	servSock = socket(PF_INET, SOCK_DGRAM, 0);
	if (servSock == INVALID_SOCKET)
		exit(0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);	// == servAdr.sin_addr.S_un.S_addr = ...
	servAdr.sin_port = htons(atoi(_port));

	if (bind(servSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
	}

	string cli[2];

	if (strcmp(_port, "8080") == 0)
	{
		cli[0] = "192.168.0.16";
		cli[1] = "8081";
	}
	else
	{
		cli[0] = "192.168.0.16";
		cli[1] = "8080";
	}


	memset(&clntAdr, 0, sizeof(clntAdr));
	clntAdr.sin_family = AF_INET;
	//servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	inet_pton(AF_INET, cli[0].c_str(), (void *)&clntAdr.sin_addr.s_addr);
	clntAdr.sin_port = htons(atoi(cli[1].c_str()));
	clntAdrSz = sizeof(clntAdr);

	FD_ZERO(&reads);
	FD_SET(servSock, &reads);
	FD_SET(cSocket, &reads);
	
	return S_OK;
}



void NetworkManager::release()
{
	closesocket(servSock);
	closesocket(cSocket);
	WSACleanup();
}

void NetworkManager::send(string message)
{
	sendto(cSocket, message.c_str(), message.size(), 0, (SOCKADDR*)&clntAdr, sizeof(clntAdr));
}

string NetworkManager::receive()
{
	char message[BUF_SIZE];
	strLen = recvfrom(cSocket, message, BUF_SIZE, 0, (SOCKADDR*)&clntAdr, &clntAdrSz);

	return string(message);
}

int NetworkManager::checkInput()
{
	cpyReads = reads;
	timeout.tv_sec = 0;
	timeout.tv_usec = 10;

	if ((fdNum = select(0, &cpyReads, 0, 0, &timeout)) == SOCKET_ERROR)
		return 0;

	for (unsigned int i = 0; i < reads.fd_count; ++i)
	{
		if (FD_ISSET(reads.fd_array[i], &cpyReads))
		{
			if (reads.fd_array[i] == servSock)
			{
				string temp = receive();
				return atoi(temp.c_str());
			}
		}
	}

	return 0;
}



/*
void temp()
{
	clntAdrSz = sizeof(clntAdr);

	strLen = recvfrom(servSock, message, BUF_SIZE, 0, (SOCKADDR*)&clntAdr, &clntAdrSz);

	//sendto(servSock, message, strLen, 0, (SOCKADDR*)&clntAdr, sizeof(clntAdr));
	//strcpy_s(message, inet_ntop(AF_INET, (void*)&clntAdr, message, BUF_SIZE));

	strcpy_s(message, inet_ntop(AF_INET, (void*)&clntAdr.sin_addr, message, BUF_SIZE));
	strcat_s(message, ("/" + std::to_string(clntAdr.sin_port)).c_str());
	strLen = strlen(message);
}

*/
#pragma once
#include "SingletonBase.h"

using namespace std;

#define BUF_SIZE 30

class NetworkManager :
	public SingletonBase<NetworkManager>
{
	char _ip[20], _port[10];

	WSADATA wsaData;
	SOCKET servSock, cSocket;
	//char message[BUF_SIZE];
	char *token, *context = NULL;
	int strLen;
	int servAdrSz, clntAdrSz;
	SOCKADDR_IN servAdr, clntAdr;
	
	TIMEVAL timeout;
	fd_set reads, cpyReads;
	int fdNum;


public:
	HRESULT init();
	void release();

	void send(string message);
	string receive();

	int checkInput();


	void setIP(const char *ip, const char *port)
	{
		strcpy_s(_ip, ip);
		strcpy_s(_port, port);
	}

	NetworkManager();
	~NetworkManager();
};


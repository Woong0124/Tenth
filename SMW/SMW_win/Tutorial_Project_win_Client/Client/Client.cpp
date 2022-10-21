#define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma comment(lib,"ws2_32")

using namespace std;

#define PORT	3307
#define PACKED_SIZE 1024
#define SERVER_IP	"192.168.0.177"

struct FVector
{
	int x;
	int y;
	int z;
};

struct SpawnActorInfo
{
	int ID;
	std::string ActorType;
	FVector VectorInfo;
};

int main()
{

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << " Winsock Error: " << GetLastError() << endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}

	SOCKET ClinetSocket;
	ClinetSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClinetSocket == INVALID_SOCKET)
	{
		cout << " fail create Socket : " << GetLastError() << endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}

	SOCKADDR_IN ClinetSocketAddr;
	memset(&ClinetSocketAddr, 0, sizeof(SOCKADDR_IN));
	ClinetSocketAddr.sin_family = AF_INET;
	ClinetSocketAddr.sin_port = htons(3307);
	ClinetSocketAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	int Result = connect(ClinetSocket, (SOCKADDR*)&ClinetSocketAddr, sizeof(SOCKADDR_IN));

	if (Result == SOCKET_ERROR)
	{
		cout << " fail connect : " << GetLastError() << endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}

	char	MSG[] = "Clinet Send";
	send(ClinetSocket, MSG, sizeof(MSG), 0);

	int len;
	recv(ClinetSocket, (char*)&len, sizeof(int), 0);

	int as;
	SpawnActorInfo* a;
	char	Buffer[1024] = { 0, };
	as = recv(ClinetSocket, Buffer, len, 0);



	Buffer[as] = '\0';
	a = (SpawnActorInfo*)Buffer;

	cout << a->ID << endl;
	cout << a->ActorType << endl;
	cout << a->VectorInfo.x << endl;
	cout << a->VectorInfo.y << endl;
	cout << a->VectorInfo.z << endl;

	closesocket(ClinetSocket);

	WSACleanup();
	return 0;
}
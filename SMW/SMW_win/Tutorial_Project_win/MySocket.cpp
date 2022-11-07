#include "MySocket.h"
#include <iostream>



MySocket::MySocket()
{ 
	memset(this, 0, sizeof(MySocket));
	ServerSocket = INVALID_SOCKET;
	ClientSocket = INVALID_SOCKET;
}

MySocket::~MySocket()
{
	closesocket(ServerSocket);
	closesocket(ClientSocket);
	WSACleanup();
}

bool MySocket::InitSocket()
{
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "Winsock Error : " << GetLastError() << std::endl;
		return false;
	}
	return true;
}

bool MySocket::CreateSocket()
{
	
	// Socket ����
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		std::cout << "fail create Socket : " << GetLastError() << std::endl;
		return false;
	}

	return true;
}

bool MySocket::BindSocket(const char* _BindIP, int _BindPort)
{
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); //host to network long( 4byte)
	ServerSockAddr.sin_port = htons(_BindPort); //host to network short(2 byte). �� �Լ��� ��ġ�� ������ �򿣵�� ������� �����͸� ��ȯ�Ͽ� ����.

	// Socket ���ε�
	int BindServerSock = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));
	if (BindServerSock == SOCKET_ERROR)
	{
		std::cout << "fail bind : " << GetLastError() << std::endl;
		return false;
	}
	return true;
}

bool MySocket::ListenSocket()
{

	// Socket ���Ŵ��
	int BindServerSock = listen(ServerSocket, 0); // 2��° ���ڴ� �Ѳ����� ��û ������ �ִ� ���� ���� ��. 0�̳� SOMAXCONN. ������ ��ǻ�� ������ ���� �ǹ� ����.
	if (BindServerSock == SOCKET_ERROR) 
	{
		std::cout << "fail listen : " << GetLastError() << std::endl;
		return false;
	}

	return true;
}


bool MySocket::AcceptSocket()
{
	// Client socket ����
	// Ŭ���̾�Ʈ ���� ��û ��, ������ �ִ� ����
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	// Client ���� ����
	ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	if (ClientSocket == SOCKET_ERROR)
	{
		std::cout << "fail accept : " << GetLastError() << std::endl;
		return false;
	}

	return true;
}


bool MySocket::SendSocket()
{
	char Buffer[] = "Nunu";
	int SendBuffer = sizeof(Buffer);
	SendBuffer = send(ClientSocket, Buffer, SendBuffer, 0);
	if (SendBuffer == SOCKET_ERROR)
	{
		std::cout << "Send Error" << GetLastError() << std::endl;
		exit(-1);
		return false;
	}
	return true;
}

bool MySocket::ReciveSocket()
{
	char	Buffer[1024] = { 0, };
	int RecvBuffer = recv(ClientSocket, Buffer, 1024, 0);
	std::cout << "Recive Message : " << Buffer << std::endl;

	if (RecvBuffer <= 0)
	{
		std::cout << " fail send : " << GetLastError() << std::endl; 
		exit(-1);
		return false;
		
	}
	return true;
}




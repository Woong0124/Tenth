#pragma once
#include "Common.h"
#include <mysql.h>

class MySocket
{
public:
	MySocket();
	~MySocket();

	// ���ε� ����
	SOCKET ServerSocket;


	SOCKET CToSSocket;

	// ���� ����
	SOCKET ClientSocket;

	//���� �ʱ�ȭ ���� ���� 2.2 ����
	bool InitSocket();

	// ���� ����
	bool CreateSocket();

	// Bind Socket
	bool BindSocket(const char* _BindIP,int _BindPort);


	//���� ���·� ����
	bool ListenSocket();

	// ���� ����
	bool AcceptSocket();

	
	// Send
	bool SendSocket();

	// Recv
	bool ReciveSocket();

	



	template<typename T> //���ø��� ����� ����. cpp�� �ϸ� ��ã��. 
	void TSendStruct(T Struct);

	template<typename T>
	T TReciveStruct(T* Struct);
};

template<typename T>
inline void MySocket::TSendStruct(T Struct)
{
	int SendInt;
	int SendIntLength = sizeof(Struct);
	SendInt = send(CToSSocket, (char*)&SendIntLength, sizeof(int), 0);

	SendInt = send(CToSSocket, (char*)&Struct, sizeof(Struct), 0);

}
template<typename T>
inline T MySocket::TReciveStruct(T* Struct)
{
	char Buffer[1024] = { 0, };
	int len = 0;
	recv(CToSSocket, (char*)&len, sizeof(int), 0);
	
	recv(CToSSocket, sizeof(Struct), 1024, 0);
	Struct = (T*)Buffer;

	return *Struct;
}
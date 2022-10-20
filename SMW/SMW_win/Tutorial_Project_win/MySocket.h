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

	//Ŭ���̾�Ʈ���� ������ ����
	bool ConnectSocket(const char* _ServerIP, int _ConnectPort);

	// Send
	bool SendSocket();

	// Recv
	bool RecvSocket();

	//����ü ����
	void SendStruct(SpawnActorInfo Actorinfo);

	// ����ü �ޱ�
	SpawnActorInfo ReciveStruct(SpawnActorInfo* ActorInfo);
};
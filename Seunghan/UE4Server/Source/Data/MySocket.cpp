// Fill out your copyright notice in the Description page of Project Settings.


#include "Socket.h"
#include "MySocket.h"
#include "Sockets.h"
#include "Networking.h"
#include "SocketSubsystem.h"
#include "MyActor.h"
#include "DataGameModeBase.h"

#define PORT	4000
#define PACKED_SIZE 1024
#define SERVER_IP	"192.168.0.178"

#pragma region Main Thread Code
MySocket::MySocket()
{
	//FSocket* TestSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(SOCK_STREAM, TEXT("default"), false);
	//FString address = TEXT("127.0.0.1");
	//int32 port = PORT;
	//FIPv4Address ip;
	//FIPv4Address::Parse(address, ip);
	//TSharedRef<FInternetAddr> addr =ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	//addr->SetIp(ip.GetValue());
	//addr->SetPort(port);
	//bool connected = Socket->Connect(*addr);
	Thread = FRunnableThread::Create(this, TEXT("SocketServer"));
}

MySocket::MySocket(ADataGameModeBase* a)
{
	MyGameModeBase = a;
	Thread = FRunnableThread::Create(this, TEXT("SocketServer"));
}

MySocket::~MySocket()
{
	if (Thread)
	{
		// Kill() is a blocking call, it waits for the thread to finish.
		// Hopefully that doesn't take too long
		Thread->Kill();
		delete Thread;
	}

}
#pragma endregion

bool MySocket::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("My custom thread has been initialized"));

	// Return false if you want to abort the thread
	return true;
}

uint32 MySocket::Run()
{
	FSocket* Socket;

	// ���� ����
	// ���� Ÿ�԰� ������ ���ڷ� �ִ´�.TEXT("Stream")�� �ָ� TCP ���������� ����ϰڴٴ� ���̴�. (UDP�� TEXT("DGram")�� ���ڷ� �ָ� �ȴ�.)
	//�� ��° ���� TEXT("Client Socket") �� ����� �̸��̴�.�˱� ���� �̸����� ����������.
	// �� ��° ���ڴ� UDP�� true TCP�� flase�̴�.

	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));

	// IP ����
	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	int32 port = PORT;	// ��Ʈ�� 4000��

	// ��Ʈ�� ������ ��� Ŭ����
	// FInternetAddr�� ��Ʈ��ũ ������ �����ϰ�, ��Ŭ�������� ��Ʈ��ũ ����Ʈ�� ������ �ȴ�.

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);



	// ����õ�, ����� �޾ƿ�
	bool isConnetcted = Socket->Connect(*addr);
	if (isConnetcted)
	{
		UE_LOG(LogTemp, Log, TEXT("Connect Success"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Connect fail"));
	}

	Package ReceivePack;

	while (bRunThread)
	{

		FPlatformProcess::Sleep(0.3f);

		uint8	Buffer[1024] = { 0 };
		int32	temp = 0;
		Socket->Recv(Buffer, 1024, temp);

		Package* a = (Package*)Buffer;
		ReceivePack = *a;

		UE_LOG(LogTemp, Log, TEXT("Header : %d X : %d Z : %d"), ReceivePack.Header, ReceivePack.X, ReceivePack.Z);

		MyGameModeBase->ReceivePack = ReceivePack;
	}


	return 0;
}

void MySocket::Stop()
{
	bRunThread = false;
}

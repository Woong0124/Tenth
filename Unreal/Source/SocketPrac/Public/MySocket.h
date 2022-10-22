// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma comment(lib, "ws2_32.lib")

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"
#include <WinSock2.h>
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#include "CoreMinimal.h"

enum ActiveInfo
{
	SpawnActor = 1,
	MoveActor = 2
};

struct DataStruct
{
	int Key;
	ActiveInfo AInfo;
	char ActorType[50];
	float LocX;
	float LocY;
	float LocZ;

	DataStruct()
	{
		memset(this, 0, sizeof(DataStruct));
	};
};



class ASocketPracGameModeBase;

/**
 * 
 */
class SOCKETPRAC_API MySocket : public FRunnable
{
public:
	MySocket();
	~MySocket();


	////////////////////////////////////////////////
	////////////////////////////////////////////////
	MySocket(ASocketPracGameModeBase* MyGameMode);

	// Thread
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;

	bool CheckThread = false;
	ASocketPracGameModeBase* MyGM;
	////////////////////////////////////////////////
	////////////////////////////////////////////////


	SOCKET ClientSocket;
	DataStruct* MyDataStruct;

	// ���� �ʱ�ȭ
	bool InitSocket();

	// ���� ����
	bool ConnectSocket();

	// ���� ���
	bool CommunicateSocket();

	// recv
	DataStruct RecvStructSocket(DataStruct* DStruct);

	// send
	void SendStructSocket(DataStruct* DStruct);

};

#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#include <mysql.h>
#include <iostream>
#include "MyDB.h"
#include "MySocket.h"



int main()
{
	// DB ���� ����
	MyDB* MyDataBase = new(MyDB);

	// DB ���� üũ
	bool DBCheck;

	// DB ����
	DBCheck = MyDataBase->ConnectDataBase();
	if (DBCheck == false)
	{
		return 1;
	}





	// ���� ���� ����
	MySocket* MySock = new(MySocket);

	// ���� ���� üũ
	bool SocketCheck;
	
	// Socket
	SocketCheck = MySock->CreateSocket();
	if (SocketCheck == false)
	{
		exit(-1);
	}
	
	// Bind, Listen
	SocketCheck = MySock->BindListenSocket();
	if (SocketCheck == false)
	{
		exit(-1);
	}

	// Accept
	SocketCheck = MySock->AcceptSocket();
	if (SocketCheck == false)
	{
		exit(-1);
	}





	DataStruct* DStruct = new DataStruct; 

	MyDataBase->QueryTransmission("SELECT * FROM DATATABLE");

	while ((MyDataBase->SqlRow = mysql_fetch_row(MyDataBase->SqlResult)) != NULL)
	{
		DStruct->AInfo = SpawnActor;
		MyDataBase->QueryStructInsert(DStruct);
		MySock->SendStructSocket(DStruct);
	}



	// �׽�Ʈ ��
	while (true)
	{
		char Buffer[1024] = "1";
		send(MySock->ClientSocket, (char*)Buffer, sizeof(Buffer), 0);
	}



	delete DStruct;

	// ���� ����
	delete MySock;

	// DB ����
	delete MyDataBase;

	return 0;
}
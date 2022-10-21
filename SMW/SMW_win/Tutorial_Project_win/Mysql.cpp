#include "MySQL.h"
#pragma comment (lib, "libmysql.lib")
#include <iostream>
#include <mysql.h>



using namespace std;

MySQL::MySQL()
{
	memset(this, 0, sizeof(MySQL)); //(��ü, ��, ������(������ �ʱ�ȭ �� ������)
	mysql_init(&conn);				// MySQL ���� �ʱ�ȭ
}

MySQL::~MySQL()
{

	mysql_close(ConnPtr);			// MySQL ���� ����
}

bool MySQL::ConncetMySQL()
{	// ������ ���̽��� ����
	ConnPtr = mysql_real_connect(&conn, "localhost", "root", "smwbs1570", "tutorial", 3306, NULL, 0);

	// ���� ��� Ȯ�� Null�� ��� ����
	if (ConnPtr == NULL)
	{
		std::cout << stderr << "Mysql Connection Error : 1 " << mysql_error(&conn);
		return false;
	}

	return true;
}

bool MySQL::RecQueryResult()
{
	// ���� ��û (���̺� �˻�)
	const char* Query = "SELECT * FROM tosocketdb";
	Stat = mysql_query(ConnPtr, Query);
	if (Stat != 0)
	{
		std::cout << stderr << "Mysql Connection Error : 2 " << mysql_error(&conn);
		return false;
	}

	// ��û ��� ����
	mysqlResult = mysql_store_result(ConnPtr);

	return true;
}

void MySQL::OutResult()
{

	// ��û ��� ���
	while ((Row = mysql_fetch_row(mysqlResult)) != NULL)
	{
		for (int i = 0; i < mysql_num_fields(mysqlResult); ++i)
		{
			cout << Row[i] << "  ";
		}
		cout << endl;
	}
}
void MySQL::Insert(SpawnActorInfo& ActorInfo)
{
	
	Row = mysql_fetch_row(mysqlResult);

	for (unsigned int i = 0; i < mysql_num_fields(mysqlResult); ++i)
	{
		switch (i)
		{
		case 0:
			ActorInfo.ID = stoi(Row[i]);
			break;
		case 1:
			strcpy_s(ActorInfo.ActorType, Row[i]);
			break;
		case 2:
			ActorInfo.x = stoi(Row[i]);
			break;
		case 3:
			ActorInfo.y = stoi(Row[i]);
			break;
		case 4:
			ActorInfo.z = stoi(Row[i]);
			break;

		}


	}
}

void MySQL::DataTableInsert(const char* value)
{
	char InsertQuery[100] = "insert into tosocketdb ";
	strcat_s(InsertQuery, value);
	cout << InsertQuery << endl;
	mysql_query(ConnPtr, InsertQuery);
}

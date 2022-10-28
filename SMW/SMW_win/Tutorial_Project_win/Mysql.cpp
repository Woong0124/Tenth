#include "MySQL.h"
#pragma comment (lib, "libmysql.lib")
#include <iostream>
#include <mysql.h>
#include "Common.h"


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
	Row = mysql_fetch_row(mysqlResult);
	return true;
}

void MySQL::OutResult()
{

	// ��û ��� ���
	while ((Row = mysql_fetch_row(mysqlResult)) != NULL)
	{
		for (unsigned int i = 0; i < mysql_num_fields(mysqlResult); ++i)
		{
			cout << Row[i] << "  ";
		}
		cout << endl;
	}
	Row = mysql_fetch_row(mysqlResult);
}

void MySQL::Insert(Package& Package)
{
	
	char Temp[10] = {};
	if (Row !=nullptr)
	{ 
	
		for (unsigned int i = 0; i < mysql_num_fields(mysqlResult); ++i)
	
		{
		Package.PackSize = sizeof(Package);
		switch (i)
		{
		case 0:
			Package.Key = stoi(Row[i]);
			break;
		case 1:
			strcpy_s(Temp, Row[i]);
			cout << "Temp : " << Temp << endl;
			if (strcmp(Temp, "Spawn") == 0)
			{
				cout << "Spawn Success" << endl;
				Package.Header = PackageHeader::Spawn;
			}
			else if (strcmp(Temp, "Move") == 0)
			{
				cout << "Move Success" << endl;
				Package.Header = PackageHeader::Move;
			}
			else
			{
				Package.Header = PackageHeader::None;
			}
			break;
		case 2:
			Package.X = stoi(Row[i]);
			break;
		case 3:
			Package.Y = stoi(Row[i]);
			break;
		case 4:
			Package.Z = stoi(Row[i]);
			break;

		}

		}

	}
	Row = mysql_fetch_row(mysqlResult);
}
void MySQL::DataTableInsert(const char* value)
{
	char InsertQuery[100] = "insert into tosocketdb ";
	strcat_s(InsertQuery, value);
	cout << InsertQuery << endl;
	mysql_query(ConnPtr, InsertQuery);
}

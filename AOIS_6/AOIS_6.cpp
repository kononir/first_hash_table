// AOIS_6.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "HeshTable.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <cstdio>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������
	int answer, size;
	cout<<"������� ����� �������: ";
	cin>>size;
	HeshTable hesh_table(size);
	do{
		cout<<endl<<"1-������ ����� �������,"<<endl<<"2-����� ������� � ������� ����������,"<<endl<<"3-������� �������,"<<endl<<"4-������� ��� �������,"<<endl<<"5-�������� �������,"<<endl<<"0-�����"<<endl<<endl;
		cin>>answer;
		//cin.clear();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (answer){
			case 1:
				{
					string key, info;
					int returning_number;
					cout<<endl<<"������� ����: ";
					getline(cin, key, '\n');
					getline(cin, key, '\n');
					cout<<"������� ���������� ��� ��������: ";
					//cin>>info;
					getline(cin, info, '\n');
					//cout<<info<<endl;
					returning_number=hesh_table.push_string(key, info);
					if(returning_number==-1)
						cout<<endl<<"������� �����������!"<<endl;
					if(returning_number==0)
						cout<<endl<<"���� ��� ������������ � �������!"<<endl;
					if(returning_number==1)
						cout<<endl<<"�������!"<<endl;
					break;
				}
			case 2:
				{
					string key;
					cout<<endl<<"������� ����: ";
					getline(cin, key, '\n');
					getline(cin, key, '\n');
					cout<<endl<<hesh_table.pull_string(key)<<endl;
					break;
				}
			case 3:
				{
					string key;
					int returning_number;
					cout<<endl<<"������� ����: ";
					getline(cin, key, '\n');
					getline(cin, key, '\n');
					returning_number=hesh_table.delete_string(key);
					if(returning_number==0)
						cout<<endl<<"���� �� ������!";
					if(returning_number==1)
						cout<<endl<<"�������!";
					break;
				}
			case 4:
				{
					hesh_table.show_table();
					break;
				}
			case 5:
				{
					system("cls");
					break;
				}
			case 0:
				{
					exit(1);
				}
		}
	}
	while(answer==answer);
}


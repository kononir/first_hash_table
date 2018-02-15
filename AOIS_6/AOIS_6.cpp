// AOIS_6.cpp: определяет точку входа для консольного приложения.
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
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	int answer, size;
	cout<<"Введите длину таблицы: ";
	cin>>size;
	HeshTable hesh_table(size);
	do{
		cout<<endl<<"1-ввести новую строчку,"<<endl<<"2-найти строчку и вывести содержимое,"<<endl<<"3-удалить строчку,"<<endl<<"4-вывести всю таблицу,"<<endl<<"5-очистить консоль,"<<endl<<"0-выход"<<endl<<endl;
		cin>>answer;
		//cin.clear();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (answer){
			case 1:
				{
					string key, info;
					int returning_number;
					cout<<endl<<"Введите ключ: ";
					getline(cin, key, '\n');
					getline(cin, key, '\n');
					cout<<"Введите информацию для хранения: ";
					//cin>>info;
					getline(cin, info, '\n');
					//cout<<info<<endl;
					returning_number=hesh_table.push_string(key, info);
					if(returning_number==-1)
						cout<<endl<<"ТАБЛИЦА ПЕРЕПОЛНЕНА!"<<endl;
					if(returning_number==0)
						cout<<endl<<"Ключ уже присутствует в таблице!"<<endl;
					if(returning_number==1)
						cout<<endl<<"Успешно!"<<endl;
					break;
				}
			case 2:
				{
					string key;
					cout<<endl<<"Введите ключ: ";
					getline(cin, key, '\n');
					getline(cin, key, '\n');
					cout<<endl<<hesh_table.pull_string(key)<<endl;
					break;
				}
			case 3:
				{
					string key;
					int returning_number;
					cout<<endl<<"Введите ключ: ";
					getline(cin, key, '\n');
					getline(cin, key, '\n');
					returning_number=hesh_table.delete_string(key);
					if(returning_number==0)
						cout<<endl<<"КЛЮЧ НЕ НАЙДЕН!";
					if(returning_number==1)
						cout<<endl<<"Успешно!";
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


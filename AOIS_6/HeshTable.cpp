#include "StdAfx.h"
#include "HeshTable.h"
//#include "IdtfTable.h"
//#include <sstream>
#include <iostream>
using namespace std;

HeshTable::HeshTable(int s): size(s)
{
	//idtf_number = -1;
	hesh = new HeshString[size];
	//id_table = new IdtfTable(size); 
}


HeshTable::~HeshTable(void)
{
	delete hesh;
}


int HeshTable::push_string(string key, string info) //функция добавления новой строки
{
	int next_hesh_number, free_hesh_number;
	int sum=this->find_sum(key);
	int hesh_number=this->find_hesh(sum);
	if(rec_find_hesh_with_key(hesh_number, key)!=-1) //если ключ уже есть
		return 0; //возвращает 0
	next_hesh_number=rec_find_next_hesh(hesh_number);
	free_hesh_number=this->find_free_hesh(next_hesh_number);
	if(free_hesh_number==-1) //нет свободного места 
		return -1; //возвращает -1
	//idtf_number++;
	//stringstream ss;
	//ss<<idtf_number;
	//string str;
	//ss>>str;
	//id_table->setId_table(key, "ID"+str, sum, hesh_number); //добавление ключа, соответствующего ему id, суммы и хэша в доп. массив
	hesh[free_hesh_number].setID(key);
	hesh[free_hesh_number].setC(0);
	hesh[free_hesh_number].setU(1);
	hesh[free_hesh_number].setT(1);
	hesh[free_hesh_number].setL(0);
	hesh[free_hesh_number].setD(0);
	hesh[free_hesh_number].setPi(info);

	if(free_hesh_number==hesh_number){ //если строка до этого была пустая
		hesh[free_hesh_number].setP0(hesh_number);
		return 1;
	}
	if(hesh[next_hesh_number].getP0()==-1){ //если строка была последней в списке резервных строк
		hesh[free_hesh_number].setP0(-1);
		hesh[next_hesh_number].setT(0);
		hesh[next_hesh_number].setP0(free_hesh_number);
	}
	if(hesh[next_hesh_number].getP0()==next_hesh_number){ //если строка была занята, но колизии ещё не было
		hesh[free_hesh_number].setP0(-1);
		hesh[next_hesh_number].setC(1);
		hesh[next_hesh_number].setT(0);
		hesh[next_hesh_number].setP0(free_hesh_number);
	}
	return 1; //всё прошло успешно - возвращает 1
}


int HeshTable::find_sum(string info) //функция поиска суммы
{
	int asciisum = (info[0]+1)*33+info[1]+1;
	return -asciisum;
}


int HeshTable::find_hesh(int sum) //функция вычисления хэша
{
	return sum % size;
}


int HeshTable::find_free_hesh(int hesh_number) //функция поиска свободного места для записи (при колизии возвращает хэш следующей незанятой резервной строки, если строка не занята - возвращает хэш этой строки, если нет места - возврашает -1)
{
	for(int i=hesh_number; i<size; i++)
		if(!hesh[i].getU() || hesh[hesh_number].getU()==-111)
			return i;
	for(int i=0; i<hesh_number; i++)
		if(!hesh[i].getU() || hesh[hesh_number].getU()==-111)
			return i;
	return -1;
}


int HeshTable::rec_find_next_hesh(int hesh_number) //функция поиска последнего хэш элемента (при колизии возвращает хэш последней занятой резервной строчки, если не было - возвращает хэш саиой строки)
{
	if(!hesh[hesh_number].getU() || hesh[hesh_number].getP0()==-1 || hesh[hesh_number].getP0()==hesh_number || hesh[hesh_number].getP0()==-111) return hesh_number;
	return rec_find_next_hesh(hesh[hesh_number].getP0());
}


string HeshTable::pull_string(string key) //функция выборки по ключу
{
	//string idtf=this->find_key(key); //ищем ключ в таблице ключей
	//if(idtf=="0")
		//return "This key doesn't exist!";
	int sum=this->find_sum(key);
	int hesh_number=this->find_hesh(sum);
	int required_hesh_number=rec_find_hesh_with_key(hesh_number, key);
	if(required_hesh_number==-1)
		return "This key doesn't exist!";	
	return hesh[required_hesh_number].getPi();
}


int HeshTable::rec_find_hesh_with_key(int hesh_number, string key) //функция поиска строки таблицы по хэшу и ключу (возвращает найденный хэш или -1, если хэш с таким идентификатором не был найден)
{
	if(hesh[hesh_number].getID()==key) return hesh_number;
	if(hesh[hesh_number].getP0()==-1 || hesh[hesh_number].getP0()==hesh_number || hesh[hesh_number].getP0()==-111) return -1;
	return rec_find_hesh_with_key(hesh[hesh_number].getP0(), key);
}


/*string HeshTable::find_key(string key) //функция поиска идентификатора по ключу
{
	for(int i=0; i<size; i++)
		if(id_table->getKey(i)==key)
			return id_table->getID(i);
	return "0";
}*/


int HeshTable::delete_string(string key)
{
	int sum=this->find_sum(key);
	int hesh_number=this->find_hesh(sum);
	int next_hesh_number=rec_find_hesh_with_key(hesh_number, key); //ищем удаляемую строчку
	if(next_hesh_number==-1) //если не находим
		return 0; //возвращаем 0
	hesh[next_hesh_number].setD(1);
	if(hesh[next_hesh_number].getT()==1 && hesh[next_hesh_number].getP0()==next_hesh_number) //если удаляем одиночную строчку
		hesh[next_hesh_number].setU(0); //переводим флажок U в 0
	if(hesh[next_hesh_number].getT()==1 && hesh[next_hesh_number].getP0()==-1){ //если удаляем последнюю строчку в цепочке резервных строк
		int previous_hesh_number=rec_find_previous_hesh(hesh_number, next_hesh_number); //находим хэш предыдущей до удаляемой строки
		hesh[next_hesh_number].setU(0); //переводим флажок U для удаляемой строки в 0
		hesh[previous_hesh_number].setT(1); //переводим флажок T для предыдущей строки в 1
	}
	if((hesh[next_hesh_number].getT()==0 && hesh[next_hesh_number].getP0()!=next_hesh_number) || (hesh[next_hesh_number].getT()==0 && hesh[next_hesh_number].getC()==1)){ //если удаляем не последнюю строчку в цепочке резервных ячеек (любую, кроме последней)
		int next_next_hesh_number=hesh[next_hesh_number].getP0(); //находим следующую строчку
		hesh[next_hesh_number].setID(hesh[next_next_hesh_number].getID()); //переписываем её в удаляемую
		hesh[next_hesh_number].setT(hesh[next_next_hesh_number].getT()); //
		hesh[next_hesh_number].setL(hesh[next_next_hesh_number].getL()); //
		hesh[next_hesh_number].setD(hesh[next_next_hesh_number].getD()); //
		hesh[next_hesh_number].setP0(hesh[next_next_hesh_number].getP0()); // 
		hesh[next_hesh_number].setPi(hesh[next_next_hesh_number].getPi()); //
		hesh[next_next_hesh_number].setU(0); //переводим флажок U для следующей строки в 0
		//флажок колизии C не трогаем
	}
	return 1; //возвращаем 1, если удаления прошло успешно
}


int HeshTable::rec_find_previous_hesh(int hesh_number, int next_hesh_number)
{
	if(hesh[hesh_number].getP0()==next_hesh_number) return hesh_number;
	//if(hesh[hesh_number].getP0()==-1 || hesh[hesh_number].getP0()==hesh_number) return -1;
	return rec_find_previous_hesh(hesh[hesh_number].getP0(), next_hesh_number);
}


void HeshTable::show_table(void)
{
	setlocale(LC_ALL, "Russian");
	cout<<"                                   "<<"ВСЯ ТАБЛИЦА"<<endl;
	cout<<"--------------------------------------------------------------------------------"<<endl;
	for(int i=0; i<size; i++)
	{
		cout<<"                                   "<<hesh[i].getID()<<" ["<<i<<"]"<<endl;
		if(hesh[i].getC()==-111 || hesh[i].getU()==-111 || hesh[i].getT()==-111 || hesh[i].getL()==-111 || hesh[i].getD()==-111 || hesh[i].getP0()==-111)
		{
			cout<<"C = "<<endl;
			cout<<"U = "<<endl;
			cout<<"T = "<<endl;
			cout<<"L = "<<endl;
			cout<<"D = "<<endl;
			cout<<"P0 = "<<endl;
			cout<<"Pi = "<<hesh[i].getPi()<<endl;
			cout<<endl<<endl;
		}
		else
		{
			cout<<"C = "<<hesh[i].getC()<<endl;
			cout<<"U = "<<hesh[i].getU()<<endl;
			cout<<"T = "<<hesh[i].getT()<<endl;
			cout<<"L = "<<hesh[i].getL()<<endl;
			cout<<"D = "<<hesh[i].getD()<<endl;
			cout<<"P0 = "<<hesh[i].getP0()<<endl;
			cout<<"Pi = "<<hesh[i].getPi()<<endl;
			cout<<endl<<endl;
		}
	}
	cout<<"--------------------------------------------------------------------------------"<<endl;
}
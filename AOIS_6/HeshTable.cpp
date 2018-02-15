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


int HeshTable::push_string(string key, string info) //������� ���������� ����� ������
{
	int next_hesh_number, free_hesh_number;
	int sum=this->find_sum(key);
	int hesh_number=this->find_hesh(sum);
	if(rec_find_hesh_with_key(hesh_number, key)!=-1) //���� ���� ��� ����
		return 0; //���������� 0
	next_hesh_number=rec_find_next_hesh(hesh_number);
	free_hesh_number=this->find_free_hesh(next_hesh_number);
	if(free_hesh_number==-1) //��� ���������� ����� 
		return -1; //���������� -1
	//idtf_number++;
	//stringstream ss;
	//ss<<idtf_number;
	//string str;
	//ss>>str;
	//id_table->setId_table(key, "ID"+str, sum, hesh_number); //���������� �����, ���������������� ��� id, ����� � ���� � ���. ������
	hesh[free_hesh_number].setID(key);
	hesh[free_hesh_number].setC(0);
	hesh[free_hesh_number].setU(1);
	hesh[free_hesh_number].setT(1);
	hesh[free_hesh_number].setL(0);
	hesh[free_hesh_number].setD(0);
	hesh[free_hesh_number].setPi(info);

	if(free_hesh_number==hesh_number){ //���� ������ �� ����� ���� ������
		hesh[free_hesh_number].setP0(hesh_number);
		return 1;
	}
	if(hesh[next_hesh_number].getP0()==-1){ //���� ������ ���� ��������� � ������ ��������� �����
		hesh[free_hesh_number].setP0(-1);
		hesh[next_hesh_number].setT(0);
		hesh[next_hesh_number].setP0(free_hesh_number);
	}
	if(hesh[next_hesh_number].getP0()==next_hesh_number){ //���� ������ ���� ������, �� ������� ��� �� ����
		hesh[free_hesh_number].setP0(-1);
		hesh[next_hesh_number].setC(1);
		hesh[next_hesh_number].setT(0);
		hesh[next_hesh_number].setP0(free_hesh_number);
	}
	return 1; //�� ������ ������� - ���������� 1
}


int HeshTable::find_sum(string info) //������� ������ �����
{
	int asciisum = (info[0]+1)*33+info[1]+1;
	return -asciisum;
}


int HeshTable::find_hesh(int sum) //������� ���������� ����
{
	return sum % size;
}


int HeshTable::find_free_hesh(int hesh_number) //������� ������ ���������� ����� ��� ������ (��� ������� ���������� ��� ��������� ��������� ��������� ������, ���� ������ �� ������ - ���������� ��� ���� ������, ���� ��� ����� - ���������� -1)
{
	for(int i=hesh_number; i<size; i++)
		if(!hesh[i].getU() || hesh[hesh_number].getU()==-111)
			return i;
	for(int i=0; i<hesh_number; i++)
		if(!hesh[i].getU() || hesh[hesh_number].getU()==-111)
			return i;
	return -1;
}


int HeshTable::rec_find_next_hesh(int hesh_number) //������� ������ ���������� ��� �������� (��� ������� ���������� ��� ��������� ������� ��������� �������, ���� �� ���� - ���������� ��� ����� ������)
{
	if(!hesh[hesh_number].getU() || hesh[hesh_number].getP0()==-1 || hesh[hesh_number].getP0()==hesh_number || hesh[hesh_number].getP0()==-111) return hesh_number;
	return rec_find_next_hesh(hesh[hesh_number].getP0());
}


string HeshTable::pull_string(string key) //������� ������� �� �����
{
	//string idtf=this->find_key(key); //���� ���� � ������� ������
	//if(idtf=="0")
		//return "This key doesn't exist!";
	int sum=this->find_sum(key);
	int hesh_number=this->find_hesh(sum);
	int required_hesh_number=rec_find_hesh_with_key(hesh_number, key);
	if(required_hesh_number==-1)
		return "This key doesn't exist!";	
	return hesh[required_hesh_number].getPi();
}


int HeshTable::rec_find_hesh_with_key(int hesh_number, string key) //������� ������ ������ ������� �� ���� � ����� (���������� ��������� ��� ��� -1, ���� ��� � ����� ��������������� �� ��� ������)
{
	if(hesh[hesh_number].getID()==key) return hesh_number;
	if(hesh[hesh_number].getP0()==-1 || hesh[hesh_number].getP0()==hesh_number || hesh[hesh_number].getP0()==-111) return -1;
	return rec_find_hesh_with_key(hesh[hesh_number].getP0(), key);
}


/*string HeshTable::find_key(string key) //������� ������ �������������� �� �����
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
	int next_hesh_number=rec_find_hesh_with_key(hesh_number, key); //���� ��������� �������
	if(next_hesh_number==-1) //���� �� �������
		return 0; //���������� 0
	hesh[next_hesh_number].setD(1);
	if(hesh[next_hesh_number].getT()==1 && hesh[next_hesh_number].getP0()==next_hesh_number) //���� ������� ��������� �������
		hesh[next_hesh_number].setU(0); //��������� ������ U � 0
	if(hesh[next_hesh_number].getT()==1 && hesh[next_hesh_number].getP0()==-1){ //���� ������� ��������� ������� � ������� ��������� �����
		int previous_hesh_number=rec_find_previous_hesh(hesh_number, next_hesh_number); //������� ��� ���������� �� ��������� ������
		hesh[next_hesh_number].setU(0); //��������� ������ U ��� ��������� ������ � 0
		hesh[previous_hesh_number].setT(1); //��������� ������ T ��� ���������� ������ � 1
	}
	if((hesh[next_hesh_number].getT()==0 && hesh[next_hesh_number].getP0()!=next_hesh_number) || (hesh[next_hesh_number].getT()==0 && hesh[next_hesh_number].getC()==1)){ //���� ������� �� ��������� ������� � ������� ��������� ����� (�����, ����� ���������)
		int next_next_hesh_number=hesh[next_hesh_number].getP0(); //������� ��������� �������
		hesh[next_hesh_number].setID(hesh[next_next_hesh_number].getID()); //������������ � � ���������
		hesh[next_hesh_number].setT(hesh[next_next_hesh_number].getT()); //
		hesh[next_hesh_number].setL(hesh[next_next_hesh_number].getL()); //
		hesh[next_hesh_number].setD(hesh[next_next_hesh_number].getD()); //
		hesh[next_hesh_number].setP0(hesh[next_next_hesh_number].getP0()); // 
		hesh[next_hesh_number].setPi(hesh[next_next_hesh_number].getPi()); //
		hesh[next_next_hesh_number].setU(0); //��������� ������ U ��� ��������� ������ � 0
		//������ ������� C �� �������
	}
	return 1; //���������� 1, ���� �������� ������ �������
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
	cout<<"                                   "<<"��� �������"<<endl;
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
#pragma once
#include "IdtfString.h"
#include <string>
using namespace std;
class IdtfTable
{
IdtfString *id_table;
int length;
int pos;
public:
	IdtfTable(int);
	~IdtfTable(void);
	string getID(int);
	string getKey(int);
	int getSum(int);
	int getHesh_number(int);
	void setId_table(string, string, int, int);
	//int find_idtf_in_table(string key);
};


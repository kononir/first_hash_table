#include "StdAfx.h"
#include "IdtfTable.h"
#include "IdtfString.h"


IdtfTable::IdtfTable(int s): length(s), pos(0)
{
	id_table=new IdtfString[s];
}


IdtfTable::~IdtfTable(void)
{
	delete id_table;
}


string IdtfTable::getID(int a)
{
	return id_table[a].getID();
}


string IdtfTable::getKey(int a)
{
	return id_table[a].getKey();
}


int IdtfTable::getSum(int a)
{
	return id_table[a].getSum();
}


int IdtfTable::getHesh_number(int a)
{
	return id_table[a].getHesh_number();
}


void IdtfTable::setId_table(string key, string id, int sum, int hesh_number)
{
	id_table[pos].setKey(key);
	id_table[pos].setID(id);
	id_table[pos].setSum(sum);
	id_table[pos].setHesh_number(hesh_number);
	pos++;
}


/*int IdtfTable::find_idtf_in_table(string key)
{

}*/
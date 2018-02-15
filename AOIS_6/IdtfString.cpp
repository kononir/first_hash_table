#include "StdAfx.h"
#include "IdtfString.h"


IdtfString::IdtfString(void)
{
}


IdtfString::~IdtfString(void)
{
}


string IdtfString::getKey(void)
{
	return key;
}


string IdtfString::getID(void)
{
	return id;
}


int IdtfString::getSum(void)
{
	return sum;
}


int IdtfString::getHesh_number(void)
{
	return hesh_number;
}


void IdtfString::setKey(string k)
{
	key=k;
}


void IdtfString::setID(string i)
{
	id=i;
}


void IdtfString::setSum(int s)
{
	sum=s;
}


void IdtfString::setHesh_number(int h_n)
{
	hesh_number=h_n;
}
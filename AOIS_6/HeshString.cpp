#include "StdAfx.h"
#include "HeshString.h"


HeshString::HeshString(void): U(0)
{
}


HeshString::~HeshString(void)
{
}


string HeshString::getID(void)
{
	if(ID=="")
		return "<пусто>";
	return ID;
}


int HeshString::getC(void)
{
	if(C<0)
		return -111;
	return C;
}


int HeshString::getU(void)
{
	if(U<0)
		return -111;
	return U;
}


int HeshString::getT(void)
{
	if(T<0)
		return -111;
	return T;
}


int HeshString::getL(void)
{
	if(L<0)
		return -111;
	return L;
}


int HeshString::getD(void)
{
	if(D<0)
		return -111;
	return D;
}


int HeshString::getP0(void)
{
	if(P0<-1)
		return -111;
	return P0;
}


string HeshString::getPi(void)
{
	return Pi;
}


void HeshString::setID(string key_ID)
{
	ID=key_ID;
}


void HeshString::setC(int c)
{
	C=c;
}


void HeshString::setU(int u)
{
	U=u;
}


void HeshString::setT(int t)
{
	T=t;
}


void HeshString::setL(int l)
{
	L=l;
}


void HeshString::setD(int d)
{
	D=d;
}


void HeshString::setP0(int p0)
{
	P0=p0;
}


void HeshString::setPi(string pi)
{
	Pi=pi;
}
#pragma once
#include <string>
using namespace std;
class HeshString
{
	string ID;
	int C;
	int U;
	int T;
	int L;
	int D;
	int P0;
	string Pi;
public:
	HeshString(void);
	~HeshString(void);
	string getID(void);
	int getC(void);
	int getU(void);
	int getT(void);
	int getL(void);
	int getD(void);
	int getP0(void);
	string getPi(void);
	void setID(string key_ID);
	void setC(int);
	void setU(int);
	void setT(int);
	void setL(int);
	void setD(int);
	void setP0(int);
	void setPi(string info);
};


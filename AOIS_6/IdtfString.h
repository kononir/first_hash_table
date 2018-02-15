#pragma once
#include <string>;
using namespace std;
class IdtfString
{
string key;
string id;
int sum;
int hesh_number;
public:
	IdtfString(void);
	~IdtfString(void);
	string getKey(void);
	string getID(void);
	int getSum(void);
	int getHesh_number(void);
	void setKey(string);
	void setID(string);
	void setSum(int);
	void setHesh_number(int);
};


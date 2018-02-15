#pragma once
#include <string>
#include "HeshString.h"
//#include "IdtfTable.h"
using namespace std;
class HeshTable
{
	int size;
	HeshString *hesh;
	//IdtfTable *id_table;
	//static int idtf_number;
	int find_free_hesh(int hesh_number);
	int rec_find_next_hesh(int hesh_number);
	int rec_find_hesh_with_key(int hesh_number, string key);
	int rec_find_previous_hesh(int hesh_number, int next_hesh_number);
	//string find_key(string key);
public:
	HeshTable(int s);
	~HeshTable(void);
	int find_sum(string info);
	int find_hesh(int sum);
	int push_string(string key, string info);
	string pull_string(string key);
	int delete_string(string key);
	void show_table(void);
};


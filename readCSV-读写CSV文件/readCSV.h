#pragma once
#define DATA_MAX_NUM 50
#include<map>
#include<string>

struct CSVtable {
	int table_x_num;
	int table_y_num;
	std::map<std::string, int> table_x;
	std::map<std::string, int> table_y;
	std::map<std::string, double**>table_x_data;
	std::map<std::string, double*>table_y_data;
	struct CSVtable* last_table;
	struct CSVtable* next_table;
};

class readCSV {
public:
	readCSV();
	~readCSV();
	void readFile(std::string name);
	double getData(std::string key1, std::string key2);
	void getData(std::string key1,double* container);
	void getData(std::string key1,double* container,int num);
	void getData(std::string key1,double* container,int begin_ID,int end_ID);
private:
	int table_num;
	std::map<std::string, struct CSVtable*> key_table;
	CSVtable* first_table;
};
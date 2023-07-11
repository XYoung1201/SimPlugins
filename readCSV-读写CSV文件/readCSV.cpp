#include "readCSV.h"
#include <fstream>
#include <string>

using namespace std;

readCSV::readCSV() {
	table_num = 0;
}

readCSV::~readCSV() {
	map<string, double*>::iterator iter;
	map<string, double**>::iterator iter_x;
	CSVtable* tb=first_table;
	while (true) {
		for (iter = tb->table_y_data.begin(); iter != tb->table_y_data.end(); iter++) {
			delete[] iter->second;
		}
		for (iter_x = tb->table_x_data.begin(); iter_x != tb->table_x_data.end(); iter_x++) {
			delete[] iter_x->second;
		}
		if(tb->next_table==first_table){
			delete tb;
			break;
		}
		tb=tb->next_table;
		delete tb->last_table;
	}
}

void readCSV::readFile(string Filename) {
	ifstream CSVfile(Filename.c_str());
	char line[4096];
	char name[4096];
	char value[4096];
	char* it;
	int i,j;
	CSVtable* tb = NULL;
	while (true) {
		CSVfile.getline(line, 4096);
		if (CSVfile.eof()) {
			break;
		}
		bool new_table = false;
		bool new_line = false;
		bool new_blank = false;
		line[0] == ',' ? line[1] == ',' ? new_blank = true : new_table = true : new_line = true;
		if (new_table) {
			table_num++;
			if (tb == NULL) {
				first_table = new CSVtable;
				tb = first_table;
			}
			else {
				tb->next_table = new CSVtable;
				tb->next_table->last_table = tb;
				tb = tb->next_table;
			}
			it = line+1;
			tb->table_x_num = 0;
			tb->table_y_num = 0;
			i = 0; 
			while (true) {
				name[i++] = *it++;
				if (*it == ','|| *it == '\0') {
					name[i] = '\0';
					tb->table_x[name] = tb->table_x_num++;
					key_table[name] = tb;
					i = 0;
					if (*it == '\0') {
						break;
					}
					if (*++it == ',') {
						break;
					}
				}
			}
		}
		if (new_line) {
			i = 0;
			it = line;
			while (*it != ',') {
				name[i++] = *it++;
			}
			name[i] = '\0';
			tb->table_y[name] = tb->table_y_num++;
			key_table[name] = tb;
			tb->table_y_data[name] = new double[tb->table_x_num];

			i = 0;
			j = 0;
			it++;
			while (*it != '\0') {
				value[i++] = *it++;
				if (*it == ','||*it=='\0') {
					value[i] = '\0';
					tb->table_y_data[name][j++] = atof(value);
					if (*it == '\0') {
						break;
					}
					i = 0;
					it++;
				}
			}
		}
		if (new_blank) {
			continue;
		}
	}
	tb->next_table = first_table;
	first_table->last_table = tb;
	tb = first_table;
	map<string, int>::iterator iter_x;
	map<string, int>::iterator iter_y;
	while (true) {
		for (iter_x = tb->table_x.begin(); iter_x != tb->table_x.end(); iter_x++) {
			tb->table_x_data[iter_x->first] = new double*[tb->table_y_num];
			for (iter_y = tb->table_y.begin(); iter_y != tb->table_y.end(); iter_y++) {
				tb->table_x_data[iter_x->first][iter_y->second] = &(tb->table_y_data[iter_y->first][iter_x->second]);
			}
		}
		if (tb->next_table == first_table) {
			break;
		}
		tb = tb->next_table;
	}
}

double readCSV::getData(std::string key1, std::string key2) {
	CSVtable* tb;
	tb = key_table[key1];
	if (tb->table_x.count(key1) != 0) {
		if(tb->table_y.count(key2)!=0){
			return *(tb->table_x_data[key1][tb->table_y[key2]]);
		}
	}
	else {
		if(tb->table_x.count(key2)!=0){
			return tb->table_y_data[key1][tb->table_x[key2]];
		}
	}

	tb=key_table[key2];
	if (tb->table_x.count(key1) != 0) {
		return *(tb->table_x_data[key1][tb->table_y[key2]]);
	}
	else {
		return tb->table_y_data[key1][tb->table_x[key2]];
	}
}
void readCSV::getData(std::string key1, double* container) {
	CSVtable* tb;
	tb = key_table[key1];
	if (tb->table_x.count(key1) != 0) {
		for (int i = 0; i < tb->table_y_num; i++) {
			container[i] = *tb->table_x_data[key1][i];
		}
	}
	else {
		for (int i = 0; i < tb->table_x_num; i++) {
			container[i] = tb->table_y_data[key1][i];
		}
	}
}

void readCSV::getData(std::string key1, double* container,int num) {
	CSVtable* tb;
	tb = key_table[key1];
	if (tb->table_x.count(key1) != 0) {
		for (int i = 0; i < num; i++) {
			container[i] = *tb->table_x_data[key1][i];
		}
	}
	else {
		for (int i = 0; i < num; i++) {
			container[i] = tb->table_y_data[key1][i];
		}
	}
}

void readCSV::getData(std::string key1, double* container,int begin_num,int end_num) {
	CSVtable* tb;
	tb = key_table[key1];
	if (tb->table_x.count(key1) != 0) {
		for (int i = begin_num; i < end_num; i++) {
			container[i] = *tb->table_x_data[key1][i];
		}
	}
	else {
		for (int i = begin_num; i < end_num; i++) {
			container[i] = tb->table_y_data[key1][i];
		}
	}
}
#pragma once
#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include <map>
#include <algorithm>

using namespace std;

//struct dataNodeRecord {
//	int dataType;
//	void* dataAddress;
//	char* dataName;
//	struct dataNodeRecord* next;
//	struct dataNodeRecord* first;
//	dataNodeRecord(struct dataNodeRecord** last, int type, void* address) {
//		if (*last == NULL) {
//			first = this;
//		}
//		else {
//			(*last)->next = this;
//			first = (*last)->first;
//		}
//		dataType = type;
//		dataAddress = address;
//		next = NULL;
//		*last = this;
//		dataName = NULL;
//	}
//};

class easyRead {
	ifstream file;
public:
	struct dataNodeRecord* dataNode;
	map<string, int> columnNames;
	bool first;
	easyRead(bool headerReader = false);
	easyRead(const char* fileName,bool headerReader = false);
	~easyRead();
	void loadFile(const char* fileName);
	void bindData(int columnNum, int* a);
	void bindData(int columnNum, double* a);
	void bindData(int columnNum, bool* a);
	void bindData(string columnName,int *a);
	void bindData(string columnName,double *a);
	void bindData(string columnName,bool *a);
	friend easyRead& operator << (easyRead& ew, double* a);
	friend easyRead& operator << (easyRead& ew, int* a);
	friend easyRead& operator << (easyRead& ew, bool* a);
	bool read();
};

#include "stdafx.h"
#include "easyRead.h"

easyRead::easyRead(bool headerReader) {
	dataNode = NULL;
	first = headerReader;
}

easyRead::easyRead(const char* filePath, bool headerReader) {
	dataNode = NULL;
	first = headerReader;
	loadFile(filePath);
}

easyRead::~easyRead()
{
	struct dataNodeRecord* iter = dataNode->first;
	struct dataNodeRecord* iterNext;
	while(iter!=NULL){
		iterNext = iter->next;
		delete iter;
		iter = iterNext;
	}
	if(file.is_open())
		file.close();
}

void easyRead::loadFile(const char* filePath) {
	file.open(filePath);
	string line;
	getline(file, line);
	if (first) {
		string item;
		int ID = 0;
		stringstream s_line(line);
		while (getline(s_line, item, ',')) {
			columnNames.insert(pair<string, int>(item, ID++));
			dataNode = new struct dataNodeRecord(&dataNode, -1,NULL);
		}
	}
	else {
		int lineCount = count(line.begin(), line.end(), ',') + 1;
		while (lineCount-- > 0)
			dataNode = new struct dataNodeRecord(&dataNode, -1, NULL);
		file.seekg(0, ios::beg);
	}
	dataNode = dataNode->first;
}

easyRead& operator<< (easyRead& ew, int* a) {
	ew.dataNode->dataType = 1;
	ew.dataNode->dataAddress = (void*)a;
	if(ew.dataNode->next != NULL)
		ew.dataNode = ew.dataNode->next;
	return ew;
}

easyRead& operator<< (easyRead& ew, double* a) {
	ew.dataNode->dataType = 0;
	ew.dataNode->dataAddress = (void*)a;
	if(ew.dataNode->next != NULL)
		ew.dataNode = ew.dataNode->next;
	return ew;
}

easyRead& operator<< (easyRead& ew, bool* a) {
	ew.dataNode->dataType = 2;
	ew.dataNode->dataAddress = (void*)a;
	if(ew.dataNode->next != NULL)
		ew.dataNode = ew.dataNode->next;
	return ew;
}

void easyRead::bindData(int columnNum, int* a) {
	struct dataNodeRecord* iter = dataNode->first;
	while (columnNum-- > 0)
		iter = iter->next;
	iter->dataType = 1;
	iter->dataAddress = (void*)a;
}
void easyRead::bindData(int columnNum, double* a) {
	struct dataNodeRecord* iter = dataNode->first;
	while (columnNum-- > 0)
		iter = iter->next;
	iter->dataType = 0;
	iter->dataAddress = (void*)a;
}
void easyRead::bindData(int columnNum, bool* a) {
	struct dataNodeRecord* iter = dataNode->first;
	while (columnNum-- > 0)
		iter = iter->next;
	iter->dataType = 2;
	iter->dataAddress = (void*)a;
}
void easyRead::bindData(string columnName, int* a) {
	int columnNum = columnNames[columnName];
	struct dataNodeRecord* iter = dataNode->first;
	while (columnNum-- > 0)
		iter = iter->next;
	iter->dataType = 1;
	iter->dataAddress = (void*)a;
}
void easyRead::bindData(string columnName, double* a) {
	int columnNum = columnNames[columnName];
	struct dataNodeRecord* iter = dataNode->first;
	while (columnNum-- > 0)
		iter = iter->next;
	iter->dataType = 0;
	iter->dataAddress = (void*)a;
}
void easyRead::bindData(string columnName, bool* a) {
	int columnNum = columnNames[columnName];
	struct dataNodeRecord* iter = dataNode->first;
	while (columnNum-- > 0)
		iter = iter->next;
	iter->dataType = 2;
	iter->dataAddress = (void*)a;
}

bool easyRead::read() {
	string line;
	getline(file, line);
	string item;
	int ID = 0;
	struct dataNodeRecord* iter = dataNode->first;
	stringstream s_line(line);
	while (getline(s_line, item, ',')) {
		switch (iter->dataType) {
		case(-1):
			break;
		case(0):
			*(double*)iter->dataAddress = stod(item);
			break;
		case(1):
			*(double*)iter->dataAddress = stoi(item);
			break;
		case(2):
			*(double*)iter->dataAddress = (bool)stoi(item);
			break;
		default:
			;
		}
		iter = iter->next;
	}
	if(file.eof())
		return true;
	return false;	
}


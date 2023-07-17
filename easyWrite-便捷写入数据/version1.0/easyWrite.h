#pragma once
#include <fstream>
#include <direct.h>

using namespace std;

struct dataNodeRecord {
	int dataType;
	char* dataName;
	void* dataAddress;
	struct dataNodeRecord* first;
	struct dataNodeRecord* next;
	dataNodeRecord(struct dataNodeRecord** last,int type, void* address) {
		if (*last == NULL) {
			*last = this;
			first = this;
			dataType = type;
			dataAddress = address;
			next = NULL;
			dataName = NULL;
		}
		else {
			first = (*last)->first;
			dataType = type;
			dataAddress = address;
			next = NULL;
			(*last)->next = this;
			*last = this;
			dataName = NULL;
		}
	}
};

class easyWrite
{
	ofstream file;
public:
	struct dataNodeRecord* dataNode;
	bool first;
	easyWrite();
	easyWrite(const char* fileName,bool headerWrite);
	~easyWrite();
	friend easyWrite& operator<< (easyWrite& ew, double* a);
	friend easyWrite& operator<< (easyWrite& ew, int* a);
	friend easyWrite& operator<< (easyWrite& ew, bool* a);
	friend easyWrite& operator<< (easyWrite& ew, const char* a);
	friend easyWrite& operator<< (easyWrite& ew, double a);
	friend easyWrite& operator<< (easyWrite& ew, int a);
	friend easyWrite& operator<< (easyWrite& ew, bool a);
	friend easyWrite& operator<< (easyWrite& ew, char a);
	void write();
};


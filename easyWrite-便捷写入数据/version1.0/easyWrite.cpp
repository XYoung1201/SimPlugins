#include "easyWrite.h"

easyWrite::easyWrite()
{
	_mkdir("easyWrite");
	file.open("easyWrite/data.txt",ios::out|ios::trunc);
	first = true;
	dataNode = NULL;

}

easyWrite::easyWrite(const char* fileName,bool headerWrite)
{
	_mkdir("easyWrite");
	string location = "easyWrite/";
	location.append(fileName);
	file.open(location,ios::out|ios::trunc);
	first = headerWrite;
	dataNode = NULL;

}

easyWrite::~easyWrite()
{
	file.close();
	if (dataNode == NULL)
		return;

	struct dataNodeRecord* iter_last = dataNode->first;
	for (struct dataNodeRecord* iter = dataNode->first->next; iter != NULL; iter = iter->next) {
		delete iter_last;
		iter_last = iter;
	}
}

void easyWrite::write()
{
	if(dataNode == NULL)
		return;
	if(first){
		first = false;
		for(struct dataNodeRecord* iter = dataNode->first;iter!=NULL;iter=iter->next){
			if(iter->dataName != NULL)
				file << iter->dataName;
			else
				file << "data";
			if(iter->next!=NULL)
				file << ',';
		}
		file << endl;
	}
	for(struct dataNodeRecord* iter = dataNode->first;iter!=NULL;iter=iter->next){
		if (iter->dataType == 1)
			file << *(int*)iter->dataAddress;
		if (iter->dataType == 0)
			file << *(double*)iter->dataAddress;
		if (iter->dataType == 2)
			file << *(bool*)iter->dataAddress;
		if(iter->next!=NULL)
			file << ',';
	}
	file << endl;
}

easyWrite& operator<< (easyWrite& ew, const char* a) {
	if(ew.dataNode == NULL)
		return ew;
	for (struct dataNodeRecord* iter = ew.dataNode->first; iter != NULL; iter = iter->next) {
		if(iter->dataName == NULL){
			iter->dataName = new char[strlen(a)+1];
			strcpy_s(iter->dataName,strlen(a)+1, a);
			break;
		}
	}
		return ew;
}

easyWrite& operator<< (easyWrite& ew, int* a) {
		new dataNodeRecord(&ew.dataNode, 1, (void*)a);
		return ew;
}

easyWrite& operator<< (easyWrite& ew, double* a) {
		new dataNodeRecord(&ew.dataNode, 0, (void*)a);
		return ew;
}

easyWrite& operator<< (easyWrite& ew, bool* a) {
		new dataNodeRecord(&ew.dataNode, 2, (void*)a);
		return ew;
}

easyWrite& operator<< (easyWrite& ew, int a) {
	ew.file << a;
		return ew;
}

easyWrite& operator<< (easyWrite& ew, double a) {
	ew.file << a;
		return ew;
}

easyWrite& operator<< (easyWrite& ew, bool a) {
	ew.file << a;
		return ew;
}

easyWrite& operator<< (easyWrite& ew, char a) {
	ew.file << a;
		return ew;
}



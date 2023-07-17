#include "easyWrite.h"

easyWrite::easyWrite()
{
	_mkdir("easyWrite");
	file.open("easyWrite/data.txt",ios::out|ios::trunc);
	first = true;
	dataNode = NULL;
	intervalTime = 50;
}

easyWrite::easyWrite(const char* fileName,bool headerWrite,int writeInterval)
{
	_mkdir("easyWrite");
	string location = "easyWrite/";
	location.append(fileName);
	file.open(location,ios::out|ios::trunc);
	first = headerWrite;
	dataNode = NULL;
	intervalTime = writeInterval;
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

void simuThread(easyWrite* ew) {
	while (ew->runningWrite) {
		if(ew->dataNode == NULL)
			return;
		if(ew->first){
			ew->first = false;
			for(struct dataNodeRecord* iter = ew->dataNode->first;iter!=NULL;iter=iter->next){
				if(iter->dataName != NULL)
					ew->file << iter->dataName;
				else
					ew->file << "data";
				if(iter->next!=NULL)
					ew->file << ',';
			}
			ew->file << endl;
		}
		for(struct dataNodeRecord* iter = ew->dataNode->first;iter!=NULL;iter=iter->next){
			if (iter->dataType == 1)
				ew->file << *(int*)iter->dataAddress;
			if (iter->dataType == 0)
				ew->file << *(double*)iter->dataAddress;
			if (iter->dataType == 2)
				ew->file << *(bool*)iter->dataAddress;
			if(iter->next!=NULL)
				ew->file << ',';
		}
		ew->file << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(ew->intervalTime));
	}
}

void easyWrite::startWrite()
{
	runningWrite = true;
	std::thread newThread(simuThread, this);
	newThread.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void easyWrite::stopWrite() {
	std::this_thread::sleep_for(std::chrono::milliseconds(intervalTime));
	runningWrite = false;
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



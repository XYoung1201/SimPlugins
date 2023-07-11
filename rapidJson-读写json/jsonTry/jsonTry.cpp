// jsonTry.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "document.h"


#include <iostream>
#include <fstream>

#include <iostream>

using namespace rapidjson;
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
 
#include <stdlib.h>
using namespace std;

struct MyHandler {
    bool Null() { cout << "Null()" << endl; return true; }
    bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
    bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
    bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
    bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
    bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
    bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
    bool RawNumber(const char* str, SizeType length, bool copy) { 
        cout << "Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool String(const char* str, SizeType length, bool copy) { 
        cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool StartObject() { cout << "StartObject()" << endl; return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
    bool StartArray() { cout << "StartArray()" << endl; return true; }
    bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
};

string readFileIntoString(char * filename)
{
ifstream ifile(filename);
//将文件读入到ostringstream对象buf中
ostringstream buf;
char ch;
while(buf&&ifile.get(ch))
buf.put(ch);
//返回与流对象buf关联的字符串
return buf.str();
}


int main() {
    const char json[] = "{\"abc\":{\"abc\":\"def\"}}";
	char * fn="config.txt";
	string str;
	str=readFileIntoString(fn);
	Document doc;
	doc.Parse(str.c_str());
	double a = doc["EarthData"]["J2"].GetDouble();
    return 0;
}



#include<stdio.h>
#include<windows.h>
#include<string>
#include<iostream>
#include "tinyxml2.h"

using namespace tinyxml2;

void getRange(const char* str,int* nums) {
	nums[0] = atoi(str);
	while (*(str++) != ',');
	nums[1] = atoi(str);
}

void create_xml_file(char* filename) {
	//创建声明
	tinyxml2::XMLDocument doc;
	//doc.LoadFile("model_file_write.xml");
	XMLDeclaration* declaration = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-16\"");
	doc.InsertFirstChild(declaration);

	//创建节点
	XMLElement* root = doc.NewElement("ClassSet");
	//插入节点
	doc.InsertEndChild(root);

	XMLElement* entityModelList = doc.NewElement("EntityModelList");
	root->InsertEndChild(entityModelList);

	XMLElement* entityModel = doc.NewElement("EntityModel");
	entityModelList->InsertFirstChild(entityModel);
	entityModel->SetAttribute("Caption", "XXX");//设置标签属性

	XMLElement* entityModelID = doc.NewElement("EntityModelID");
	entityModel->InsertEndChild(entityModelID);
	entityModelID->InsertEndChild(doc.NewText("070101002"));//标签内插入值

	XMLElement* entityModelSort = doc.NewElement("EntityModelSort");
	entityModel->InsertEndChild(entityModelSort);
	entityModelSort->InsertEndChild(doc.NewText("8163"));

	XMLElement* entityName = doc.NewElement("EntityName");
	entityModel->InsertEndChild(entityName);
	entityName->InsertEndChild(doc.NewText("XXXX"));

	XMLElement* entityType = doc.NewElement("EntityType");
	entityModel->InsertEndChild(entityType);
	entityType->InsertEndChild(doc.NewText("型号"));

	XMLElement* initAttribute = doc.NewElement("InitAttribute");
	entityModel->InsertEndChild(initAttribute);

	XMLElement* att = doc.NewElement("Att");
	initAttribute->InsertEndChild(att);
	att->SetAttribute("AttName", "工作模式");
	att->SetAttribute("AttDataType", "Enum");
	att->SetAttribute("AttDef", "eXXXX");
	att->SetAttribute("AttUnit", "1:xxxxx;2:xxxxxx");
	att->SetAttribute("AttDefaultValue", "1");
	att->SetAttribute("AttRange", "");
	att->SetAttribute("AttKind", "1");
	att->SetAttribute("AttMaxNum", "");
	att->SetAttribute("AttNote", "0");
	att->SetAttribute("ReadOnly", "0");
	att->SetAttribute("ParaUnVisible", "0");

	XMLElement* attributeList = doc.NewElement("AttributeList");
	entityModel->InsertEndChild(attributeList);

	att = doc.NewElement("Att");
	attributeList->InsertEndChild(att);
	att->SetAttribute("AttName", "是否使用设置参数");
	att->SetAttribute("AttDataType", "Enum");
	att->SetAttribute("AttDef", "bUsePara");
	att->SetAttribute("AttUnit", "0：不是，1：是；");
	att->SetAttribute("AttDefaultValue", "0");
	att->SetAttribute("AttRange", "0,1");
	att->SetAttribute("AttKind", "1");
	att->SetAttribute("AttMaxNum", "");
	att->SetAttribute("AttNote", "");
	att->SetAttribute("ReadOnly", "0");
	att->SetAttribute("ParaUnVisible", "0");

	att = doc.NewElement("Att");
	attributeList->InsertEndChild(att);
	att->SetAttribute("AttName", "天线");
	att->SetAttribute("AttDataType", "Complex");
	att->SetAttribute("AttDef", "Antenna");
	att->SetAttribute("AttUnit", "");
	att->SetAttribute("AttDefaultValue", "");
	att->SetAttribute("AttRange", "");
	att->SetAttribute("AttKind", "1");
	att->SetAttribute("AttMaxNum", "");
	att->SetAttribute("AttNote", "");
	att->SetAttribute("ReadOnly", "0");
	att->SetAttribute("ParaUnVisible", "0");

	XMLElement* attDetail = doc.NewElement("AttDetail");
	att->InsertEndChild(attDetail);

	attDetail->SetAttribute("AttName", "天线序号");
	attDetail->SetAttribute("AttDataType", "string");
	attDetail->SetAttribute("AttDef", "AntennaNo");
	attDetail->SetAttribute("AttUnit", "");
	attDetail->SetAttribute("AttDefaultValue", "1");
	attDetail->SetAttribute("AttRange", "");
	attDetail->SetAttribute("AttKind", "1+");
	attDetail->SetAttribute("AttMaxNum", "");
	attDetail->SetAttribute("AttNote", "");
	attDetail->SetAttribute("ReadOnly", "1");
	attDetail->SetAttribute("ParaUnVisible", "1");

	XMLElement* methodList = doc.NewElement("MethodList");
	entityModel->InsertEndChild(methodList);

	XMLElement* method = doc.NewElement("Method");
	methodList->InsertEndChild(method);

	XMLElement* methodName = doc.NewElement("MethodName");
	method->InsertEndChild(methodName);
	methodName->InsertEndChild(doc.NewText("ZoneTask"));

	XMLElement* methodDef = doc.NewElement("MethodDef");
	method->InsertEndChild(methodDef);
	methodDef->InsertEndChild(doc.NewText("任务区域"));

	XMLElement* isAllTime = doc.NewElement("IsAllTime");
	method->InsertEndChild(isAllTime);
	isAllTime->InsertEndChild(doc.NewText("0"));

	att = doc.NewElement("Att");
	method->InsertEndChild(att);
	att->SetAttribute("AttName", "区域中心位置信息");
	att->SetAttribute("AttDataType", "Complex");
	att->SetAttribute("AttDef", "sPostion");
	att->SetAttribute("AttUnit", "");
	att->SetAttribute("AttDefaultValue", "");
	att->SetAttribute("AttRange", "");
	att->SetAttribute("AttKind", "1");
	att->SetAttribute("AttMaxNum", "");
	att->SetAttribute("AttNote", "区域的中心位置.");
	att->SetAttribute("ReadOnly", "0");
	att->SetAttribute("ParaUnVisible", "0");

	attDetail = doc.NewElement("AttDetail");
	att->InsertEndChild(attDetail);
	attDetail->SetAttribute("AttName", "中心经度");
	attDetail->SetAttribute("AttDataType", "double");
	attDetail->SetAttribute("AttDef", "dCentorLon");
	attDetail->SetAttribute("AttUnit", "度");
	attDetail->SetAttribute("AttRange", "-180,180");
	attDetail->SetAttribute("AttDefaultValue", "0");
	attDetail->SetAttribute("AttKind", "1");
	attDetail->SetAttribute("ReadOnly", "0");
	attDetail->SetAttribute("ParaUnVisible", "0");

	attDetail = doc.NewElement("AttDetail");
	att->InsertEndChild(attDetail);
	attDetail->SetAttribute("AttName", "中心纬度");
	attDetail->SetAttribute("AttDataType", "double");
	attDetail->SetAttribute("AttDef", "dCentorLat");
	attDetail->SetAttribute("AttUnit", "度");
	attDetail->SetAttribute("AttRange", "-90,90");
	attDetail->SetAttribute("AttDefaultValue", "0");
	attDetail->SetAttribute("AttKind", "1");
	attDetail->SetAttribute("ReadOnly", "0");
	attDetail->SetAttribute("ParaUnVisible", "0");

	attDetail = doc.NewElement("AttDetail");
	att->InsertEndChild(attDetail);
	attDetail->SetAttribute("AttName", "中心高度");
	attDetail->SetAttribute("AttDataType", "float");
	attDetail->SetAttribute("AttDef", "fCentorHeight");
	attDetail->SetAttribute("AttUnit", "米");
	attDetail->SetAttribute("AttRange", "0,1000000");
	attDetail->SetAttribute("AttDefaultValue", "0");
	attDetail->SetAttribute("AttKind", "1");
	attDetail->SetAttribute("ReadOnly", "0");
	attDetail->SetAttribute("ParaUnVisible", "0");

	XMLElement* relation = doc.NewElement("Relation");
	entityModel->InsertEndChild(relation);

	XMLElement* resourceModelList = doc.NewElement("ResourceModelList");
	root->InsertEndChild(resourceModelList);

	doc.SaveFile(filename);
}

void read_xml_file(char* filename) {
	//创建声明
	tinyxml2::XMLDocument doc;
	doc.LoadFile("model_file_write.xml");
	XMLElement* root = doc.RootElement();
	XMLElement* entityList = root->FirstChildElement();
	XMLElement* entityModel = entityList->FirstChildElement();
	//获取标签内字符串属性，输出字符串“1234”
	printf("%s\n", entityModel->Attribute("Caption"));
	//获取标签内整型属性，输出整型数字1234
	printf("%d\n", entityModel->IntAttribute("Caption"));
	//获取标签内浮点型属性，输出浮点型数字1234.0000
	printf("%lf\n\n", entityModel->DoubleAttribute("Caption"));
	
	//获取标签内字符串值,输出字符串“8163”
	printf("%s\n", entityModel->FirstChildElement("EntityModelSort")->GetText());
	//获取标签内整型值，输出整型8163
	printf("%d\n", entityModel->FirstChildElement("EntityModelSort")->IntText());
	//获取标签内浮点型值，输出浮点型8163.0000
	printf("%lf\n\n", entityModel->FirstChildElement("EntityModelSort")->DoubleText());

	//获取标签内范围,原理是对提取字符串进行拆解，可用于标签内值与标签属性
	int nums[2];
	getRange(entityModel->FirstChildElement("EntityName")->GetText(), nums);
	printf("%d,%d", nums[0], nums[1]);
}

void change_xml_file(char* filename) {
	//创建声明
	tinyxml2::XMLDocument doc;
	doc.LoadFile("model_file_write.xml");
	XMLElement* root = doc.RootElement();
	XMLElement* entityList = root->FirstChildElement();
	XMLElement* entityModel = entityList->FirstChildElement();
	//更改标签属性
	entityModel->SetAttribute("Caption", "1234");
	//更改标签内的值
	entityModel->FirstChildElement("EntityName")->SetText("dddd");
	//保存
	doc.SaveFile("model_file_write.xml");
}

void show_xml_file(char* filename) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("model_file_write.xml");
	doc.Print();
}

int main() {
	create_xml_file("model_file_write.xml");
	change_xml_file("model_file_write_xml");
	read_xml_file("model_file_write_xml");
	//show_xml_file("model_file_write_xml");
	system("pause");
	return 0;
}
// AEROREAD.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"interpolytion.hpp"

int main(){
	Interpolytion poly;
	int input_num = 2;
	int output_num = 3;
	double minValue[] = { 1,0 };
	double maxValue[] = { 4,15 };
	double dataStep[] = { 1,3 };
	bool boundLim[] = {true,true,true};
	poly.config(input_num,output_num,minValue,maxValue,dataStep);
	poly.boundryLimit(boundLim);
	poly.read_file("data.txt");
	double data_input[] = { 1,0 };
	double *a=poly.interpolyte(data_input);
	for(int i=0;i<3;i++)
		printf("%lf\t",a[i]);
}
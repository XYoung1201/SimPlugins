// AEROREAD.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"interpolytion.hpp"

int main(){
	Interpolytion poly;
	poly.read_file("data.txt");
	double data_input[] = { 1,0 };
	double *a=poly.interpolyte(data_input);
	for(int i=0;i<3;i++)
		printf("%lf\t",a[i]);
}
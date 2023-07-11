#pragma once
#include<cmath>

class smoothAcc
{
	double sData;
	double rate;
	double rate_interval;
public:
	void initial(double smoothTime,double step);
	void setStart(double startData);
	double smooth(double inputData); 
};


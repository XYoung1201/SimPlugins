#include "stdafx.h"
#include "smoothAcc.h"

void smoothAcc::initial(double smoothTime, double step)
{
	rate = 1.0 ;
	int stepNum = ceil(smoothTime/step+0.5);
	rate_interval = 1.0 / stepNum;
}

void smoothAcc::setStart(double startData)
{
	sData = startData;
}

double smoothAcc::smooth(double inputData)
{
	rate -= rate_interval;
	if (rate <= 0)
		return inputData;
	return sData * rate + (1 - rate) * inputData;
}

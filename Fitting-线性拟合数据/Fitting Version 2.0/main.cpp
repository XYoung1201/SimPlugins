#include <stdio.h>
#include <vector>
#include "LinearFitting.h"

int main() {
	int input_dim = 3;
	int output_dim = 2;
	LinearFitting a("data.txt",input_dim,output_dim);
	double x_pre[] = { 16,17,18 };
	double* y = a.Predicting(x_pre);
	for (int i = 0; i < 2; i++)
		printf("%lf\t", y[i]);
	return 0;
}
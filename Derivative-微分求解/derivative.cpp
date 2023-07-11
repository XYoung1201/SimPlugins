#include <iostream>
#include <math.h>

using namespace std;

double function1(double* parameters) {
	return cos(parameters[0]) + sin(parameters[1]);
}

double function2(double x) {
	return x * x * x;
}

double derivative(double(*func)(double*),double* parameters,int n,double step=0.01) {
	parameters[n] += 2 * step;
	double f_p2 = func(parameters);
	parameters[n] -= step;
	double f_p1 = func(parameters);
	parameters[n] -= 2 * step;
	double f_n1 = func(parameters);
	parameters[n] -= step;
	double f_n2 = func(parameters);
	return (-f_p2 + 8 * f_p1 - 8 * f_n1 + f_n2) / (12 * step);
}

double derivative(double(*func)(double),double x,double step = 0.01) {
	x += 2 * step;
	double f_p2 = func(x);
	x -= step;
	double f_p1 = func(x);
	x -= 2 * step;
	double f_n1 = func(x);
	x -= step;
	double f_n2 = func(x);
	return (-f_p2 + 8 * f_p1 - 8 * f_n1 + f_n2) / (12 * step);
}

int main() {
	double a[2] = { 2,1 };
	cout << derivative(function1, a, 1);
}
#pragma once
#include<stdlib.h>

class RungeKutta {
public:
	RungeKutta();
	void setDifferentianEquation(void* equation, int var_length);
	double run(double* y, void* parameters=NULL, double step = 0.01,double *t_out=NULL);
	void set_t(double t);
	void set_t_span(double t_span);
	void set_t_end(double t_end);
	~RungeKutta();
private:
	double t;
	double t_end;
	int N;
	void** differential_equations;
	int* var_length;
	double* s1, * s2, * s3, * s4, * temp;
};

void RungeKutta::set_t(double t) {
	this->t = t;
}
void RungeKutta::set_t_span(double t_span) {
	this->t_end = t + t_span;
}
void RungeKutta::set_t_end(double t_end) {
	this->t_end = t_end;
}

RungeKutta::RungeKutta() {
	s1 = (double*)malloc(sizeof(double) * 512);
	s2 = (double*)malloc(sizeof(double) * 512);
	s3 = (double*)malloc(sizeof(double) * 512);
	s4 = (double*)malloc(sizeof(double) * 512);
	temp = (double*)malloc(sizeof(double) * 512);

	var_length = NULL;
	differential_equations = NULL;
	N = 0;
	t = 0;
	t_end = 10;
}

RungeKutta::~RungeKutta() {
	free(var_length);
	free(differential_equations);
	free(s1);
	free(s2);
	free(s3);
	free(s4);
	free(temp);
}

void RungeKutta::setDifferentianEquation(void* equation, int var_length) {
	void** last = differential_equations;
	int* varl_last = this->var_length;
	this->N++;
	differential_equations = (void**)malloc(sizeof(void*) * this->N);
	this->var_length = (int*)malloc(sizeof(int) * this->N);
	for (int i = 0; i < this->N - 1; i++) {
		differential_equations[i] = last[i];
		this->var_length[i] = varl_last[i];
	}
	differential_equations[N - 1] = equation;
	this->var_length[N - 1] = var_length;
	free(last);
	free(varl_last);
}

void vecSum(double C1, double C2, double* x1, double* x2, double* y,int N) {
	for (int i = 0; i < N; i++)
		y[i] = C1 * x1[i] + C2 * x2[i];
}

double RungeKutta::run(double* y0,void* parameters, double step,double* t_out) {
	void (*func)(double t, double* y,double* dy,void* parameters);
	double* y = y0;
	
	for (int i = 0; i < N; i++) {
		func = (void(*) (double t,double* y,double* dy,void* parameters))differential_equations[i];
		func(t, y, s1,parameters);
		vecSum(1, step / 2, y, s1, temp, var_length[i]);
		func(t + step / 2, temp, s2, parameters);
		vecSum(1, step / 2, y, s2, temp, var_length[i]);
		func(t + step / 2, temp, s3, parameters);
		vecSum(1, step, y, s3, temp, var_length[i]);
		func(t + step, temp, s4, parameters);
		vecSum(1, 2, s1, s2, temp, var_length[i]);
		vecSum(1, 2, temp, s3, temp, var_length[i]);
		vecSum(1, 1, temp, s4, temp, var_length[i]);
		vecSum(1, step / 6, y, temp, y, var_length[i]);
		y += var_length[i];
	}

	t += step;
	if (t_out != NULL)
		*t_out = t;
	if (t >= t_end)
		return false;
	else
		return true;
}
#include "Dense"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#pragma once
class LinearFitting
{
private:
	Eigen::MatrixXd W;
	int N;
	int m;
	int n;
	Eigen::VectorXd x;
	Eigen::VectorXd y;
	double* y_out;
	void getW(const Eigen::MatrixXd& X, const Eigen::MatrixXd& Y);
public:
	LinearFitting(const std::string fileName, const int input_dim, const int output_dim);
	~LinearFitting();
	double* Predicting(double* x);
};


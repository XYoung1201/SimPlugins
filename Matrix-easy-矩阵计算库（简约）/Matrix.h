#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class CMatrix
{
public:
	CMatrix(void);
	~CMatrix(void);

private:
	double *PBUF,*PA[25],*PW[25];//25
	int PM,PN;

	int m,n,ka;
	double **ia,**u,**v,**aa,eps;
	double *s,*e,*w,fg[2],cs[2];

private:
	void GetMatrix(double *A, int M, int N);
	double GetMainElement(int k);
	int Jordan_G();//Jordan-Gauss

	void GInv_initial(int mm, int nn);
	void GInv_input(double* A, int M, int N);
	void GInv_uav();
	void GInv_ppp();
	void GInv_sss();
	void GInv_Math();
	void GInv_output(double* A, int N, int M);

public:
	//矩阵求逆
	int MatrixInversion(double *A,double *B, int n);
	//矩阵求行列式
	double Determinant(double *A, int n);
	//矩阵相加
	void MatrixAdd(double *A, double *B, double *C, int PM, int PN);
	//矩阵相减
	void MatrixMus(double *A, double *B, double *C, int PM, int PN);
	//矩阵相乘
	void MatrixMul(double *A, double *B, double *C, int PM, int PN, int PQ);
	//矩阵数乘
	void MatrixMulNum(double num, double *A, double *B, int M, int N);
	//矩阵转置
	void MatrixTranspose(double *A, double *B, int M, int N);

	// 矩阵求违逆
	void MatrixGinv(int M,int N,double* A, double* B);


};

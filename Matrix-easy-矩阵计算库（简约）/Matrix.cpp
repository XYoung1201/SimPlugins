#include "StdAfx.h"
#include "Matrix.h"
#define ZERO 1.0E-30


CMatrix::CMatrix(void)
{

}

CMatrix::~CMatrix(void)
{
	//int i;
	//for(i=0;i<m;i++) {delete[] ia[i];}
	//delete []ia;
	//for(i=0;i<m;i++) {delete[] u[i];}
	//delete []u;
	//for(i=0;i<n;i++) {delete[] v[i];}
	//delete []v;
	//for(i=0;i<n;i++) {delete[] aa[i];}
	//delete []aa;
	//delete[]s,e,w;

}

void CMatrix::GetMatrix(double *A, int M, int N)
{
	int k;
	PM = M; 
	PN = N;
	for(k=0;k<PM;k++)
	{
		PA[k]=A+k*PN;
	}
}

double CMatrix::GetMainElement(int k)
{
	int i,j,FLAG;
	double temp,MEAV;
	FLAG = k;
	MEAV = fabs(PA[k][k]);
	for(i=k+1;i<PM;i++)
	{
		temp =fabs(PA[i][k]);
		if(temp<=MEAV)
		{
			continue;
		}
		FLAG = i;
		MEAV = temp;
	}
	for(j=0;j<PN;j++)
	{
		temp = PA[k][j];
		PA[k][j]=PA[FLAG][j];
		PA[FLAG][j] = temp;
	}
	return MEAV;
}

int CMatrix::Jordan_G()
{
	int i,j,k;
	double x,test=0;
	for(k=0;k<PM;k++)
	{
		test = GetMainElement(k);
		if(test<ZERO)
		{
			return -11;
		}
		x=PA[k][k];
		for(j=k;j<PN;j++)
		{
			PA[k][j]=PA[k][j]/x;
		}
		for(i=0;i<PM;i++)
		{
			if(i==k)
			{
				continue;
			}
			x=PA[i][k];
			for(j=k;j<PN;j++)
			{
				PA[i][j]=PA[i][j]-x*PA[k][j];
			}
		}
	}
	return 0;
}

int CMatrix::MatrixInversion(double *A,double *B, int n)//B=inv(A)
{
	int i,j,k,ErrCode=0;

	if(n>25)
	{
		return -1;
	}

	PM=n; PN=PM*2;

	PBUF=(double*)malloc(PM*PN*sizeof(double));

	if(!PBUF)
	{
		return -2;
	}
	for(k=0;k<PM;k++)
	{
		PW[k]=A+k*PM;
		PA[k]=PBUF+k*PN;
	}
	for(i=0;i<PM;i++)
	{
		for(j=0;j<PM;j++)
		{
			PA[i][j]=PW[i][j];
			PA[i][j+PM]=0.0;
		}
		PA[i][i+PM]=1.0;
	}
	ErrCode = Jordan_G();
	for(i=0;i<PM;i++)
	{
		PW[i]=B+i*PM;
		for(j=0;j<PM;j++)
		{
			PW[i][j]=PA[i][j+PM];
		}
	}
	free(PBUF);
	return ErrCode;
}

double CMatrix::Determinant(double *A, int n)
{
	int i,j,k;
	PBUF = (double*)malloc(n*n*sizeof(double));
	if(PBUF==NULL)
	{
		return -1;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			PBUF[i*n+j]=A[i*n+j];
		}
	}
	GetMatrix(PBUF, n, n);

	double  temp,MEAV;
	int iSign, jSign;

	double det = 1.0;
	int	nSgn = 1;

	for(k=0;k<PM-1;k++)
	{	
		MEAV = 0.0;
		for(i=k;i<PM;i++)//PM=PN
		{
			for(j=k;j<PM;j++)
			{
				temp = fabs(PA[i][j]);
				if(temp > MEAV)
				{
					MEAV = temp;
					iSign = i;
					jSign = j;
				}
			}
		}

		if(MEAV<ZERO)
			return 0.0;

		if(iSign != k)
		{
			nSgn = -nSgn;
			for(j=k;j<PM;j++)
			{
				temp = PA[iSign][j];
				PA[iSign][j] = PA[k][j];
				PA[k][j] = temp;
			}
		}
		if(jSign != k)
		{
			nSgn = -nSgn;
			for(i = k; i < PM; i ++)
			{
				temp = PA[i][jSign];
				PA[i][jSign] = PA[i][k];
				PA[i][k] = temp;
			}
		}

		det = det*PA[k][k];
		for(i = k + 1; i < PM; i ++)
		{
			temp = PA[i][k]/ PA[k][k];
			for(j = k + 1; j < PM; j ++)
			{
				PA[i][j] =PA[i][j]- temp * PA[k][j];
			}
		}
	}
	det = nSgn*det*PA[PM-1][PM-1];
	free(PBUF);
	return det;
}

void CMatrix::MatrixAdd(double *A, double *B, double *C, int PM, int PN)//C=A+B
{
	int i,j;
	for(i=0;i<PM;i++)
	{
		PA[i]=A+i*PN;
		PW[i]=B+i*PN;
	}
	for(i=0;i<PM;i++)
	{
		for(j=0;j<PN;j++)
		{
			C[i*PN+j] = PA[i][j]+PW[i][j];
		}
	}
}

void CMatrix::MatrixMus(double *A, double *B, double *C, int PM, int PN)//C=A-B
{	
	int i,j;
	for(i=0;i<PM;i++)
	{
		PA[i]=A+i*PN;
		PW[i]=B+i*PN;
	}
	for(i=0;i<PM;i++)
	{
		for(j=0;j<PN;j++)
		{
			C[i*PN+j]=PA[i][j]-PW[i][j];
		}
	}
}

void CMatrix::MatrixMul(double *A, double *B, double *C, int PM, int PN, int PQ)//C=A*B
{
	int i,j,k;
	
	for(i=0;i<PM;i++)
	{
		PA[i]=A+i*PN;
	}
	for(i=0;i<PN;i++)
	{
		PW[i]=B+i*PQ;
	}
	for(i=0;i<PM;i++)
	{
		for(j=0;j<PQ;j++)
		{
			C[i*PQ+j]=0.0;//clear C,require independent memory
			for(k=0;k<PN;k++)
			{
				C[i*PQ+j] += PA[i][k]*PW[k][j];
			}
		}
	}
}

void CMatrix::MatrixMulNum(double num, double *A, double *B, int M, int N)//B=num*A
{
	GetMatrix(A, M, N);
	int i,j;
	for(i=0;i<PM;i++)
	{
		for(j=0;j<PN;j++)
		{
			B[i*PN+j]=num*PA[i][j];
		}
	}

}

void CMatrix::MatrixTranspose(double *A, double *B, int M, int N)//B=A`
{
	GetMatrix(A, M, N);
	int i,j;
	for(i=0;i<PM;i++)
	{
		for(j=0;j<PN;j++)
		{
			B[j*PM+i] = PA[i][j];
		}
	}
}

void CMatrix::GInv_initial(int mm, int nn)
{
	eps=0.000001;
	int i;
	m=mm;n=nn;
	ia=new double *[m];
	for(i=0;i<m;i++) ia[i]=new double [n];
	u=new double *[m];
	for(i=0;i<m;i++) u[i]=new double [m];
	v = new double *[n];
	for(i=0;i<n;i++) v[i]=new double [n];
	aa = new double *[n];
	for(i=0;i<n;i++) aa[i]=new double [m];
	ka=m+1;
	if(m<n) ka=n+1;
	s=new double[ka];
	e=new double[ka];
	w=new double[ka];
}

void CMatrix::GInv_input(double* A, int M, int N)
{
	int i,j;
	for (i=0; i<M; i++)
	{
		for (j=0; j<N; j++)
		{
			ia[i][j] = *(A+i*N+j);
		}
	}
	//double c[3][5];   ///用来监视输入矩阵
	//for (int i=0; i<M; i++)
	//{
	//	for (int j=0; j<N; j++)
	//	{
	//		c[i][j] = a[i][j];
	//	}
	//}
	for(i=0;i<m;i++)
		for(j=0;j<m;j++) u[i][j]=0;

	for(i=0;i<n;i++)
		for(j=0;j<n;j++) v[i][j]=0;
}


void CMatrix::GInv_uav()///对矩阵a奇异值分解，u左奇异向量mxm，v右奇异向量v~nxn
{

	int i,j,k,l,it,ll,kk,mm,nn,m1,ks;
	double d,dd,t,sm,sm1,em1,sk,ek,b,c,shh;
	it=60;k=n;
	if (m-1<n) k= m-1;
	l=m;
	if (n-2<m) l=n-2;
	if(l<0) l=0;
	ll=k;
	if(l>k) ll=l;
	if(ll>=1)
	{
		for(kk=1;kk<=ll;kk++)
		{
			if(kk<=k)
			{
				d=0.0;
				for (i=kk;i<=m;i++)
					d=d+ia[i-1][kk-1]*ia[i-1][kk-1];
				s[kk-1] = sqrt(d);
				if (s[kk-1]!=0.0)
				{
					if(ia[kk-1][kk-1]!=0.0)
					{
						s[kk-1]=fabs(s[kk-1]);
						if(ia[kk-1][kk-1]<0.0) s[kk-1]=-s[kk-1];
					}
					for(i=kk;i<=m;i++)
					{
						ia[i-1][kk-1]=ia[i-1][kk-1]/s[kk-1];
					}
					ia[kk-1][kk-1]=1.0+ia[kk-1][kk-1];
				}
				s[kk-1]=-s[kk-1];
			}
			if(n>=kk+1)
			{
				for (j=kk+1;j<=n;j++)
				{
					if((kk<=k)&&(s[kk-1]!=0.0))
					{
						d=0.0;
						for(i=kk;i<=m;i++)
						{
							d=d+ia[i-1][kk-1]*ia[i-1][j-1];
						}
						d=-d/ia[kk-1][kk-1];
						for(i=kk;i<=m;i++)
						{
							ia[i-1][j-1]=ia[i-1][j-1]+d*ia[i-1][kk-1];
						}
					}
					e[j-1]=ia[kk-1][j-1];
				}
			}
			if(kk<=k)
			{
				for(i=kk;i<=m;i++)
				{
					u[i-1][kk-1]=ia[i-1][kk-1];
				}
			}
			if(kk<=l)
			{
				d=0.0;
				for(i=kk+1;i<=n;i++)
					d=d+e[i-1]*e[i-1];
				e[kk-1]=sqrt(d);
				if(e[kk-1]!=0.0)
				{
					if(e[kk]!=0.0)
					{
						e[kk-1]=fabs(e[kk-1]);
						if (e[kk]<0.0) e[kk-1]=-e[kk-1];
					}
					for(i=kk+1;i<=n;i++)
						e[i-1]=e[i-1]/e[kk-1];
					e[kk]=1.0+e[kk];
				}
				e[kk-1]=-e[kk-1];
				if((kk+1<=m)&&(e[kk-1]!=0.0))
				{
					for(i=kk+1;i<=m;i++) w[i-1]=0.0;
					for(j=kk+1;j<=n;j++)
						for(i=kk+1;i<=m;i++)
							w[i-1]=w[i-1]+e[j-1]*ia[i-1][j-1];
					for(j=kk+1;j<=n;j++)
						for(i=kk+1;i<=m;i++)
						{
							ia[i-1][j-1]=ia[i-1][j-1]-w[i-1]*e[j-1]/e[kk];
						}
				}
				for(i=kk+1;i<=n;i++)
					v[i-1][kk-1]=e[i-1];
			}
		}
	}
	mm=n;
	if(m+1<n) mm=m+1;
	if(k<n) s[k]=ia[k][k];
	if(m<mm) s[mm-1]=0.0;
	if(l+1<mm) e[l]=ia[l][mm-1];
	e[mm-1]=0.0;
	nn=m;
	if(m>n) nn=n;
	if(nn>=k+1)
	{
		for(j=k+1;j<=nn;j++)
		{
			for (i=1;i<=m;i++) u[i-1][j-1]=0.0;
			u[j-1][j-1]=1.0;

		}
	}
	if(k>=1)
	{
		for(ll=1;ll<=k;ll++)
		{
			kk=k-ll+1;
			if(s[kk-1]!=0.0)
			{
				if(nn>=kk+1)
					for(j=kk+1;j<=nn;j++)
					{
						d=0.0;
						for(i=kk;i<=m;i++)
						{
							d=d+u[i-1][kk-1]*u[i-1][j-1]/u[kk-1][kk-1];
						}
						d=-d;
						for (i=kk;i<=m;i++)
						{
							u[i-1][j-1]=u[i-1][j-1]+d*u[i-1][kk-1];
						}
					}
					for(i=kk;i<=m;i++)
						u[i-1][kk-1]=-u[i-1][kk-1];
					u[kk-1][kk-1]=1.0+u[kk-1][kk-1];
					if(kk-1>=1)
						for(i=1;i<=kk-1;i++) u[i-1][kk-1]=0.0;
			}
			else
			{
				for(i=1;i<=m;i++) u[i-1][kk-1]=0.0;
				u[kk-1][kk-1]=1.0;
			}
		}
	}
	for(ll=1;ll<=n;ll++)
	{
		kk=n-ll+1;
		if((kk<=l)&&(e[kk-1]!=0.0))
		{
			for(j=kk+1;j<=n;j++)
			{
				d=0.0;
				for(i=kk+1;i<=n;i++)
				{
					d=d+v[i-1][kk-1]*v[i-1][j-1]/v[kk][kk-1];
				}
				d=-d;
				for(i=kk+1;i<=n;i++)
				{
					v[i-1][j-1]=v[i-1][j-1]+d*v[i-1][kk-1];
				}
			}
		}
		for (i=1;i<=n;i++) v[i-1][kk-1]=0.0;
		v[kk-1][kk-1]=1.0;
	}
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++) ia[i-1][j-1]=0.0;
	m1=mm;it=60;
	////////////////////////////////////////////////////////////
	while(1==1)
	{
		if(mm==0)
		{
			GInv_ppp();
			return;
		}
		if(it==0)
		{
			GInv_ppp();
		}
		kk=mm-1;
		while((kk!=0)&&(fabs(e[kk-1])!=0.0))
		{
			d=fabs(s[kk-1])+fabs(s[kk]);
			dd=fabs(e[kk-1]);
			if(dd>eps*d) kk=kk-1;
			else e[kk-1]=0.0;
		}
		if(kk==mm-1)
		{
			kk=kk+1;
			if(s[kk-1]<0.0)
			{
				s[kk-1]=-s[kk-1];
				for(i=1;i<=n;i++)
					v[i-1][kk-1]=-v[i-1][kk-1];
			}
			while((kk!=m1)&&(s[kk-1]<s[kk]))
			{
				d=s[kk-1];s[kk-1]=s[kk];s[kk]=d;
				if(kk<n)
					for(i=1;i<=n;i++)
					{
						d=v[i-1][kk-1];
						v[i-1][kk-1]=v[i-1][kk];
						v[i-1][kk]=d;
					}
					if(kk<m)
						for(i=1;i<=m;i++)
						{
							d=u[i-1][kk-1];
							u[i-1][kk-1]=u[i-1][kk];
							u[i-1][kk]=d;
						}
						kk=kk+1;
			}
			it=60;
			mm=mm-1;

		}
		else
		{
			ks=mm;
			while((ks>kk)&&(fabs(s[ks-1])!=0.0))
			{
				d=0.0;
				if(ks!=mm) d=d+fabs(e[ks-1]);
				if(ks!=kk+1) d=d+fabs(e[ks-2]);
				dd=fabs(s[ks-1]);
				if(dd>eps*d) ks=ks-1;
				else s[ks-1]=0.0;
			}
			if(ks==kk)
			{
				kk=kk+1;
				d=fabs(s[mm-1]);
				t=fabs(s[mm-2]);
				if(t>d) d=t;
				t=fabs(e[mm-2]);
				if(t>d) d=t;
				t=fabs(s[kk-1]);
				if(t>d) d=t;
				t=fabs(e[kk-1]);
				if(t>d) d=t;
				sm=s[mm-1]/d; sm1=s[mm-2]/d;
				em1=e[mm-2]/d;
				sk=s[kk-1]/d; ek =e[kk-1]/d;
				b=((sm1+sm)*(sm1-sm)+em1*em1)/2.0;
				c=sm*em1;c=c*c;shh=0.0;
				if((b!=0.0)||(c!=0.0))
				{
					shh=sqrt(b*b+c);
					if(b<0.0) shh=-shh;
					shh=c/(b+shh);
				}
				fg[0]=(sk+sm)*(sk-sm)-shh;
				fg[1]=sk*ek;
				for(i=kk;i<=mm-1;i++)
				{
					GInv_sss();
					if(i!=kk) e[i-2]=fg[0];
					fg[0]=cs[0]*s[i-1]+cs[1]*e[i-1];
					e[i-1]=cs[0]*e[i-1]-cs[1]*s[i-1];
					fg[1]=cs[1]*s[i];
					s[i]=cs[0]*s[i];
					if((cs[0]!=1.0)||(cs[1]!=0.0))
						for(j=1;j<=n;j++)
						{
							d=cs[0]*v[j-1][i-1]+cs[1]*v[j-1][i];
							v[j-1][i]=-cs[1]*v[j-1][i-1]+cs[0]*v[j-1][i];
							v[j-1][i-1]=d;
						}
						GInv_sss();
						s[i-1]=fg[0];
						fg[0]=cs[0]*e[i-1]+cs[1]*s[i];
						s[i]=-cs[1]*e[i-1]+cs[0]*s[i];
						fg[1]=cs[1]*e[i];
						e[i]=cs[0]*e[i];
						if(i<m)
							if((cs[0]!=1.0)||(cs[1]!=0.0))
								for(j=1;j<=m;j++)
								{
									d=cs[0]*u[j-1][i-1]+cs[1]*u[j-1][i];
									u[j-1][i]=-cs[1]*u[j-1][i-1]+cs[0]*u[j-1][i];
									u[j-1][i-1]=d;
								}
				}
				e[mm-2]=fg[0];
				it=it-1;

			}
			else
			{
				if(ks==mm)
				{
					kk=kk+1;
					fg[1]=e[mm-2];e[mm-2]=0.0;
					for(ll=kk;ll<=mm-1;ll++)
					{
						i=mm+kk-ll-1;
						fg[0]=s[i-1];
						GInv_sss();
						s[i-1]=fg[0];
						if(i!=kk)
						{
							fg[1]=-cs[1]*e[i-2];
							e[i-2]=cs[0]*e[i-2];
						}
						if((cs[0]!=1.0)||(cs[1]!=0.0))
							for(j=1;j<=n;j++)
							{
								d=cs[0]*v[j-1][i-1]+cs[1]*v[j-1][mm-1];
								v[j-1][mm-1]=-cs[1]*v[j-1][i-1]+cs[0]*v[j-1][mm-1];
								v[j-1][i-1]=d;
							}
					}
				}
				else
				{
					kk=ks+1;
					fg[1]=e[kk-2];
					e[kk-2]=0.0;
					for(i=kk;i<=mm;i++)
					{
						fg[0]=s[i-1];
						GInv_sss();
						s[i-1]=fg[0];
						fg[1]=-cs[1]*e[i-1];
						e[i-1]=cs[0]*e[i-1];
						if((cs[0]!=1.0)||(cs[1]!=0.0))
							for(j=1;j<=m;j++)
							{
								d=cs[0]*u[j-1][i-1]+cs[1]*u[j-1][kk-2];
								u[j-1][kk-2]=-cs[1]*u[j-1][i-1]+cs[0]*u[j-1][kk-2];
								u[j-1][i-1]=d;

							}
					}
				}
			}
		}
	}
}
void CMatrix::GInv_ppp()
{
	int i,j;
	double d;
	if(m>=n) i=n;
	else i=m;
	for(j=1;j<=i-1;j++)
	{
		ia[j-1][j-1]=s[j-1];
		ia[j-1][j]=e[j-1];
	}
	ia[i-1][i-1]=s[i-1];
	if(m<n) ia[i-1][i]=e[i-1];
	for(i=1;i<=n-1;i++)
		for(j=i+1;j<=n;j++)
		{
			d=v[i-1][j-1];
			v[i-1][j-1]=v[j-1][i-1];
			v[j-1][i-1]=d;
		}

}
void CMatrix::GInv_sss()
{
	double r,d;
	if((fabs(fg[0]))+(fabs(fg[1]))==0.0)
	{
		cs[0]=1.0;cs[1]=0.0;d=0.0;
	}
	else
	{
		d=sqrt(fg[0]*fg[0]+fg[1]*fg[1]);
		if (fabs(fg[0])>fabs(fg[1]))
		{
			d=fabs(d);
			if(fg[0]<0.0) d=-d;
		}
		if (fabs(fg[1])>=fabs(fg[0]))
		{
			d=fabs(d);
			if(fg[1]<0.0) d=-d;
		}
		cs[0]=fg[0]/d;cs[1]=fg[1]/d;
	}
	r=1.0;
	if(fabs(fg[0])>fabs(fg[1])) r=cs[1];
	else
		if(cs[0]!=0.0) r=1.0/cs[0];
	fg[0]=d;fg[1]=r;
}
void CMatrix::GInv_Math()
{
	int i,j,k,l;
	GInv_uav();
	j=n;
	if(m<n) j=m;
	j=j-1;
	k=0;
	while((k<=j)&&(ia[k][k]!=0.0)) k=k+1;
	k=k-1;
	for(i=0;i<=n-1;i++)
		for(j=0;j<=m-1;j++)
		{
			aa[i][j]=0.0;
			for(l=0;l<=k;l++)
			{
				aa[i][j]=aa[i][j]+v[l][i]*u[j][l]/ia[l][l];
			}
		}
}

void CMatrix::GInv_output(double* AA, int N, int M)
{
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<M; j++)
		{
			*(AA+i*M+j)= aa[i][j] ;
		}
	}

}

void CMatrix::MatrixGinv(int M,int N,double* A, double* B)
{

	GInv_initial(M,N);
	GInv_input(A,M,N);
	GInv_Math( );
	GInv_output(B,N,M);

	int i;
	for(i=0;i<m;i++) {delete[] ia[i];}
	delete []ia;
	for(i=0;i<m;i++) {delete[] u[i];}
	delete []u;
	for(i=0;i<n;i++) {delete[] v[i];}
	delete []v;
	for(i=0;i<n;i++) {delete[] aa[i];}
	delete []aa;
	delete[]s;
	delete []e;
	delete []w;
}
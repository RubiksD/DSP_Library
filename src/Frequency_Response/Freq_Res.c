#include <math.h>
#include "Freq_Res.h"

void	FIR_Freq_Res_mag(double *num,int N,int points,double *response)
{
	double w;
	int i,j;
	double complex Z;
	for(w=0,j=0;w< 2*PI; w= w+(2*PI/points)){
		Z = 0;
		for(i=0;i<N;i++){
			Z += (num[i]*cexp(-I*w*(N-i-1)));
		}
		response[j++] = cabs(Z);

	}
}

void	FIR_Freq_Res_phase(double *num,int N,int points,double *response)
{
	double w;
	int i,j;
	double complex Z;
	for(w=0,j=0;w< 2*PI; w= w+(2*PI/points)){
		Z = 0;
		for(i=0;i<N;i++){
			Z += (num[i]*cexp(-I*w*(N-i-1)));
		}
		response[j++] = atan(cimag(Z)/creal(Z));

	}
}

void	IIR_Freq_Res_mag(double *num,double *den,int N,int points,double *response)
{
	double response_num[points];
	double response_den[points];
	FIR_Freq_Res_mag(num,N,points,response_num);
	FIR_Freq_Res_mag(den,N,points,response_den);
	int i;
	for (i=0;i<points;i++){
		response[i]= response_num[i]/response_den[i];
	}
}

void	IIR_Freq_Res_phase(double *num,double *den,int N,int points,double *response)
{
	double response_num[points];
	double response_den[points];
	FIR_Freq_Res_phase(num,N,points,response_num);
	FIR_Freq_Res_phase(den,N,points,response_den);
	int i;
	for (i=0;i<points;i++){
		response[i]= response_num[i]-response_den[i];
	}
}
#include <stdio.h>
void CT_Freq_Res_mag(double *num,double *den,int N,int points,double *response,double Wmax)
{
	double complex response_num[points];
	double complex response_den[points];
	double w;
	int i,j;
	double complex S;
	for(w=0,j=0;w< Wmax; w= w+(Wmax/points)){
		S = 1;
		response_num[j] = 0;
		response_den[j] = 0;
		for(i=N-1;i>=0;i--){
			response_num[j] += (num[i]*S);
			response_den[j] += (den[i]*S);
			S *= I*w;
		}
		response[j] = cabs(response_num[j]/response_den[j]);
		j++;

	}
}

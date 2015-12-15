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
void CT_Freq_Res_mag(double *num,double *den,int N,int points,double *response,double fmax)
{
	double response_num[points];
	double response_den[points];
	double w;
	int i,j;
	double complex S;
	for(i=0;i<N;i++){
		printf("%lf\n",num[i]);
	}
	for(i=0;i<N;i++){
		printf("%lf\n",den[i]);
	}
	for(w=0,j=0;w< 2*PI*fmax; w= w+((2*PI*fmax)/points)){
		S = 1;
		for(i=0;i<N;i++){
			 response_num[j] += (num[N-1-i]*S);
			 response_den[j] += (den[N-1-i]*S);
			 
		printf("num=%lf\n",num[N-1-i]);
		printf("den=%lf\n",den[N-1-i]);
		printf("%lf\t%lf\t%lf\n",num[N-1-i],creal(response_num[j]),cimag(response_num[j]));
		printf("%lf\t%lf\t%lf\n",den[N-1-i],creal(response_den[j]),cimag(response_den[j]));
			S *= I*w;
		}
		response[j] = cabs(response_num[j]/response_den[j]);
		printf("Res = %lf\t%lf\t%lf\t%lf\n",w,cabs(response_den[j]),cabs(response_num[j]),response[j]);
		j++;

	}
}

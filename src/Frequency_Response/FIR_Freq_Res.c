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
			Z += (num[i]*cexp(-I*w*i));
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
			Z += (num[i]*cexp(-I*w*i));
		}
		response[j++] = atan(cimag(Z)/creal(Z));

	}
}


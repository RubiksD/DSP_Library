#include <math.h>
#include "Freq_Res.h"

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




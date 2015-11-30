#include <math.h>
#include "FIR_Freq_Res.h"

void	IIR_Freq_Res(double *num,double *den,int N,int points,double *response)
{
	double response_num[points];
	double response_den[points];
	FIR_Freq_Res(num,N,points,response_num);
	FIR_Freq_Res(den,N,points,response_den);
	int i;
	for (i=0;i<points;i++){
		response[i]= response_num[i]/response_den[i];
	}
}



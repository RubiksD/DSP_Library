#include <math.h>
#include "FIR_Freq_Res.h"

void	FIR_Freq_Res(int *num,int N,int points,double *response)
{
	double w;
	int i,j;
	double complex Z;
	for(w=0,j=0;w< 2*PI; w= w+(2*PI/points)){
		Z = 0;
		for(i=0;i<N;i++){
			Z += cexp(-I*w*i);
		}
		response[j++] = cabs(Z);

	}
}



#include <math.h>
#include <complex.h>
#include "Butterworth_Filter.h"


void Butterworth_Filter(int N, double complex coeff[])
{
	int i;
	for(i=1;i<=N;i++){
		coeff[i-1]=cexp(I*M_PI*(N+(2*i)-1)/(2*N));
	}
}

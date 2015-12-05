#include <math.h>
#include <complex.h>
#include "Butterworth_Filter.h"
#include "Filter_Dsg.h"

int Get_Butterworth_Order(LP_Filter_Spac_t Filter_g)
{
	

}

void Butterworth_Filter(int N, double complex coeff[])
{
	int i;
	for(i=1;i<=N;i++){
		coeff[i-1]=cexp(I*M_PI*(N+(2*i)-1)/(2*N));
	}
}

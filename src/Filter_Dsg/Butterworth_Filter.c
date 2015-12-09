#include <math.h>
#include <complex.h>
#include "Butterworth_Filter.h"

int Get_Butterworth_Order(LP_Filter_Spec_t *Filter_p)
{
	double Order;
	
	Order = (log10(1/(Filter_p->discrimination_parameter))/log10(1/(Filter_p->selectivity_parameter)));
	Filter_p->Order = (Order - ((int)Order))?(((int)(Order))+1):(int)Order;
	return Filter_p->Order;
}

void Butterworth_Filter(int N, double complex coeff[])
{
	int i;
	for(i=1;i<=N;i++){
		coeff[i-1]=cexp(I*M_PI*(N+(2*i)-1)/(2*N));
	}
}

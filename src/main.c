#include <stdio.h>
#include <math.h>
#include "FIR_Freq_Res.h"

int main()
{
	double num[]={0.0088,0.0263,0.0263,0.0088,1,1,1,1};
	double den[]={1,-2.2343,1.8758,-0.5713,1,1,1,1};
	int N=4;
	int points=1000;

	double response[points];

	IIR_Freq_Res(num,den,N,points,response);

	double w=0;
	int i;
	for(i=0;i<points;i++){
		printf("%lf\t%lf\n",w,20*log10(response[i]));
		w= w+(64000.0/points);
	}
	return 0;
}

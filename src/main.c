#include <stdio.h>
#include <math.h>
#include "Freq_Res.h"

int main()
{
	double num[]={1,1,1,1,1,1,1,1};
//	double num[]={0.0088,0.0263,0.0263,0.0088,1,1,1,1};
//	double den[]={1,-2.2343,1.8758,-0.5713,1,1,1,1};
	int N=8;
	int points=1000;

	double response[points];
	double response1[points];

	FIR_Freq_Res_phase(num,N,points,response);
	FIR_Freq_Res_mag(num,N,points,response1);

	double w=0;
	int i;
	for(i=0;i<points;i++){
		printf("%lf\t%lf\t%lf\n",w,response[i],20*log10(response1[i]));
		w= w+(64000.0/points);
	}
	return 0;
}

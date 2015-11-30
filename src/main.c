#include <stdio.h>
#include <math.h>
#include "FIR_Freq_Res.h"

int main()
{
	int num[]={1,1,1,1,1,1,1,1};
	int N=4;
	int points=1000;

	double response[points];

	FIR_Freq_Res(num,N,points,response);

	double w=0;
	int i;
	for(i=0;i<points;i++){
		printf("%lf\t%lf\n",w,20*log10(response[i]));
		w= w+(64000.0/points);
	}
	return 0;
}

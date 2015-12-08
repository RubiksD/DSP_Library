#include <stdio.h>
#include <math.h>
#include "Freq_Res.h"
#include "Filter_Dsg.h"
#include "Butterworth_Filter.h"

#if 0
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
#endif

int main()
{
	LP_Filter_Spec_t Butterworth_Filter;
	Butterworth_Filter.omega_pass_ana =4000;
	Butterworth_Filter.omega_stop_ana =40000;
	Butterworth_Filter.F_sampl = 12000;
	Butterworth_Filter.ripple_pass = 0.00115;
	Butterworth_Filter.ripple_stop = 0.0003162;
	Estimate_LP_params_from_ripple(&Butterworth_Filter);
	printf("%lf \t %lf",Butterworth_Filter.ripple_pass_db,Butterworth_Filter.ripple_stop_db);
	Get_Butterworth_Order(&Butterworth_Filter);
	return 0;
}

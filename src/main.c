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
	double complex Butterworth_roots[10];
#if 0
	Butterworth_Filter.omega_pass =2*M_PI*1000;
	Butterworth_Filter.omega_stop =2*M_PI*5000;
	Butterworth_Filter.F_sampl = 12000;
	Butterworth_Filter.ripple_pass_db = 1;
	Butterworth_Filter.ripple_stop_db = 40;
	Butterworth_Filter.ripple_pass = 0.00115;
	Butterworth_Filter.ripple_stop = 0.0003162;
#else
	Butterworth_Filter.omega_pass =1;
	Butterworth_Filter.omega_stop =10;
	Butterworth_Filter.F_sampl = 12000;
	Butterworth_Filter.ripple_pass_db = 3;
	Butterworth_Filter.ripple_stop_db = 45;
#endif
	Estimate_LP_params_from_ripple_db(&Butterworth_Filter);
	printf("%lf\t%lf\n",Butterworth_Filter.discrimination_parameter,Butterworth_Filter.selectivity_parameter);
	printf("%lf \t %lf\n",Butterworth_Filter.eps*Butterworth_Filter.eps,Butterworth_Filter.A);
	int N=Get_Butterworth_Order(&Butterworth_Filter);
	
	printf("N = %d\n",N);

	Butterworth_Filter_roots(&Butterworth_Filter,Butterworth_roots);

	int i;
	for(i=0;i<N;i++){
		printf("%lf\t%lf\n",creal(Butterworth_roots[i]),cimag(Butterworth_roots[i]));
	}

	double den[10];
	ZP2NumDen(Butterworth_roots,N,Butterworth_roots,N,den,den);
	for(i=0;i<=N;i++){
		if(i!=N){
			printf("s^%d %lf ",N-i,den[i]);
			printf("+ ");
		}else{
			printf("%lf \n",den[i]);
		}
	}
#if 0
	double num[10]={0,0,0,1,0,0,0,0,0,0};
	int points = 1024;
	double response[points];
	IIR_Freq_Res_mag(num,den,N+1,points,response);
	double w=0;
	for(i=0;i<points;i++){
		printf("%lf\t%lf\t%lf\n",w,response[i],20*log10(response[i]));
		w= w+(64000.0/points);
	}
#endif
	return 0;
}

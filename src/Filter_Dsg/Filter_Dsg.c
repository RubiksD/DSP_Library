#include <math.h>
#include "Filter_Dsg.h"

void Estimate_LP_params_from_ripple(LP_Filter_Spec_t *Filter_p)
{
	Filter_p->omega_pass_d = (Filter_p->omega_pass)/Filter_p->F_sampl;
	Filter_p->omega_stop_d = (Filter_p->omega_stop)/Filter_p->F_sampl;
	Filter_p->ripple_pass_db = -20*log10(1-Filter_p->ripple_pass);
	Filter_p->ripple_stop_db = -20*log10(Filter_p->ripple_stop);
	Filter_p->eps = sqrt((1/((1-(2*Filter_p->ripple_pass))*(1-(2*Filter_p->ripple_pass))))-1);
	Filter_p->A		= 1/Filter_p->ripple_stop;
	Filter_p->selectivity_parameter = Filter_p->omega_pass/Filter_p->omega_stop;
	Filter_p->discrimination_parameter	= Filter_p->eps/(sqrt((Filter_p->A*Filter_p->A)-1));

}

void Estimate_LP_params_from_ripple_db(LP_Filter_Spec_t *Filter_p)
{
	Filter_p->omega_pass_d = (Filter_p->omega_pass)/Filter_p->F_sampl;
	Filter_p->omega_stop_d = (Filter_p->omega_stop)/Filter_p->F_sampl;
	Filter_p->ripple_pass = 1-pow(10,-Filter_p->ripple_pass_db/20);
	Filter_p->ripple_stop = pow(10,-Filter_p->ripple_stop_db/20);
	Filter_p->eps = sqrt((1/(pow(10,-Filter_p->ripple_pass_db/10)))-1);
	Filter_p->A		= 1/Filter_p->ripple_stop;
	Filter_p->selectivity_parameter = Filter_p->omega_pass_d/Filter_p->omega_stop_d;
	Filter_p->discrimination_parameter	= Filter_p->eps/(sqrt((Filter_p->A*Filter_p->A)-1));

}

void ZP2NumDen(
	double complex *Zeros,
	int N_Z, 
	double complex *Poles,
	int N_P,
	double K,
	double *Num, 
	double *Den
								)
{
	double complex temp1_Num[N_P], temp2_Num[N_P];
	double complex *temp1,*temp2;
	int i,j;
	for(i=0;i<N_P;i++){
		if(i==0){
			temp1_Num[0]=1;
			temp1_Num[1]=-Poles[0];
		}else{
			if((i%2)==0){
				temp1=temp2_Num;
				temp2=temp1_Num;
			}else{
				temp2=temp2_Num;
				temp1=temp1_Num;
			}
			for(j=0;j<=(i+1);j++){
				if(j==0){
					temp2[0] = temp1[0]*1;
				}else if(j==(i+1)){
					temp2[j]= -(temp1[j-1]*Poles[i]);
				}else{
					temp2[j]= (temp1[j]*1)-(temp1[j-1]*Poles[i]);
				}
			}
		}

	}
	for(i=0;i<=N_P;i++){
		if((N_P%2)==0){
			temp1=temp2_Num;
		}else{
			temp1=temp1_Num;
		}
		Den[i]=creal(temp1[i]);
	}

	for(i=0;i<N_Z;i++){
		if(i==0){
			temp1_Num[0]=1;
			temp1_Num[1]=-Zeros[0];
		}else{
			if((i%2)==0){
				temp1=temp2_Num;
				temp2=temp1_Num;
			}else{
				temp2=temp2_Num;
				temp1=temp1_Num;
			}
			for(j=0;j<=(i+1);j++){
				if(j==0){
					temp2[0] = temp1[0]*1;
				}else if(j==(i+1)){
					temp2[j]= -(temp1[j-1]*Zeros[i]);
				}else{
					temp2[j]= (temp1[j]*1)-(temp1[j-1]*Zeros[i]);
				}
			}
		}

	}
	for(i=0;i<=N_Z;i++){
		if((N_Z%2)==0){
			temp1=temp2_Num;
		}else{
			temp1=temp1_Num;
		}
		Num[i]=K*creal(temp1[i]);
	}
}

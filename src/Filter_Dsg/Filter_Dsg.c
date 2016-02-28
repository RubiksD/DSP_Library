/*
File: Filter_Dsg.c

This file contains funtions for designing a filter

*/
#include <math.h>
#include <stdio.h>
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

void IdealFilter()
{
	int i,j;
	int N;
	int NumOfPts;
	int scan_temp;

	double W[1024];
	double M[1024];

	double w[1024];
	double m[1024];

	FILE *fp;

	fp = fopen("IdealMagRes.txt","w");

	printf("Enter the filter frequency response in terms of peicewise continuous points\n");
	do{
		printf("Enter number of points < 1024:");
		scan_temp = scanf("%d",&N);
	}while((N >= 1024 ) && (N < 0));
	
	printf("Enter magnitude at F=0\n");
	W[0] = 0;
	scan_temp = scanf("%lf",&M[0]);
	for(i=1;i<N-1;i++){
		printf("Enter digital frequency F 0 < F/pi < 1 \n");
		scan_temp = scanf("%lf",&W[i]);
		W[i] = W[i] * M_PI;
		printf("Enter magnitude\n");
		scan_temp = scanf("%lf",&M[i]);
	}
	printf("Enter magnitude at Pi\n");
	scan_temp = scanf("%lf",&M[i]);

	printf("Writing ideal frequency response into file IdealMagRes.txt\n");
	printf("Enter number of points of response:");
	scan_temp = scanf("%d",&NumOfPts);
	for(i=0,j=1;i<NumOfPts;i++){
		w[i] = i*(M_PI/NumOfPts);
		while(w[i] > W[j]){
			j++;
		}
		m[i] = M[j-1] + ((M[j-1]-M[j])*((w[i]-W[j-1])/(W[j-1]-W[j])) );
		fprintf(fp,"%lf\t%lf\n",w[i],m[i]);
	}
	for(i=0;i<NumOfPts;i++){
		fprintf(fp,"%lf\t%lf\n",(2*M_PI)-w[NumOfPts-i-1],m[NumOfPts-i-1]);
	}
	fclose(fp);
}

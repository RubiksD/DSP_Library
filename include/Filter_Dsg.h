// Generalized filter spec structure
#ifndef FILTER_DSG_H
#define FILTER_DSG_H

typedef struct LP_Filter_Spec_s{
	double omega_pass_ana;
	double omega_stop_ana;
	double F_sampl;
	double omega_pass_d;
	double omega_stop_d;
	double ripple_pass;			//Del-p Passband bet (1-Dp)< H(jw) < (1+Dp)
	double ripple_stop;			//Del-s Stopband less than (Ds) > H(jw)
	double ripple_pass_db;
	double ripple_stop_db;
	double eps; //1/sqrt(1+(eps^2)) = (1-2*Dp);
	double A; //1/A = Ds
	double selectivity_parameter;		// omega_pass_ana/omega_stop_ana
	double discrimination_parameter;// eps/sqrt((A^2)-1)
	int Order;
}LP_Filter_Spec_t;
void Estimate_LP_params_from_ripple(LP_Filter_Spec_t *Filter_p);

#endif

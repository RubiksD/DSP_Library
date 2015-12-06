#include <math.h>
#include "Filter_Dsg.h"

void Estimate_LP_params_from_ripple(LP_Filter_Spac_t *Filter_p)
{
	Filter_p->omega_pass_d = (Filter_p->omega_pass_ana*2*M_PI)/Filter_p->F_sampl;
	Filter_p->omega_stop_d = (Filter_p->omega_stop_ana*2*M_PI)/Filter_p->F_sampl;
	Filter_p->ripple_pass_db = -20*log10(1-Filter_p->ripple_pass);
	Filter_p->ripple_stop_db = -20*log10(1-Filter_p->ripple_stop);
	Filter_p->eps = sqrt((1/((1-(2*Filter_p->ripple_pass))*(1-(2*Filter_p->ripple_pass))))-1);
	Filter_p->A		= 1/Filter_p->ripple_stop;
	Filter_p->selectivity_parameter = Filter_p->omega_pass_d/Filter_p->omega_stop_ana;
	Filter_p->discrimination_parameter	= Filter_p->eps/(sqrt((Filter_p->A*Filter_p->A)-1));
}



#include <complex.h>

#define	PI M_PI

void	FIR_Freq_Res_mag(double *num,int N,int points,double *response);
void	IIR_Freq_Res_mag(double *num,double *den,int N,int points,double *response);
void	FIR_Freq_Res_phase(double *num,int N,int points,double *response);
void	IIR_Freq_Res_phase(double *num,double *den,int N,int points,double *response);
void CT_Freq_Res_mag(double *num,double *den,int N,int points,double *response,double Wmax);

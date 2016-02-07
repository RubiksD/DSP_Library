/*
File: test_interpolate_decimate.c

*/

#include <stdio.h>
#include <math.h>
#include "Interpolate_Decimate.h"
#include "cordic.h"
#include "fft.h"

#undef F_SAMPLE
#undef F_SIN
#define F_SAMPLE 8000.0
#define F_SIN    300.0

#define INP_LEN 128
#define INT_FAC 8

int main()
{
	int Input[INP_LEN];
	int Output[(INP_LEN*INT_FAC)];
	int Output_ZOH[(INP_LEN*INT_FAC)];

	int Input_fft[2][INP_LEN];
	int Output_fft[2][(INP_LEN*INT_FAC)];
	int Output_ZOH_fft[2][(INP_LEN*INT_FAC)];
	
	int i;
	
	printf("Input Samples are\n");
	for(i=0; i<128 ; i++){
		Input[i] = 0xFFFF*sin(2*M_PI*i*F_SIN/F_SAMPLE);
		printf("%d\n",Input[i]);
	}

	interpolate(INP_LEN,INT_FAC,Input,Output);

	printf("Output Samples are\n");
	for(i=0; i<(INP_LEN*INT_FAC) ; i++){
		printf("%d\n",Output[i]);
	}
	interpolate_ZOH(INP_LEN,INT_FAC,Input,Output_ZOH);

	printf("Output Samples with ZOH are\n");
	for(i=0; i<(INP_LEN*INT_FAC) ; i++){
		printf("%d\n",Output_ZOH[i]);
	}
	
	create_lookup_table();

	fft_Npt(Input,Input_fft[0],Input_fft[1],INP_LEN);
	printf("Input Signal FFT\n");
	for(i=0;i<INP_LEN;i++){
		printf("%d\n",cordic_vector(Input_fft[0][i],Input_fft[1][i]));
	}
	printf("Output Signal FFT\n");
	fft_Npt(Output,Output_fft[0],Output_fft[1],INP_LEN*INT_FAC);
	for(i=0;i<INP_LEN*INT_FAC;i++){
		printf("%d\n",cordic_vector(Output_fft[0][i],Output_fft[1][i]));
	}
	printf("Output Signal with ZOH FFT\n");
	fft_Npt(Output_ZOH,Output_ZOH_fft[0],Output_ZOH_fft[1],INP_LEN*INT_FAC);
	for(i=0;i<INP_LEN*INT_FAC;i++){
		printf("%d\n",cordic_vector(Output_ZOH_fft[0][i],Output_ZOH_fft[1][i]));
	}
	
	return 0;
}

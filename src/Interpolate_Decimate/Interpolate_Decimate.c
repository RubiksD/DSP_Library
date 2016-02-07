/*
File: Interpolate_Decimate.c

*/

#include <stdio.h>

void interpolate(int N, int IF, int *Input, int *Output)
{
	int i,j;
	if(IF < 1){
		printf("Please give interpolation factor > 0\n");
	} else if (IF == 1){
		for(i=0; i<N; i++){
			Output[i] = Input[i];
		}
	} else {
		for(i=0; i<N; i++){
			Output[i*IF] = Input[i];
			for(j=1; j<IF ; j++){
				Output[j + (i*IF)] = 0;
			}
		}
	}
}

void interpolate_ZOH(int N, int IF, int *Input, int *Output)
{
	int i,j;
	if(IF < 1){
		printf("Please give interpolation factor > 0\n");
	} else if (IF == 1){
		for(i=0; i<N; i++){
			Output[i] = Input[i];
		}
	} else {
		for(i=0; i<N; i++){
			Output[i*IF] = Input[i];
			for(j=1; j<IF ; j++){
				Output[j + (i*IF)] = Input[i];
			}
		}
	}
}

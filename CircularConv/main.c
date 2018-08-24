#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "circularConvolution.h"

//#define BUFF_SIZE 256 
//#define firLength 51
//#define N_POINT (BUFF_SIZE + firLength - 1) + 78


int main()
{
	printf(" the circular convolution is\n");

	FILE *fp_inp, *fp_fir, *fp_res; 

	fp_inp = fopen("input.dat", "r");
	fp_fir = fopen("filter.dat", "r");
	fp_res = fopen("result.dat", "r+");
	if ((fp_inp == NULL)) {
		printf("I couldn't open input.dat for reading.\n");
		exit(0);
	}
	if ((fp_fir == NULL)) {
		printf("I couldn't open filter.dat for reading.\n");
		exit(0);
	}

	if ((fp_res == NULL)) {
		printf("I couldn't open result.dat for writing.\n");
		exit(0);
	}

	// reading the filter coefficients into array of N_POINT buffer
	float x[N_POINT];
	float h[N_POINT];
	float* wholeData; 
	
	// count the number of lines in the input data file:
	int count = 0;
	char c;
	for (c = getc(fp_inp); c != EOF; c = getc(fp_inp))
		if (c == '\n') // Increment count if this character is newline
			count = count + 1;
	//reset the file pointer
	fseek(fp_inp, 0, SEEK_SET);

	//allocate the memory to the data:
	wholeData = malloc(count * sizeof(float));
	for(int i= 0; i< count; i++)
	{
		fscanf(fp_inp, "%f", (wholeData+i));
		//printf("data %d:  %f\n", i, *(wholeData + i));
	}
	fseek(fp_inp, 0, SEEK_SET);

	// zero pad the sequence block in the front
	for (int k = 0; k < firLength - 1; k++)
	{
		//fscanf(fp_inp, "%f", &x[k
		x[k] = 0;
		//printf("data %d : %f\n",i,  x[i]);
	}
	//copy sequence from input file to the sequence block
	for (int k = firLength - 1; k < N_POINT; k++)
	{
		fscanf(fp_inp, "%f", &x[k]);
		//printf("data %d : %f\n",k,  x[k]);
		//printf("the fileptr value: %ld\n", ftell(fp_inp));
	}

	//copy the fir block
	for (int j = 0; j < firLength; j++)
	{
		fscanf(fp_fir, "%f", &h[j]);
		//printf("data %d : %f\n", j, h[j]);
	}
	
	//zeropad the fir filter:
	for (int j = firLength; j < N_POINT; j++)
		h[j] = 0;

	//calculating output for the very first zeropadded block:
	float * p;
	int MminusOne = (firLength - 1);
	p = circularConv(N_POINT, x, h);
	for (int i = MminusOne; i < N_POINT; i++)
	{
		//printf("the %d value is %f \n", i, *(p + i));
		fprintf(fp_res, "%f\n", checkRange(*(p + i)));
	}

	//fixing the shift variable
	int srtInx = BUFF_SIZE - ( firLength - 1); 
	//int endInx = BUFF_SIZE - (firLength - 1) + BUFF_SIZE;



	//calculation for rest of the blocks:
	//offset value by seeing the binary input file pointer values: change by 11
	int offset = 11* (firLength - 1);
	//fseek(fp_res, offset, SEEK_SET);
	//printf("the value of fp_inp: %ld\n", ftell(fp_res));
	for (int j = srtInx; j< count; j= j+N_POINT) 
	{
		for (int i = 0; i < N_POINT; i++)
		{
			x[i] = *(wholeData + i + j);
			//printf("Data is: %f \n", *(wholeData + i));
		}

		fseek(fp_res, -offset, SEEK_END);
		//printf("the value of fp_inp: %ld\n", ftell(fp_res));
		p = circularConv(N_POINT, x, h);
		for (int i = 0; i < N_POINT; i++)
		{
			//y[i] = circularConv(n, x, h);
			//printf("the %d value is %f \n", i, *(p + i));
			//printf("the value of fp_inp: %ld\n", ftell(fp_res));
			fprintf(fp_res, "%f\n", checkRange(*(p + i)));
		}

	}


	free(wholeData);
	fclose(fp_res);
	fclose(fp_inp);
	fclose(fp_fir);

	printf("End of Filtering\n");
	getchar();
}




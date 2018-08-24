#include<stdio.h>
#include<string.h>
#include "circularConvolution.h"

//#define BUFF_SIZE 256 
//#define firLength 51
//#define N_POINT (BUFF_SIZE + firLength - 1) 

void printName()
{
	printf("This is Satnam");
}

float checkRange(float input) 
{
	float output;
	if (input > 1.0) {
		output = 1.0;
	}
	else if (input < -1.0) {
		output = -1.0;
	}
	else {
		output = input;
	}

	return output;
}
//int m, n, x[30], h[30], y[30], i, j, k, x2[30], a[30];

float* circularConv(int n, float x[], float h[])
{


	float x2[N_POINT] = { 0 }, a[N_POINT] = { 0 };
	static float y[N_POINT] = { 0 };

	y[0] = 0;
	a[0] = *(h + 0);

	for (int j = 1; j < n; j++)            /*folding h(n) to h(-n)*/
		a[j] = *(h + n - j);

	/*Circular convolution*/
	for (int i = 0; i < n; i++)
		y[0] += *(x + i) * a[i];

	for (int k = 1; k < n; k++)
	{
		y[k] = 0;
		/*circular shift*/

		for (int j = 1; j < n; j++)
			x2[j] = a[j - 1];
		x2[0] = a[n - 1];
		for (int i = 0; i < n; i++)
		{
			a[i] = x2[i];
			y[k] += *(x + i) * x2[i];
		}
	}
	return y;
}
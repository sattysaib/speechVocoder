#pragma once

#include<stdio.h>
#include<stdlib.h>
#define BUFF_SIZE 256 
#define firLength 51
#define N_POINT (BUFF_SIZE + firLength - 1) 

void printName(); 
float checkRange(float input);
float* circularConv(int n, float x[], float h[]); 

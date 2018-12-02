#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

//const int NUM_SLICES 	= 90;
//const int NUM_THREADS	=  4;
const int NUM_X = 3;
const int NUM_Y = 3;

static long m1[NUM_X][NUM_Y] = { 0 };
static long m2[NUM_X][NUM_Y] = { 0 };
static long m3[NUM_X][NUM_Y] = { 0 };


void print_m(long m[NUM_X][NUM_Y])
{
        for (int j = 0; j < NUM_Y; j++)
        {
                for (int i = 0; i < NUM_X; i++)
                {
                        printf("%ld\t",  m[i][j]);
                }
                printf("\r\n");
        }
}


int main(void)
{
	long idx = 0;

	for (int i = 0; i < NUM_X; i++)
		for (int j = 0; j < NUM_Y; j++)
			m1[i][j] = m2[j][i] = idx++;


	// MatMul

	#pragma omp parallel for
	for (long idx_x = 0; idx_x < NUM_X; idx_x++)
	{
		for (long idx_y = 0; idx_y < NUM_Y; idx_y++)
		{
			long sum = 0;

			for (long mul_slice = 0; mul_slice < NUM_X; mul_slice++)
				sum += m1[mul_slice][idx_y] * m2[idx_x][mul_slice];

			m3[idx_x][idx_y] = sum;
		}
	}


	printf("m1[][] =\r\n");
	print_m(m1);
	printf("\r\n");

        printf("m2[][] =\r\n");
        print_m(m2);
        printf("\r\n");

        printf("m3[][] =\r\n");
        print_m(m3);
        printf("\r\n");

        return 0;
}

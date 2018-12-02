#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

const int NUM_SLICES 	= 90;
//const int NUM_THREADS	=  4;

static long fib[NUM_SLICES] = { 0, 1 };


int main(void)
{
	long c;

	#pragma omp parallel private(c)
	{
		#pragma omp for ordered
		for (long idx = 0; idx < NUM_SLICES; idx++)
		{
			#pragma omp ordered
			{
				fib[idx + 2] = c = fib[idx] + fib[idx + 1];
				printf("%02ld: %ld\r\n", idx, c);
			}
		}
	}

        return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

const int NUM_SLICES 	= 1000000;
//const int NUM_THREADS	=  4;


int main(void)
{
	long ac = 0;
	double x, y;

	#pragma omp parallel private(x, y)
	{
		#pragma omp for
		for(long idx = 0; idx < NUM_SLICES; idx++)
		{
			x = (2.0 * rand() / RAND_MAX) - 1.0;
			y = (2.0 * rand() / RAND_MAX) - 1.0;

			if (x*x + y*y < 1.0)
				#pragma omp atomic
					ac++;
		}
	}

	printf("pi = %lf - done.\n", 4.0 * ac / NUM_SLICES);
        return 0;
}

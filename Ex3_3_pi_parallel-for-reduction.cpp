#include <stdio.h>
#include "omp.h"

static long num_steps 	= 160000;
static long cnt_threads	= 16;

int main(void)
{
	double sum = 0.0;
	const double step = 1.0 / (double)num_steps;

	omp_set_num_threads(cnt_threads);

	#pragma omp parallel for reduction (+:sum)
	for (long i = 0; i < num_steps; i++)
	{
		double x = (i + 0.5) * step;
		double subsum = 4.0 / (1.0 + x*x);

		sum += subsum;
	}
		
	double pi  = step * sum;
	printf("sum: pi=%f\n", pi);

	return 0;
}


// <EOF>

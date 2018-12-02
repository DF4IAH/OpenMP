#include <stdio.h>
#include <stdlib.h>
#include "omp.h"


const long N = 256;


static void fill_rand(long len, double* ary)
{
	long idx;

	sranddev();

	#pragma omp parallel for private(idx)
	for (idx = 0; idx < len; idx++) {
		ary[idx] = (double)rand() / (double)rand();
	}
}

static double Sum_array(long len, const double* ary)
{
	long idx;
	double s = 0.0;

	#pragma omp parallel for private(idx)
	for (long idx = 0; idx < len; idx++)
		s += ary[idx];
	
	return s;
}

static double check(long len, const double* ary)
{
	double sum = 0.0;

	for (long idx = 0; idx < len; idx++) {
		printf("%lf  ", ary[idx]);
		sum += ary[idx];
	}

	return sum;
}


int main(void)
{
	double* A, sum, runtime; 
	int flag = 0;

	A = (double*) malloc(N * sizeof(double));

	runtime = omp_get_wtime();
	fill_rand(N, A); // Producer: fill an array of data

	#pragma omp flush(A, runtime)

	sum = Sum_array(N, A); // Consumer: sum the array
	runtime = omp_get_wtime() - runtime;
	printf(" In %lf seconds, The sum is %lf \n", runtime, sum);

	#if 1
	#pragma omp flush(A, runtime)

	runtime = omp_get_wtime();
	sum = check(N, A);
	runtime = omp_get_wtime() - runtime;
        printf(" In %lf seconds, The sum is %lf \n", runtime, sum);
	#endif

	free(A);
	A = NULL;

        return 0;
}

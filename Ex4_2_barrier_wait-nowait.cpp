#include <stdio.h>
#include "omp.h"

const int NUM_SLICES 	= 16;
const int NUM_THREADS	=  4;


static long A[NUM_SLICES]	= { 0 };
static long B[NUM_SLICES]	= { 0 };
static long C[NUM_SLICES]	= { 0 };


long big_calc1(long id)
{
	printf("big_calc1(%ld)\r\n", id);
	return id + 100;
}

long big_calc2(long C[NUM_SLICES], long idx)
{
        printf("big_calc2(.., %ld)\r\n", idx);
	return C[idx] + 1000000;
}

long big_calc3(long idx, long A[NUM_SLICES])
{
        printf("big_calc3(%ld, ..)\r\n", idx);
	return A[idx] + 10000;
}

long big_calc4(long id)
{
        printf("big_calc4(%ld)\r\n", id);
	return id + 200;
}


int main(void)
{
	long id;

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel shared (A, B, C) private(id) 
	{
		id = omp_get_thread_num();
		A[id] = big_calc1(id);

		#pragma omp barrier

		#pragma omp for 
		for (long i = 0; i < NUM_SLICES; i++)
		{
			C[i] = big_calc3(i, A);
		}

		#pragma omp for nowait
		for (long i = 0; i < NUM_SLICES; i++)
		{
			B[i] = big_calc2(C, i);
		}

		A[id] = big_calc4(id);
	}
        
	printf("done.\n");
        return 0;
}

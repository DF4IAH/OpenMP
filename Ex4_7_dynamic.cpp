#include <stdio.h>
#include "omp.h"

//const int NUM_SLICES 	= 16;
//const int NUM_THREADS	=  4;


int main(void)
{
	long id;
	long num_threads;

	omp_set_dynamic(0);
	omp_set_num_threads(omp_get_num_procs());

	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();

		#pragma omp single
			num_threads = omp_get_num_threads();

		printf("id = %ld, num_threads = %ld\r\n", id, num_threads);
	}

	printf("done.\n");
        return 0;
}

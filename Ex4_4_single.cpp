#include <stdio.h>
#include "omp.h"

const int NUM_SLICES 	= 16;
const int NUM_THREADS	=  4;


int main(void)
{
	long id;

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
		id = omp_get_thread_num();

		#pragma omp single nowait
		{
			id += 100;
			printf("single: id = %ld\r\n", id);
		}

		id = omp_get_thread_num();
		printf("id = %ld\r\n", id);
	}
        
	printf("done.\n");
        return 0;
}

#include <stdio.h>
#include "omp.h"

const int NUM_SLICES 	= 16;
const int NUM_THREADS	=  4;


int main(void)
{
	long id;
	long tmp;
	omp_lock_t lck;

	omp_set_num_threads(NUM_THREADS);
	omp_init_lock(&lck);

	#pragma omp parallel private(tmp, id)
	{
		id = omp_get_thread_num();
		tmp = 1 + id;

		omp_set_lock(&lck);
			printf("tmp = %ld\r\n", tmp);
		omp_unset_lock(&lck);
	}

	omp_destroy_lock(&lck);

	printf("done.\n");
        return 0;
}

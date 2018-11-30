#include <stdio.h>
#include "omp.h"

const int NUM_SLICES 	= 16;
const int NUM_THREADS	=  4;


int main(void)
{
	long res = 0;
	long id;
	long tmp;

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel private(tmp)
	{
		id = omp_get_thread_num();

		#pragma omp for ordered reduction(+:res)
		for (long idx = 0; idx < NUM_SLICES; idx++)
		{
			tmp = idx;

			#pragma omp ordered
			{
				res += tmp;
				printf("tmp = %ld\r\n", tmp);
			}

			//printf("tmp = %ld\r\n", tmp);
		}
	}

	printf("res = %ld\r\n", res);
        
	printf("done.\n");
        return 0;
}

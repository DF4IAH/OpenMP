#include <stdio.h>
#include "omp.h"

int main(void)
{
	//omp_set_num_threads(20);
	#pragma omp parallel num_threads(4)
	{
		int ID = omp_get_thread_num();
	
		printf(" hello(%d) ", ID);
		printf(" world(%d) \n", ID);
	}
	printf("done.\n");

	return 0;
}


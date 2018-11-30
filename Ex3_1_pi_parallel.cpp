#include <stdio.h>
#include "omp.h"

static long num_steps 	= 160000;
static long cnt_threads	= 16;

int main(void)
{
	double sum = 0.0, sum2 = 0.0;
	const double step = 1.0 / (double)num_steps;

	omp_set_num_threads(cnt_threads);

	for (long idx = 0; idx < num_steps; idx += cnt_threads) {
		//double subsum[cnt_threads] = { 0.0 };

		#pragma omp parallel
		{
			long localIdx = idx;
			int threadNum = omp_get_thread_num();
			localIdx += threadNum;

			double x = (localIdx + 0.5) * step;
			double subsum2 = 4.0 / (1.0 + x*x);
			//subsum[threadNum] = 4.0 / (1.0 + x*x);

			//#pragma omp critical
			#pragma omp atomic
				sum2 += subsum2;
		}
		
		#if 0
		for (long idx2 = 0; idx2 < cnt_threads; idx2++) {
			sum += subsum[idx2];
		}
		#endif
	}


	double pi  = step * sum;
	double pi2 = step * sum2;

	printf("sum: pi=%f, sum2: pi=%f\n", pi, pi2);

	return 0;
}


// <EOF>

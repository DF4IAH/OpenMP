#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "omp.h"

const int NUM_SLICES 	= 8000;
const int NUM_COEF	= 64;

// Octave: hn = fir2(62, [0 0.38 0.39 1], [1 1 0.000001 0.000001], 512, kaiser(63,4));
const double FIR_coef[NUM_COEF] = {
  -1.7721e-04,  -1.1338e-03,  -7.2621e-04,   1.1689e-03,   2.1288e-03,   8.4506e-05,  -3.0112e-03,  -2.6415e-03,
   1.9965e-03,   5.2658e-03,   1.6162e-03,  -5.7235e-03,  -6.7875e-03,   2.0301e-03,   1.0499e-02,   5.8141e-03,
  -8.9185e-03,  -1.4676e-02,  -2.7467e-04,   1.8765e-02,   1.5493e-02,  -1.1979e-02,  -3.0208e-02,  -8.7772e-03,
   3.3968e-02,   4.1043e-02,  -1.4195e-02,  -7.6653e-02,  -4.8827e-02,   1.0448e-01,   2.9721e-01,

   3.8500e-01,

                 2.9721e-01,   1.0448e-01,  -4.8827e-02,  -7.6653e-02,  -1.4195e-02,   4.1043e-02,   3.3968e-02,
  -8.7772e-03,  -3.0208e-02,  -1.1979e-02,   1.5493e-02,   1.8765e-02,  -2.7467e-04,  -1.4676e-02,  -8.9185e-03,
   5.8141e-03,   1.0499e-02,   2.0301e-03,  -6.7875e-03,  -5.7235e-03,   1.6162e-03,   5.2658e-03,   1.9965e-03,
  -2.6415e-03,  -3.0112e-03,   8.4506e-05,   2.1288e-03,   1.1689e-03,  -7.2621e-04,  -1.1338e-03,  -1.7721e-04
};

void fir64(double out[], long len, const double in[])
{
	double sum;

	//omp_set_num_threads(1);
	omp_set_num_threads(omp_get_num_procs());

	#pragma omp parallel for private(sum)
	for (long idx = NUM_COEF; idx < len; idx++) {
		sum = 0.0;

		for (long coef = 0; coef < NUM_COEF; coef++)
		{
			sum += FIR_coef[coef] * in[idx - coef -1];
		}
		out[idx - NUM_COEF] = sum;
	}
}

int main(void)
{
	double sweep[NUM_SLICES];
	double filtered[NUM_SLICES] = { 0.0 };
	struct timeval tv;

	for (long idx = 0; idx < NUM_SLICES; idx++) {
		sweep[idx] = sin((idx * pow(10, 1.5 * idx / (double)NUM_SLICES)) / 100.0);
	}

	gettimeofday(&tv, NULL);
	long t1 = tv.tv_usec;
	fir64(filtered, NUM_SLICES, sweep);
	gettimeofday(&tv, NULL);
	long t2 = tv.tv_usec;

	#if 1
	for (long idx = 0; idx < NUM_SLICES; idx++) {
		int y = 40 * (1.0 + filtered[idx]);

		for (int i = 0; i < y; i++) {
			printf(" ");
		}
		printf("*\r\n");
	}
	#endif

	printf("tdiff=%ld us, num_procs=%d\r\n", t2 - t1, omp_get_num_procs());

	return 0;
}

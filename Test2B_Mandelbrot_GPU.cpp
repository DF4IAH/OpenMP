#include <complex>
#include <cstdio>
#include <omp.h>
 
typedef std::complex<double> complex;

 
int MandelbrotCalculate(complex c, int maxiter)
{
	// iterates z = z + c until |z| >= 2 or maxiter is reached,
	// returns the number of iterations.

	complex z 	= c;
	int 	n	= 0;

	for(; n < maxiter; ++n)
	{
		if (std::abs(z) >= 2.0)
			break;

		z = z*z + c;
	}
	return n;
}

void printScreen(const char DISP[], int width, int height)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			const char c = DISP[y * width + x];

			std::putchar(c);
			if (x + 1 == width)
				std::puts("|");
		}
}


int main()
{
	const int 	width 			= 78,
			height 			= 44,
			num_pixels 		= width * height;

	const complex 	center			(-.7, 0),
			span			(2.7, -(4 /3.0) * 2.7 * height / width);
	const complex 	begin 			= center - span / 2.0;
			//, end 		= center + span / 2.0;
	const int 	maxiter 		= 100000;
	char		DISP[width * height]	= { 0 };


	omp_set_num_threads(width);

	#pragma omp target map(tofrom:DISP) 
	#pragma omp teams distribute parallel for num_teams(height / 4) num_threads(width * 4)
	for (int pix = 0; pix < num_pixels; ++pix)
	{
		const int x = pix % width, y = pix / width;

		complex c = begin + complex(x * span.real() / (width  + 1.0),
					    y * span.imag() / (height + 1.0));

		int n = MandelbrotCalculate(c, maxiter);
		if (n == maxiter) 
			n = 0;

		{
			char c = ' ';

			if (n > 0)
			{
				static const char charset[] = ".,c8M@jawrpogOQEPGJ";
				c = charset[n % (sizeof(charset)-1)];
			}
			DISP[pix] = c;
		}
	}

	printScreen(DISP, width, height);
}

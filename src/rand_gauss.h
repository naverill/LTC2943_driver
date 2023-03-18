/*
 * Normal random numbers generator - Marsaglia algorithm.
 */
#include <math.h>

double rand_gauss(double mu, double sigma)
{
    double x, y, rsq, f;
    do {
	x = 2.0 * rand() / (double)RAND_MAX - 1.0;
	y = 2.0 * rand() / (double)RAND_MAX - 1.0;
	rsq = x * x + y * y;
    } while( rsq >= 1. || rsq == 0. );
    f = sqrt( -2.0 * log(rsq) / rsq );
    x = x * f;
    return (mu + sigma * (double) x);
}


double rand_gauss_range(double min, double max, double sigma){
    double x = rand_gauss(0., sigma);
    return -min + x * (max - min);
}  

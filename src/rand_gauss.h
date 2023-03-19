/*
 * Normal random numbers generator - Marsaglia algorithm.
 */
#include <math.h>

float64_t rand_gauss(float32_t mu, float64_t sigma)
{
    float64_t x, y, rsq, f;
    do {
	x = 2.0f * rand() / (float64_t)RAND_MAX - 1.0f;
	y = 2.0f * rand() / (float64_t)RAND_MAX - 1.0f;
	rsq = x * x + y * y;
    } while( rsq >= 1.f || rsq == 0.f );
    f = sqrt( -2.0f * log(rsq) / rsq );
    x = x * f;
    return (mu + sigma * (float64_t) x);
}


float64_t rand_gauss_range(float64_t min, float64_t max, float64_t sigma){
    float64_t x = rand_gauss(0.f, sigma);
    return -min + x * (max - min);
}  

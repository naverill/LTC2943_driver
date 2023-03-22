#ifndef RAND_GAUSS_H
#define RAND_GAUSS_H
/*
 * Normal random numbers generator - Marsaglia algorithm.
 */
#include <math.h>
#include <stdlib.h>

float rand_gauss(float mu, float sigma){
    float x, y, rsq, f;
    do {
	x = 2.0f * rand() / (float)RAND_MAX - 1.0f;
	y = 2.0f * rand() / (float)RAND_MAX - 1.0f;
	rsq = x * x + y * y;
    } while( rsq >= 1.f || rsq == 0.f );
    f = sqrt( -2.0f * log(rsq) / rsq );
    x = x * f;
    return (mu + sigma * (float) x);
}


float rand_gauss_range(float min, float max, float sigma){
    float x = rand_gauss(0.5, sigma);
    if (x > 1){
        x = 1; 
    } 
    else if (x < 0){
        x = 0;
    }
    return min + x * (max - min);
}  

#endif // RAND_GAUSS_H

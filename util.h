#ifndef UTIL_GUARD
#define UTIL_GUARD
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/**
 * Returns a random float between a and b.
 */
float randfl(float a, float b);
#endif
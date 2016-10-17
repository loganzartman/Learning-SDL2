#include <stdlib.h>
#include "util.h"

float randfl(float a, float b) {
	return (float)rand()/(float)(RAND_MAX/(b-a)) + a;
}
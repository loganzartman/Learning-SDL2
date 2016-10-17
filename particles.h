#include <stdbool.h>
#include "SDL.h"
#include "vector.h"

#ifndef PARTICLE_GUARD
#define PARTICLE_GUARD
#define PARTICLE_SIZE 8

vector* particles_list;

typedef struct particle {
	float x, y;
	float vx, vy;
	bool dead;
} particle;

void particles_init();
void particles_add(particle *p);
void particles_step(float timescale);
void particles_draw(SDL_Renderer *rnd);
particle* particle_new(float x, float y, float vx, float vy);
void particle_step(particle* p, float timescale);
float particle_speed(particle *p);
#endif

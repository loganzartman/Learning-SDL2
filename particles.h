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

/**
 * Initializes the particle system
 */
void particles_init();

/**
 * Adds a new particle to the particle system.
 * particle_new can be used to obtain a new particle.
 */
void particles_add(particle *p);

/**
 * Advance the particle simulation.
 * timescale is a float representing the ratio of actual frame time to desired frame time.
 */
void particles_step(float timescale);

/**
 * Renders all particles using a supplied SDL_Renderer
 */
void particles_draw(SDL_Renderer *rnd);

/**
 * Returns a pointer to a new particle with the given parameters.
 * Make sure to free() the pointer if the particle is dead.
 */
particle* particle_new(float x, float y, float vx, float vy);

/**
 * Advance the simulation of a single particle.
 * Called by particles_step
 */
void particle_step(particle* p, float timescale);

/**
 * Calculates the speed of a given particle.
 */
float particle_speed(particle *p);
#endif

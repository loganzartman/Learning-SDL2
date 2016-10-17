#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "SDL.h"
#include "vector.h"
#include "util.h"
#include "particles.h"
#include "graphics.h"

void particles_init() {
	particles_list = vector_new();
}

void particles_add(particle *p) {
	vector_add(particles_list, p);
}

void particles_step(float timescale) {
	for (int i=0,o=0; i<particles_list->size; i++) {
		particle* p = (particle*)vector_get(particles_list, i);
		particle_step(p, timescale);
		if (p->dead) {
			o++;
			i--;
			particles_list->size--;
			free(p);
		}
		particles_list->cont[i+1] = particles_list->cont[i+1+o];
	}
}

void particles_draw(SDL_Renderer *rnd) {
	for (int i=0; i<particles_list->size; i++) {
		particle* p = (particle*)vector_get(particles_list, i);
		int bval = MIN((int)(255 * particle_speed(p) / 30.0f), 255);
		SDL_SetRenderDrawColor(rnd, 255-bval, 0, bval, 255);
		SDL_RenderDrawLine(rnd, p->x, p->y, p->x-p->vx, p->y-p->vy);
	}
};

particle* particle_new(float x, float y, float vx, float vy) {
	particle *p = malloc(sizeof(particle));

	p->x = x;
	p->y = y;
	p->vx = vx;
	p->vy = vy;
	p->dead = false;
	return p;
}

void particle_step(particle *p, float timescale) {
	p->x += p->vx * timescale;
	p->y += p->vy * timescale;
	p->vy += 0.5;

	if (p->x < 0 || p->y < 0 || p->x > gfx_dim.w || p->y > gfx_dim.h) {
		p->dead = true;
	}
}

float particle_speed(particle *p) {
	float vx = p->vx;
	float vy = p->vy;
	return sqrt(vx*vx+vy*vy);
}
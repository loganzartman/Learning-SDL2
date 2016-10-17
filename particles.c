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
	for (int i=0; i<particles_list->size; i++) {
		particle* p = (particle*)vector_get(particles_list, i);
		particle_step(p, timescale);
	}
	for (int i=particles_list->size-1; i>=0; i--) {
		particle* p = (particle*)vector_get(particles_list, i);
		if (p->dead) {
			vector_remove(particles_list, i);
			free(p);
		}
	}
}

void particles_draw(SDL_Renderer *rnd) {
	for (int i=0; i<particles_list->size; i++) {
		particle* p = (particle*)vector_get(particles_list, i);
		int bval = MIN((int)(255 * particle_speed(p) / 20.0f), 255);
		SDL_SetRenderDrawColor(rnd, 255-bval, 0, bval, 255);
		SDL_RenderFillRect(rnd, &(p->rect));
	}
};

particle* particle_new(float x, float y, float vx, float vy) {
	particle *p = malloc(sizeof(particle));
	SDL_Rect rect;
	rect.w = PARTICLE_SIZE;
	rect.h = PARTICLE_SIZE;

	p->x = x;
	p->y = y;
	p->vx = vx;
	p->vy = vy;
	p->dead = false;
	p->rect = rect;
	return p;
}

void particle_step(particle *p, float timescale) {
	p->x += p->vx * timescale;
	p->y += p->vy * timescale;
	p->vy += 0.5;

	p->rect.x = p->x;
	p->rect.y = p->y;
	if (p->x < 0 || p->y < 0 || p->x > gfx_dim.w || p->y > gfx_dim.h) {
		p->dead = true;
	}
}

float particle_speed(particle *p) {
	float vx = p->vx;
	float vy = p->vy;
	return sqrt(vx*vx+vy*vy);
}
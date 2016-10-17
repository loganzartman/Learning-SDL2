#include <stdio.h>
#include "SDL.h"
#include "graphics.h"
#include "particles.h"
#include "util.h"

SDL_Window *gfx_win;
SDL_Renderer *gfx_rnd;

int gfx_init() {
	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("SDL_Init Error: %s\n",SDL_GetError());
		return 1;
	}
	
	//create window
	gfx_dim.w = 800;
	gfx_dim.h = 600;
	gfx_win = SDL_CreateWindow(
		"Hello SDL!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		gfx_dim.w, gfx_dim.h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if (gfx_win == NULL) {
		printf("SDL_CreateWindow error: %s\n", SDL_GetError());
		return 1;
	}

	//create renderer
	gfx_rnd = SDL_CreateRenderer(
		gfx_win,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (gfx_rnd == NULL) {
		printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
		return 1;
	}

	rectangle.x = 100;
	rectangle.y = 100;
	rectangle.w = 32;
	rectangle.h = 32;

	printf("SDL_Init success!\n");
	return 0;
}

void gfx_draw() {
	SDL_SetRenderDrawColor(gfx_rnd, 43, 38, 40, 255);
	SDL_RenderFillRect(gfx_rnd, &gfx_dim);

	particles_draw(gfx_rnd);
	SDL_RenderPresent(gfx_rnd);
}

void gfx_destroy() {
	SDL_DestroyRenderer(gfx_rnd);
	SDL_DestroyWindow(gfx_win);
	SDL_Quit();
}

void gfx_setDrawHue(SDL_Renderer *rnd, float hue) {
	hue -= (int)hue;
	float r,g,b,hf;
	if (hue < 0.33) {
		hf = 2*hue/0.33;
		r = MIN(1, 2-hf);
		g = MIN(1, hf);
		b = 0;
	}
	else if (hue < 0.66) {
		hf = 2*(hue-0.33)/0.33;
		r = 0;
		g = MIN(1, 2-hf);
		b = MIN(1, hf);
	}
	else {
		hf = 2*(hue-0.66)/0.33;
		r = MIN(1, hf);
		g = 0;
		b = MIN(1, 2-hf);
	}
	SDL_SetRenderDrawColor(rnd, (int)(r*255), (int)(g*255), (int)(b*255), 255);
}
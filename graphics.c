#include <stdio.h>
#include "SDL.h"
#include "graphics.h"

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
		SDL_WINDOW_SHOWN
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
	SDL_SetRenderDrawColor(gfx_rnd, 255, 255, 255, 255);
	SDL_RenderFillRect(gfx_rnd, &gfx_dim);

	SDL_SetRenderDrawColor(gfx_rnd, 255, 0, 0, 255);
	SDL_RenderFillRect(gfx_rnd, &rectangle);
	SDL_RenderPresent(gfx_rnd);
}

void gfx_destroy() {
	SDL_DestroyRenderer(gfx_rnd);
	SDL_DestroyWindow(gfx_win);
	SDL_Quit();
}
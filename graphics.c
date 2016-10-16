#include <stdio.h>
#include "SDL.h"
#include "graphics.h"

SDL_Window *gfx_win;
SDL_Renderer *gfx_rnd;
SDL_Rect rectangle;

int gfx_init() {
	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("SDL_Init Error: %s\n",SDL_GetError());
		return 1;
	}
	
	//create window
	gfx_win = SDL_CreateWindow(
		"Hello SDL!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800, 600,
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
		SDL_RENDERER_ACCELERATED
	);
	if (gfx_rnd == NULL) {
		printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
		return 1;
	}

	rectangle.x = 64;
	rectangle.y = 64;
	rectangle.w = 64;
	rectangle.h = 64;

	printf("SDL_Init success!\n");
	return 0;
}

void gfx_draw() {
	SDL_SetRenderDrawColor(gfx_rnd, 255, 0, 0, 255);
	SDL_RenderFillRect(gfx_rnd, &rectangle);
	SDL_RenderPresent(gfx_rnd);
}

void gfx_destroy() {
	SDL_DestroyRenderer(gfx_rnd);
	SDL_DestroyWindow(gfx_win);
	SDL_Quit();
}
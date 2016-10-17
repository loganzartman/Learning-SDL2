#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SDL.h"
#include "vector.h"
#include "Timer.h"
#include "game.h"
#include "graphics.h"

const int GAME_FPS = 60;
bool game_running = true;
SDL_Event event;
Timer game_timer;

int main(int argc, char *argv[]) {
	if (gfx_init() != 0) {
		//return 1;
	}

	//vector test
	vector v = vector_new();
	for (int i=0; i<100; i++) {
		int *j = malloc(sizeof(int));
		*j = i;
		vector_add(&v, j);
	}
	free(vector_remove(&v, 1)); //remove one element
	
	//print and remove all elements from vector
	while (v.size > 0) {
		printf("%d ", *((int*)vector_get(&v, 0)));
		free(vector_remove(&v, 0));
	}

	//start game timer
	Timer_start(&game_timer);
	
	while (game_running) {
		//determine actual time since last frame, then reset timer
		uint32_t dt = Timer_elapsed(&game_timer);
		Timer_start(&game_timer);

		//poll events from queue
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				game_running = false;
				break;
			}
		}

		game_loop(dt / (1000.0f / GAME_FPS));

		//cap FPS
		uint32_t dtCurrent = Timer_elapsed(&game_timer);
		if (dtCurrent < 1000/GAME_FPS) {
			SDL_Delay(1000/GAME_FPS - dtCurrent);
		}
	}

	gfx_destroy();
	return 0;
}

void game_loop(float timescale) {
	rectangle.x = gfx_dim.w * 0.5;
	rectangle.y = gfx_dim.h * 0.5;
	rectangle.x += sin(Timer_now() * 0.001) * gfx_dim.w * 0.3;
	rectangle.y += sin(Timer_now() * 0.002) * gfx_dim.h * 0.2;

	gfx_draw();
}
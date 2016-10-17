#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SDL.h"
#include "vector.h"
#include "Timer.h"
#include "util.h"
#include "game.h"
#include "graphics.h"
#include "particles.h"

const int GAME_FPS = 60;
bool game_running = true;
SDL_Event event;
Timer game_timer;

int main(int argc, char *argv[]) {
	if (gfx_init() != 0) {
		return 1;
	}

	particles_init();

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
	float x = gfx_dim.w * 0.5 + sin(Timer_now() * 0.004) * gfx_dim.w * 0.3;
	float y = gfx_dim.h * 0.5 + sin(Timer_now() * 0.008) * gfx_dim.h * 0.15;
	float dx = cos(Timer_now() * 0.004) * 15;
	float dy = cos(Timer_now() * 0.008) * 10;
	
	for (int i=0; i<100; i++) {
		float d = randfl(0, 6.28);
		float s = randfl(0.5, 3);
		float vx = dx + cos(d) * s;
		float vy = dy + sin(d) * s;
		particles_add(particle_new(x, y, vx, vy));
	}
	
	particles_step(timescale);

	printf("cap=%d, n=%d\n",particles_list->capacity,particles_list->size);

	gfx_draw();
}
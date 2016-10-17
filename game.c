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
			else if (event.type == SDL_MOUSEMOTION) {
				mouse.x = event.motion.x;
				mouse.y = event.motion.y;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					mouse.down = true;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					mouse.down = false;
				}
			}
			else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					gfx_dim.w = event.window.data1;
					gfx_dim.h = event.window.data2;
				}
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
	float x,y,dx,dy,len;
	if (mouse.down) {
		x = mouse.px;
		y = mouse.py;
		float vx = mouse.x - mouse.px;
		float vy = mouse.y - mouse.py;
		dx = vx;
		dy = vy;
		len = sqrt(vx*vx + vy*vy);
	}
	else {
		x = gfx_dim.w * 0.5 + sin(Timer_now() * 0.004) * gfx_dim.w * 0.3;
		y = gfx_dim.h * 0.5 + sin(Timer_now() * 0.008) * gfx_dim.h * 0.15;
		dx = cos(Timer_now() * 0.004) * 60;
		dy = cos(Timer_now() * 0.008) * 40;
		len = sqrt(dx*dx + dy*dy);
	}
	mouse.px = mouse.x;
	mouse.py = mouse.y;

	float d0 = atan2(dy,dx);
	for (int i=0; i<len; i++) {
		float xx = x + dx * i / len;
		float yy = y + dy * i / len;

		for (int j=0; j<4; j++) {
			float d = randfl(0, 6.28);
			float s = randfl(0.5, 1);
			float rd0 = randfl(-0.4,0.4);
			float rs = randfl(0.5,1.0);
			float vx = cos(d0 + rd0)*len*rs*0.3 + cos(d) * s;
			float vy = sin(d0 + rd0)*len*rs*0.3 + sin(d) * s;
			particles_add(particle_new(xx, yy, vx, vy));
		}
	}

	particles_step(timescale);

	// printf("cap=%d, n=%d\n",particles_list->capacity,particles_list->size);

	gfx_draw();
}
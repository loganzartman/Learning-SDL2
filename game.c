#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"
#include "Timer.h"
#include "graphics.h"

const int GAME_FPS = 60;
bool game_running = true;
SDL_Event event;
Timer game_timer;

int main(int argc, char *argv[]) {
	if (gfx_init() != 0) {
		//return 1;
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

		//draw screen
		gfx_draw();

		//cap FPS
		uint32_t dtCurrent = Timer_elapsed(&game_timer);
		if (dtCurrent < 1000/GAME_FPS) {
			SDL_Delay(1000/GAME_FPS - dtCurrent);
		}
	}

	gfx_destroy();
	return 0;
}

void game_loop() {

}
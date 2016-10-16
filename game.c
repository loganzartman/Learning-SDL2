#include <stdio.h>
#include "graphics.h"

int main(int argc, char const *argv[]) {
	if (gfx_init() != 0) {
		return 1;
	}
	gfx_destroy();
	return 0;
}
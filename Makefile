CC = gcc
INCDIR = $(shell pwd)/SDL2/include
LIBDIR = $(shell pwd)/SDL2/i686-w64-mingw32/lib

all:
	$(CC) game.c graphics.c -o bin/game -I"$(INCDIR)" -L"$(LIBDIR)" -lmingw32 -lSDL2

clean:
	rm -rf dist

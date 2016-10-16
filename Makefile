CC = gcc -std=c99
INCDIR = $(shell pwd)/SDL2/include
LIBDIR = $(shell pwd)/SDL2/i686-w64-mingw32/lib
SOURCES = game.c graphics.c Timer.c

all:
	$(CC) $(SOURCES) -o bin/game -I"$(INCDIR)" -L"$(LIBDIR)" -lmingw32 -lSDL2main -lSDL2

clean:
	rm -rf bin
	mkdir bin
	cp "$(LIBDIR)/../bin/SDL2.dll" "bin/SDL2.dll"

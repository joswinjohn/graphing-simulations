SDL_C = `sdl2-config --cflags`
SDL_L = `sdl2-config --libs` -I/opt/homebrew/include/SDL2 -lm -lSDL2_ttf

CC = clang
CFLAGS = $(SDL_C)
LDFLAGS = -rpath /opt/homebrew/lib -L/opt/homebrew/lib $(SDL_L)

build_main:
	echo "Starting build process"
	$(CC) $(CFLAGS) $(LDFLAGS) src/main.c -o build/out

clean:
	rm -f build/out

run: build_main && ./build/out

.PHONY: clean run

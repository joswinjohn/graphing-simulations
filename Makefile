SDL_C = `sdl2-config --cflags`
SDL_L = `sdl2-config --libs` -I/opt/homebrew/include/SDL2 -lSDL2_ttf
GLM_L = -I/opt/homebrew/include/glm

CC = clang++
CFLAGS = $(SDL_C)
LDFLAGS = -rpath /opt/homebrew/lib -L/opt/homebrew/lib -lm $(SDL_L) $(GLM_L)

build_main:
	echo "Starting build process"
	if [ ! -d "build" ]; then mkdir build; fi
	$(CC) $(CFLAGS) $(LDFLAGS) src/main.cpp src/sdl.cpp src/shapes.cpp -o build/out

clean:
	rm -rf build

run: build_main
	./build/out

.PHONY: clean run

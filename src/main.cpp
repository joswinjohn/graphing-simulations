#include <cstdio>
#include <SDL.h>
#include <iostream>
#include "SDL_events.h"
#include "camera.hpp"
#include "shapes.hpp"
#include "sdl.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#define FONT_PATH       "/Users/joswinjohn/git/graphing-simulations/FreeMono.ttf"
#define FONT_SIZE       24

#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 600.0f

int main() {
    SDL_Context sdl;
    sdl.initialize_sdl(SCREEN_WIDTH, SCREEN_HEIGHT);

    Camera camera;
    camera.projection_matrix(45.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

    glm::mat4 model_mat = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
    model_mat = glm::translate(model_mat, glm::vec3(0.0f, 0.0f, 5.0f));

    Font freemono;
    freemono.initialize_ttf(FONT_PATH, FONT_SIZE);

    freemono.create_text(sdl.renderer, 200, 200, "goob");

    printf("Starting render loop\n");
    bool quit = false;
    while(!quit) {
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        camera.position.z += 0.1f;
                        break;
                    case SDLK_s:
                        camera.position.z -= 0.1f;
                        break;
                    case SDLK_d:
                        camera.position.x -= 0.1f;
                        break;
                    case SDLK_a:
                        camera.position.x += 0.1f;
                        break;
                    case SDLK_SPACE:
                        camera.position.y -= 0.1f;
                        break;
                    case SDLK_LCTRL:
                        camera.position.y += 0.1f;
                        break;
                    case SDLK_UP:
                        glm::quat rotation = glm::angleAxis(glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                        camera.rotation = rotation * camera.rotation;
                        break;
                }
            }

        }

        // set draw color
        SDL_SetRenderDrawColor(sdl.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // background
        sdl.set_background(0x00, 0x00, 0x00, 0xFF);

        glm::mat4 view_mat = glm::lookAt(
            camera.position,
            camera.position + camera.rotation,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 mvp = camera.proj_mat * view_mat * model_mat;

        Cube c;
        c.apply_mvp(mvp);
        c.window_transform(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));

        c.render_cube(sdl.renderer, 0, 0);

        freemono.render_text(sdl.renderer);

        SDL_RenderPresent(sdl.renderer);
    }

    TTF_Quit();
    return 0;
}

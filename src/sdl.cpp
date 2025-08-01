#include "sdl.hpp"
#include "SDL_render.h"
#include "SDL_ttf.h"

bool SDL_Context::initialize_sdl(int screen_width, int screen_height) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        fprintf(stderr, "SDL_Init failed with error: %s\n", SDL_GetError());
    return false;
    }
    printf("SDL2 initialized\n"); 

    window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          screen_width, screen_height,
                                          0);
    if(!window)
    {
        fprintf(stderr, "SDL_Window failed with error: %s\n", SDL_GetError());
        return false;
    }
    printf("SDL_Window initialized\n"); 

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fprintf(stderr, "SDL_Renderer failed with error: %s\n", SDL_GetError());
        return false;
    }
    printf("SDL_Renderer initialized\n");
    return true;
}

void SDL_Context::set_background(int r, int g, int b, int a) {
    Uint8 old_r, old_g, old_b, old_a;
    SDL_GetRenderDrawColor(renderer, &old_r, &old_g, &old_b, &old_a);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, old_r, old_g, old_b, old_a);
};

bool Font::initialize_ttf(std::string font_path, int size) {
    TTF_Init();
    font = TTF_OpenFont(font_path.c_str(), size);
    if (!font) {
        fprintf(stderr, "Couldn't find/init open ttf font.");
        return false;
    }

    printf("Loaded font: %s\n", font_path.c_str());
    return true;
}

void Font::create_text(SDL_Renderer* renderer, int x, int y, const char* msg) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, msg, text_color);
    if(!surface)
    {
        fprintf(stderr, "SDL_Surface failed with error: %s\n", SDL_GetError());
        return;
    }

    textures.push_back(SDL_CreateTextureFromSurface(renderer, surface));

    SDL_Rect rect{
        static_cast<int>(x - surface->w * 0.5),
        static_cast<int>(y - surface->h * 0.5),
        surface->w,
        surface->h,
    };
    rects.push_back(rect);

    SDL_FreeSurface(surface);
}

void Font::render_text(SDL_Renderer* renderer) {
    for (int i = 0; i < textures.size(); i++) {
        SDL_RenderCopy(renderer, textures[i], NULL, &rects[i]);
    }
}

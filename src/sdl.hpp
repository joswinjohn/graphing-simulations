#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

class SDL_Context {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool initialize_sdl(int screen_width, int screen_height);
    void set_background(int r, int g, int b, int a);
};
class Font {
public:
    std::vector<SDL_Texture*> textures;
    std::vector<SDL_Rect> rects;
    TTF_Font* font;
    SDL_Color text_color{255, 255, 255, 255};

    bool initialize_ttf(std::string font_path, int size);
    void create_text(SDL_Renderer* renderer, int x, int y, const char* msg);
    void render_text(SDL_Renderer* renderer);
};

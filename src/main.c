#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <stdio.h>
#include <stdbool.h>
#include <complex.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>

#define FONT_PATH       "/Users/joswinjohn/git/graphing-simulations/FreeMono.ttf"
#define FONT_SIZE       24

// non-square dimensions will warp your graph
#define SCREEN_WIDTH    1080
#define SCREEN_HEIGHT   720
#define MARGIN          40

#define GRAPH_WIDTH     (SCREEN_WIDTH-(MARGIN * 2))
#define GRAPH_HEIGHT    (SCREEN_HEIGHT-(MARGIN * 2))

#define GRAPH_BOUND_X   10
#define GRAPH_BOUND_Y   10

// havent tested varying values of MAX_TICKERS
#define MAX_TICKERS     10

#define FUNCTION        (cos(2*x)) / (pow(M_E, x) + 1)

#define VAL(str) #str
#define TOSTRING(str) VAL(str)

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Color text_color = { 255, 255, 255, 255};
TTF_Font* font;
SDL_Texture **textures;
SDL_Rect **rects;
uint16_t texture_index;
int point_buffer[GRAPH_WIDTH];
double factor;

Uint32 build_func(Uint32 m, void* n) {
    double x = -GRAPH_BOUND_X;
    for (int i = 0; i < GRAPH_WIDTH; i++) {
        point_buffer[i] = (int)(FUNCTION * factor * (GRAPH_WIDTH / 2.0) / GRAPH_BOUND_Y);
        x += (double) GRAPH_BOUND_X * 2 / GRAPH_WIDTH;
    }
    factor += 0.01;
    return 10;
}

void create_text(int x, int y, const char* Message) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, Message, text_color);
    textures[texture_index] = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = x - surface->w * 0.5;
    rect.y = y - surface->h * 0.5;
    rect.w = surface->w;
    rect.h = surface->h;

    rects[texture_index] = malloc(sizeof(rect));
    memcpy(rects[texture_index], &rect, sizeof(rect));
    texture_index++;

    SDL_FreeSurface(surface);
}

int main() {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        fprintf(stderr, "SDL_Init failed with error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    printf("SDL2 initialized\n"); 

    window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          0);
    if(!window)
    {
        fprintf(stderr, "SDL_Window failed with error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    printf("SDL_Window initialized\n"); 

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fprintf(stderr, "SDL_Renderer failed with error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    printf("SDL_Renderer initialized\n"); 

    // populate points
    factor = 1.0;
    build_func(1, &factor);
    printf("Populated points of function: %s\n", TOSTRING(FUNCTION));

    // Create textures for ticker labels
    TTF_Init();
    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        fprintf(stderr, "Couldn't find/init open ttf font.");
    }
    printf("Loaded font: %s\n", FONT_PATH);

    // FIXME
    // malloc does not allocate the correct amount of memory, for now its allocating excess to prevent seg fault
    textures = malloc(4 * MAX_TICKERS * sizeof(SDL_Texture *));
    rects = malloc(4 * MAX_TICKERS * sizeof(SDL_Rect *));

    // ticker labels for x axis
    for (int i = MARGIN, j = -GRAPH_BOUND_X; i <= SCREEN_WIDTH - MARGIN; i+=(GRAPH_WIDTH / 10), j+=(GRAPH_BOUND_X/(MAX_TICKERS/2))) {
        char d[8];
        sprintf(d, "%d", j);
        create_text(i + 20, (SCREEN_HEIGHT / 2) + 20, d);
    }

    // ticker labels for y axis
    for (int i = SCREEN_HEIGHT - MARGIN, j = -GRAPH_BOUND_Y; i >= MARGIN; i-=(GRAPH_HEIGHT / 10), j+=(GRAPH_BOUND_Y/(MAX_TICKERS/2))) {
        char d[8];
        sprintf(d, "%d", j);
        create_text((SCREEN_WIDTH / 2) + 20, i + 20, d);
    }

    printf("Generated ticker label text\n");
    TTF_Quit();

    // change cos factor
    SDL_TimerID factor_timer = SDL_AddTimer(100, build_func, &factor);

    // event loop
    printf("Starting render loop\n");
    bool quit = false;
    while(!quit)
    {
        SDL_Event e;

        if ( SDL_PollEvent( &e ) ) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        // background
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // graph x axis
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer, MARGIN, SCREEN_HEIGHT / 2, SCREEN_WIDTH - MARGIN, SCREEN_HEIGHT / 2);

        // graph y axis
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, MARGIN, SCREEN_WIDTH / 2, SCREEN_HEIGHT - MARGIN);
        
        // x axis tick marks
        for (int i = MARGIN; i <= SCREEN_WIDTH - MARGIN; i+=(GRAPH_WIDTH / 10)) {
            SDL_RenderDrawLine(renderer, i, (SCREEN_HEIGHT / 2) - 20, i, (SCREEN_HEIGHT / 2) + 20);
        }

        // y axis tick marks
        for (int i = MARGIN; i <= SCREEN_HEIGHT - MARGIN; i+=(GRAPH_HEIGHT / 10)) {
            SDL_RenderDrawLine(renderer, (SCREEN_WIDTH / 2) - 20, i, (SCREEN_WIDTH / 2) + 20, i);
        }

        // graph function
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        for (int i = 0; i < GRAPH_WIDTH-1; i++) {
            // SDL_RenderDrawPoint(renderer, i + MARGIN, (SCREEN_HEIGHT / 2) - point_buffer[i]);
            SDL_RenderDrawLine(renderer, i+MARGIN, (SCREEN_HEIGHT / 2) - point_buffer[i], i+MARGIN+1, (SCREEN_HEIGHT / 2) - point_buffer[i+1]);
        }

        // render text
        for (int i = 0; i < texture_index; i++) {
            SDL_RenderCopy(renderer, textures[i], NULL, rects[i]);
        }

        SDL_RenderPresent(renderer);
    }

    // exit cleanly
    for (int i = 0;  i < texture_index; i++) {
        SDL_DestroyTexture(textures[i]);
    }
    SDL_RemoveTimer(factor_timer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Exited SDL.\n");
    
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH  256
#define HEIGHT 144

struct {
    SDL_Window   *win;
    SDL_Renderer *ren;
    SDL_GameController *gpad;
} game;

// void sdlInit() { }
// void gameInit() { }
// void gameUpdate() { }

int main(int argc,char **argv) {
    // sdlInit();
    SDL_Init(SDL_INIT_VIDEO);

    game.win = SDL_CreateWindow(
            "Geary guy",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN |
            SDL_WINDOW_RESIZABLE);

    game.ren = SDL_CreateRenderer(
            game.win, -1, 0);
    SDL_RenderSetLogicalSize(game.ren, WIDTH, HEIGHT);

    // gameInit();
    SDL_Surface *bg_img = IMG_Load("res/geary-backing.png");
    SDL_Texture *bg_tex = SDL_CreateTextureFromSurface(game.ren, bg_img);
    SDL_FreeSurface(bg_img);

    SDL_Surface *player = IMG_Load("res/guy_sheet.png");
    SDL_Texture *p_tex = SDL_CreateTextureFromSurface(game.ren, player);
    SDL_FreeSurface(player);

    int scrollOff = 0;
    int count = 0;

    SDL_Rect dest; dest.w = WIDTH; dest.h = HEIGHT; dest.y = 0;
    SDL_Rect dest2; dest2.w = WIDTH; dest2.h = HEIGHT; dest2.y = 0;
    SDL_Rect p_src; p_src.y = 0; p_src.w = 32; p_src.h = 32;
    SDL_Rect p_dest; p_dest.x = 20; p_dest.y = 60; p_dest.w = 32; p_dest.h= 32;

    int quit = 0;
    while (!quit) {
        //gameUpdate();
        // Tic
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) { quit = 1; }
            if (e.key.keysym.scancode ==
                    SDL_SCANCODE_ESCAPE) {
                quit = 1;
            }
        }

        int frame = (SDL_GetTicks() / 150) % 7;
        p_src.x = frame * p_src.w;

        dest.x = scrollOff;
        dest2.x = scrollOff + WIDTH;

        count++;
        if (count == 7) { scrollOff--; count = 0; }
        if (scrollOff < -WIDTH) { scrollOff = 0; }

        // Draw
        SDL_RenderClear(game.ren);
        SDL_SetRenderDrawColor(game.ren, 0, 0, 0, 255);

        SDL_RenderCopy(game.ren, bg_tex, NULL, &dest);
        SDL_RenderCopy(game.ren , bg_tex, NULL, &dest2);

        SDL_RenderCopy(game.ren, p_tex, &p_src, &p_dest);

        SDL_RenderPresent(game.ren);
    }

    return 0;
}

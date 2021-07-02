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
    SDL_Surface *distant_img = IMG_Load("res/distant.png");
    SDL_Texture *distant_tex = SDL_CreateTextureFromSurface(game.ren, distant_img);
    SDL_FreeSurface(distant_img);

    SDL_Surface *near_img = IMG_Load("res/near.png");
    SDL_Texture *near_tex = SDL_CreateTextureFromSurface(game.ren, near_img);
    SDL_FreeSurface(near_img);

    SDL_Surface *ground_img = IMG_Load("res/ground.png");
    SDL_Texture *ground_tex = SDL_CreateTextureFromSurface(game.ren, ground_img);
    SDL_FreeSurface(ground_img);

    SDL_Surface *player = IMG_Load("res/guy_sheet.png");
    SDL_Texture *p_tex = SDL_CreateTextureFromSurface(game.ren, player);
    SDL_FreeSurface(player);

    int count = 0;

    SDL_Rect distant_dest ={ 0, 0, WIDTH, HEIGHT };

    int scrollnear = 0;
    SDL_Rect near_dest; near_dest.w = WIDTH; near_dest.h = 36; near_dest.y = 30;
    SDL_Rect near_dest2; near_dest2.w = WIDTH; near_dest2.h = 36; near_dest2.y = 30;

    int scrollground = 0;
    SDL_Rect ground_dest; ground_dest.w = WIDTH; ground_dest.h = HEIGHT; ground_dest.y = 0;
    SDL_Rect ground_dest2; ground_dest2.w = WIDTH; ground_dest2.h = HEIGHT; ground_dest2.y = 0;

    SDL_Rect p_src; p_src.y = 0; p_src.w = 32; p_src.h = 32;
    SDL_Rect p_dest; p_dest.x = 20; p_dest.y = 60; p_dest.w = 32; p_dest.h = 32;

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

        ground_dest.x = scrollground;
        ground_dest2.x = scrollground + WIDTH;
        near_dest.x = scrollnear;
        near_dest2.x = scrollnear + WIDTH;

        count++;
        if (count % 7== 0) { scrollground--; }
        else if (count % 20 == 0) { scrollnear--; }
        // else if (count == 140) {  count = 0;}

        if (scrollground < -WIDTH) { scrollground = 0; }
        if (scrollnear < -WIDTH) { scrollnear = 0; }

        // Draw
        SDL_RenderClear(game.ren);
        SDL_SetRenderDrawColor(game.ren, 0, 0, 0, 255);

        SDL_RenderCopy(game.ren, distant_tex, NULL, &distant_dest);

        SDL_RenderCopy(game.ren, near_tex, NULL, &near_dest);
        SDL_RenderCopy(game.ren , near_tex, NULL, &near_dest2);

        SDL_RenderCopy(game.ren, ground_tex, NULL, &ground_dest);
        SDL_RenderCopy(game.ren , ground_tex, NULL, &ground_dest2);

        SDL_RenderCopy(game.ren, p_tex, &p_src, &p_dest);

        SDL_RenderPresent(game.ren);
    }

    return 0;
}

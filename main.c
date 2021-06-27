#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH  256
#define HEIGHT 144

int main(int argc,char **argv) {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *win = SDL_CreateWindow(
            "Geary guy",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN |
            SDL_WINDOW_RESIZABLE);

    SDL_Renderer *ren = SDL_CreateRenderer(
            win, -1, 0);
    SDL_RenderSetLogicalSize(ren, WIDTH, HEIGHT);

    SDL_Surface *bg_img = IMG_Load("res/geary-backing.png");
    SDL_Texture *bg_tex = SDL_CreateTextureFromSurface(ren, bg_img);
    SDL_FreeSurface(bg_img);

    SDL_Surface *player = IMG_Load("res/guy_sheet.png");
    SDL_Texture *p_tex = SDL_CreateTextureFromSurface(ren, player);
    SDL_FreeSurface(player);
    int scrollOff = 0;

    SDL_Rect dest;
    dest.w = WIDTH;
    dest.h = HEIGHT;
    dest.y = 0;

    SDL_Rect dest2;
    dest2.w = WIDTH;
    dest2.h = HEIGHT;
    dest2.y = 0;


    SDL_Rect p_src;
    p_src.y = 0;
    p_src.w = 32;
    p_src.h = 32;

    SDL_Rect p_dest;
    p_dest.x = 20;
    p_dest.y = 60;
    p_dest.w = 32;
    p_dest.h= 32;

    /* SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h); */
    int quit = 0;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) { quit = 1; }
            if (e.key.keysym.scancode ==
                    SDL_SCANCODE_ESCAPE) {
                quit = 1;
            }
        }
        // animate
        int frame = (SDL_GetTicks() / 150) % 7;
        p_src.x = frame * p_src.w;

        // scroll bg
        dest.x = scrollOff;
        dest2.x = scrollOff + WIDTH;

        SDL_RenderClear(ren);
        /* SDL_SetRenderDrawColor(ren, 24, 156, 255, 255); */
        // bg
        --scrollOff;
        if (scrollOff < -WIDTH) {
            scrollOff = 0;
        }

        SDL_RenderCopy(ren, bg_tex, NULL, &dest);
        SDL_RenderCopy(ren , bg_tex, NULL, &dest2);
        // fg
        SDL_RenderCopy(ren, p_tex, &p_src, &p_dest);

        SDL_RenderPresent(ren);
    }
    SDL_Quit();
}

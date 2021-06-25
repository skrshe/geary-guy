#include <stdio.h>
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

    SDL_Rect dest;
    dest.w = WIDTH;
    dest.h = HEIGHT;
    dest.x = (WIDTH - dest.w) / 2;
    dest.y = (HEIGHT - dest.h) / 2;


    SDL_Rect p_dest = {20, 60, 32, 32};

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

        int frame = (SDL_GetTicks() / 150) % 7;
        SDL_Rect p_src = {frame * 32, 0, 32, 32};

        SDL_RenderClear(ren);
        /* SDL_SetRenderDrawColor(ren, 24, 156, 255, 255); */
        SDL_RenderCopy(ren, bg_tex, NULL, &dest);
        SDL_RenderCopy(ren, p_tex, &p_src, &p_dest);

        SDL_RenderPresent(ren);
    }
    SDL_Quit();
}

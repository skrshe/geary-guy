#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH  1920
#define HEIGHT 1080

int main(int argc,char **argv) {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *win = SDL_CreateWindow(
            "Geary guy",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            0);

    SDL_Renderer *ren = SDL_CreateRenderer(
            win, -1,
            0);

    SDL_Surface *surf = IMG_Load("res/geary.png");

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);

    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w *= 4;
    dest.h *= 4;
    dest.x = (WIDTH - dest.w) / 2;
    dest.y = (HEIGHT - dest.h) / 2;

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

        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 24, 156, 255, 255);
        SDL_RenderCopy(ren, tex, NULL, &dest);

        SDL_RenderPresent(ren);
    }
    SDL_Quit();
}

#include <SDL2/SDL.h>
/* #include <SDL2/SDL_image.h> */

#define WIDTH  800
#define HEIGHT 600

int main(int argc,char **argv) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow(
            "gearyguy",
            0, 0, WIDTH, HEIGHT,
            0);

    SDL_Renderer *ren = SDL_CreateRenderer(
            win, -1,
            0);

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

        SDL_SetRenderDrawColor(ren, 24, 156, 255, 255);
        SDL_RenderClear(ren);

        SDL_RenderPresent(ren);
    }
    SDL_Quit();
}

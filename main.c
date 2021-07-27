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

//struct Thing {
//    SDL_Surface *img;
//    SDL_Texture *tex;
//    SDL_FreeSurface(img);

//    SDL_Rect src = {0,0,0,0};
//    SDL_Rect dst = {0,0,0,0};
//    int scroll = 0;
//};

// void sdlInit() { }
// void gameInit() { }
// void gameUpdate() { }

int main(int argc, char **argv) {
    // sdlInit();
    // SDL_Init(SDL_INIT_VIDEO);

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

    SDL_Surface *far_img = IMG_Load("res/far.png");
    SDL_Texture *far_tex = SDL_CreateTextureFromSurface(game.ren, far_img);
    SDL_FreeSurface(far_img);

    SDL_Surface *near_img = IMG_Load("res/near.png");
    SDL_Texture *near_tex = SDL_CreateTextureFromSurface(game.ren, near_img);
    SDL_FreeSurface(near_img);

    SDL_Surface *ground_img = IMG_Load("res/ground.png");
    SDL_Texture *ground_tex = SDL_CreateTextureFromSurface(game.ren, ground_img);
    SDL_FreeSurface(ground_img);

    SDL_Surface *road_img = IMG_Load("res/road.png");
    SDL_Texture *road_tex = SDL_CreateTextureFromSurface(game.ren, road_img);
    SDL_FreeSurface(road_img);

    SDL_Surface *player = IMG_Load("res/guy_sheet.png");
    SDL_Texture *p_tex = SDL_CreateTextureFromSurface(game.ren, player);
    SDL_FreeSurface(player);


    SDL_Rect distant_dest = { 0, 0, WIDTH, HEIGHT };

    int scrollfar = 0;
    SDL_Rect far_dest  = { .w = WIDTH, .h = 60, .y = 5 };
    SDL_Rect far_dest2 = { .w = WIDTH, .h = 60, .y = 5 };

    int scrollnear = 0;
    SDL_Rect near_dest  = { .w = WIDTH, .h = 36, .y = 40 };
    SDL_Rect near_dest2 = { .w = WIDTH, .h = 36, .y = 40 };

    int scrollground = 0;
    SDL_Rect ground_dest  = { .w = WIDTH, .h = 95, .y = 49 };
    SDL_Rect ground_dest2 = { .w = WIDTH, .h = 95, .y = 49 };

    int scrollroad = 0;
    SDL_Rect road_dest  = { .w = 251, .h = 28, .y = 76 };
    SDL_Rect road_dest2 = { .w = 251, .h = 28, .y = 76 };
    SDL_Rect road_dest3 = { .w = 251, .h = 28, .y = 76 };

    SDL_Rect p_src  = {.x = 0, .y = 0, .w = 32, .h = 32 };
    SDL_Rect p_dest = {.x = 20, .y = 60, .w = 32, .h = 32 };

    int quit = 0;
    while (!quit) {
        //gameUpdate();
        // Tic
        const Uint32 start = SDL_GetTicks();
        int jump = 0;

        SDL_Event e;
        while (SDL_PollEvent(&e) > 0) {
            switch (e.type) {
                case SDL_QUIT: quit = 1; break;

                case SDL_KEYDOWN: {
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE: quit = 1; break;
                        case SDLK_SPACE: jump = 1; break;
                    }
                }
            }
        }

        // TODO(anu): fix jump
        // TODO(anu): fix animation

        int jumpheight = 0;

        if (jump) {
            jumpheight += 7;
            jump = 0;
        }

        if (jumpheight > 0) jumpheight--;
        p_dest.y = 60;// - jumpheight;

        if (p_src.x % 6 * p_src.w == 0) p_src.x = 0;

        far_dest.x = scrollfar; far_dest2.x = scrollfar + WIDTH;
        near_dest.x = scrollnear; near_dest2.x = scrollnear + WIDTH;
        ground_dest.x = scrollground; ground_dest2.x = scrollground + WIDTH;
        road_dest.x = scrollroad; road_dest2.x = scrollroad + road_dest.w;
        road_dest3.x = scrollroad + (road_dest.w * 2);

        int count; count++;
        if (count % 1 == 0)  scrollroad--;
        if (count % 1 == 0)  {
            scrollground--;
        }
        if (count % 5 == 0) {
            scrollnear--;
            p_src.x += p_src.w;
        }
        if (count % 17 == 0) scrollfar--;
        // else if (count == 140) {  count = 0;}

        if (scrollfar    < -WIDTH)       scrollfar = 0;
        if (scrollnear   < -WIDTH)       scrollnear = 0;
        if (scrollground < -WIDTH)       scrollground = 0;
        if (scrollroad   < -road_dest.w) scrollroad = 0;

        // Draw
        SDL_RenderClear(game.ren);
        SDL_SetRenderDrawColor(game.ren, 0, 0, 0, 255);

        SDL_RenderCopy(game.ren, distant_tex, NULL, &distant_dest);
        SDL_RenderCopy(game.ren, far_tex, NULL, &far_dest); SDL_RenderCopy(game.ren , far_tex, NULL, &far_dest2);
        SDL_RenderCopy(game.ren, near_tex, NULL, &near_dest); SDL_RenderCopy(game.ren , near_tex, NULL, &near_dest2);
        SDL_RenderCopy(game.ren, ground_tex, NULL, &ground_dest); SDL_RenderCopy(game.ren , ground_tex, NULL, &ground_dest2);
        SDL_RenderCopy(game.ren, road_tex, NULL, &road_dest); SDL_RenderCopy(game.ren, road_tex, NULL, &road_dest2); SDL_RenderCopy(game.ren, road_tex, NULL, &road_dest3);
        SDL_RenderCopy(game.ren, p_tex, &p_src, &p_dest);

        SDL_RenderPresent(game.ren);

        const Uint32 duration = SDL_GetTicks() - start;
        const Uint32 delta_time_ms = 1000 / 60;
        if (duration < delta_time_ms)
            SDL_Delay(delta_time_ms - duration);
    }
    SDL_Quit();
    return 0;
}

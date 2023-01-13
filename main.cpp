#include "Life.cpp"
#include <SDL2/SDL.h>
#include <vector>

#define WINDOW_WIDTH 1000
#define PIXEL_WIDTH 10

int main(void)
{
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    std::vector<std::vector<int>> seed{
        {51, 50}, {52, 50}, {50, 51}, {51, 51}, {52, 52}, {61, 60}, {62, 60}, {60, 61}, {61, 61}, {62, 62}, {71, 70}, {72, 70}, {70, 71}, {71, 71}, {72, 72}, {81, 80}, {82, 80}, {80, 81}, {81, 81}, {82, 82}};
    Life *life = new Life(seed, WINDOW_WIDTH / PIXEL_WIDTH, WINDOW_WIDTH / PIXEL_WIDTH);

    /*
    GLIDER:
    {1, 0});
    {2, 0});
    {0, 1});
    {1, 1});
    {2, 2});
    */
    /*
     R-PENTOMINO:
     {1, 0});
     {2, 0});
     {0, 1});
     {1, 1});
     {1, 2});
     */

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderPresent(renderer);

    int white[] = {255, 0, 0};
    int black[] = {0, 0, 0};

    int i{0};
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;

        life->render(white, black, PIXEL_WIDTH, WINDOW_WIDTH, renderer);

        SDL_RenderPresent(renderer);
        life->iterate();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
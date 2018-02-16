#undef main
#include <iostream>
using std::cin;
using std::endl;
using std::cout;

#include <cmath>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void drawTriangle(int a, int b, int c, SDL_Renderer *renderer);

int main1(int argc, char *args[])
{
    SDL_Window *gWindow = NULL;
    SDL_Renderer *gRenderer = NULL;

    int a = 0,  b =0, c=30;

//    cin >> a >> b >> c;

    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        gWindow = SDL_CreateWindow("tesT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow != NULL)
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer != NULL)
            {
                bool bRunning = true;
                SDL_Event e;
                while (bRunning)
                {
                    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                    SDL_RenderClear(gRenderer);

                    while (SDL_PollEvent(&e) != 0)
                    if (e.type == SDL_QUIT)
                        bRunning = false;

                    SDL_SetRenderDrawColor(gRenderer, 122, 134, 212, 255);
                    drawTriangle(a, b, c, gRenderer);
                    SDL_RenderPresent(gRenderer);
                }
                SDL_DestroyWindow(gWindow);
                SDL_DestroyRenderer(gRenderer);

                gWindow = NULL;
                gRenderer = NULL;

                SDL_Quit();
            }
        }
    }


    return 0;
}

void drawTriangle(int a, int b, int c, SDL_Renderer *renderer)
{
    double angA = 1 / cos((a*a - b*b - c*c) / 2 * b * c);
    double angB = 1 / cos((b*b - a*a - c*c) / 2 * a * c);
    double angC = 1 / cos((c*c - a*a - b*b) / 2 * a * b);

    // ?
}

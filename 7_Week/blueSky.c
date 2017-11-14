#include <SDL2/SDL.h>
void sky() {
    int w=640, h=480;
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    SDL_Window *window =
        SDL_CreateWindow("Sky", 100, 100, w, h, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    Uint32 skyBlue =
        SDL_MapRGB(surface->format, 200, 0, 0);
    SDL_FillRect(surface, NULL, skyBlue);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(10000);
    SDL_Quit();
}
int main() {
  sky();
  return 0;
}

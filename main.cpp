#include <hello.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

int main(int argc, char** argv) {
    Hello hello;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Quit();

    return 0;
}
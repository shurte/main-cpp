#include <hello.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

int main(int argc, char** argv) {
    Hello hello;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        SDL_WINDOW_OPENGL
    );

    SDL_GLContext context = SDL_GL_CreateContext(window);
    glewInit();
    SDL_GL_MakeCurrent(window, context);

    SDL_Event event;
    bool isRunning = true;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }

            glClearColor(0.0f, 0.67f, 0.67f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            SDL_GL_SwapWindow(window);
        }
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}
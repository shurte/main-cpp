#include <hello.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

#include <string>
#include <wtypes.h>

std::string getAppDirectory() {
    char* fileName = new char[1024];
    GetModuleFileName(nullptr, fileName, 1024);
    std::string directory(fileName);
    int lastSlash = directory.find_last_of('\\');
    directory = directory.substr(0, lastSlash);
    return directory;
}

int main(int argc, char** argv) {
    Hello hello;
    
    std::string directory = getAppDirectory();
    std::cout << directory.c_str() << '\n';

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
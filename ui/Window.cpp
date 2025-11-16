#include <Window.hpp>

#include <vector>

Window::Window() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(
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
}

Window::~Window() {
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

static unsigned int VAO[1];
static unsigned int VBO[1];

static float rectangle[] = {
    -0.25f, 0.75f, 0.0f,
    -0.25f, 0.25f, 0.0f,
    -0.75f, 0.25f, 0.0f,
    -0.75f, 0.75f, 0.0f,
};

static float rectangleTwo[] = {
    0.25f, 0.75f, 0.0f,
    0.25f, 0.25f, 0.0f,
    0.75f, 0.25f, 0.0f,
    0.75f, 0.75f, 0.0f,
};

static float triangle[] = {
    0.5f, -0.25f, 0.0f,
    0.25f, -0.75f, 0.0f,
    0.75f, -0.75f, 0.0f
};

struct GeometricObject {
    float* data;
    unsigned int size;
    unsigned int vertexSize;
};


void initObjects() {
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    // glEnableVertexAttribArray(0);
    // glBindVertexArray(0);
}

void drawObjects() {
    std::vector<GeometricObject> geometricObjects;

    GeometricObject objectOne;
    objectOne.data = rectangle;
    objectOne.size = sizeof(rectangle);
    objectOne.vertexSize = 4;

    geometricObjects.push_back(objectOne);

    GeometricObject objectTwo;
    objectTwo.data = rectangleTwo;
    objectTwo.size = sizeof(rectangleTwo);
    objectTwo.vertexSize = 4;

    geometricObjects.push_back(objectTwo);

    GeometricObject objectThree;
    objectThree.data = triangle;
    objectThree.size = sizeof(triangle);
    objectThree.vertexSize = 3;

    geometricObjects.push_back(objectThree);

    for (const GeometricObject& geometricObject : geometricObjects) {
        glBindVertexArray(VAO[0]);
        glBufferData(GL_ARRAY_BUFFER, geometricObject.size, geometricObject.data, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_POLYGON, 0, geometricObject.vertexSize);
        glBindVertexArray(0);
    }
}

void Window::update() {
    initObjects();

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

            drawObjects();

            SDL_GL_SwapWindow(window);
        }
    }
}

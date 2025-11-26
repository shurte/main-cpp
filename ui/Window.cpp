#include <Window.hpp>

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

void Window::initObjects() {
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
}

void Window::drawScene() {
    glClearColor(0.0f, 0.67f, 0.67f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawObjects();

    SDL_GL_SwapWindow(window);
}

void Window::drawObjects() {
    for (const GeometricObject& geometricObject : geometricObjects) {
        drawObject(geometricObject);
    }
}

void Window::drawObject(const GeometricObject& geometricObject) {
    glBindVertexArray(VAO[0]);
    glBufferData(GL_ARRAY_BUFFER, geometricObject.size, geometricObject.data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_POLYGON, 0, geometricObject.vertexSize);
    glBindVertexArray(0);
}

size_t getKeyEvent(const SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            return WINDOW_MOVE_UP;
        case SDLK_s:
            return WINDOW_MOVE_DOWN;
        case SDLK_a:
            return WINDOW_MOVE_LEFT;
        case SDLK_d:
            return WINDOW_MOVE_RIGHT;
    }
    return 0;
}

size_t getWindowEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            return WINDOW_EXIT;
        case SDL_MOUSEBUTTONDOWN:
            return WINDOW_MOUSE_DOWN;
        case SDL_MOUSEBUTTONUP:
            return WINDOW_MOUSE_UP;
        case SDL_KEYDOWN:
            return getKeyEvent(event);
    }
    return 0;
}

void Window::update() {
    SDL_Event event;
    currentEvent = 0;
    while (SDL_PollEvent(&event)) {
        currentEvent = getWindowEvent(event);
    }
}

void Window::setGeometricObjects(const std::vector<GeometricObject>& newGeometricObjects) {
    geometricObjects.clear();
    for (GeometricObject newGeometricObject : newGeometricObjects) {
        geometricObjects.push_back(newGeometricObject);
    }
}

size_t Window::getCurrentEvent() {
    return currentEvent;
}
#pragma once

#include <Game.hpp>
#include <GameObject.hpp>
#include <GeometricObject.hpp>
#include <Window.hpp>

#include <chrono>
using namespace std::chrono;
#include <vector>

#define WINDOW_SIZE_H 1200
#define WINDOW_SIZE_V 600

/**
 * The main controller that synchronizes the game logic and the UI.
 */
class Controller {
    public:
        Controller() 
            : window(WINDOW_SIZE_H, WINDOW_SIZE_V)
            , game() {

        }

        void run() {
            init();
            runLoop();
            finish();
        }
        
    private:
        void init();
        void runLoop();
        void finish();

        void updateWindow();
        void updateGame();

    private:
        Window window;
        Game game;
};
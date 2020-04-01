#include "game.h"
#include "graphics.h"
#include "input.h"
#include <SDL.h>

/* Game class
 * Holds all information for main game loop
 */

namespace{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
    Graphics graphics;
    SDL_Event event;
    Input input;

    int LAST_UPDATE_TIME = SDL_GetTicks();
    while (true) {
        input.beginNewFrame();

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                input.keyDownEvent(event);
            }
            else if (event.type == SDL_KEYUP) {
                input.keyUpEvent(event);
            }
            if (event.type == SDL_QUIT) {
                return;
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
            return;
        }

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        this->update(min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
    }
}

void Game::draw(Graphics& graphics) {

}

void Game::update(float elapsedTime) {

}

int Game::min(int a, int b) {
    if (b > a) {
        return a;
    }
    return b;
}
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "terrainGenerator.h"
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

    this->_map = Map(graphics);
    this->_observer = this->_map.getObserver();

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
            if (event.type == SDL_MOUSEWHEEL) {
                if (event.wheel.y > 0) {
                    input.scrolledUp = true;
                }
                if (event.wheel.y < 0) {
                    input.scrolledDown = true;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                input.mouseDownEvent(event);
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                input.mouseUpEvent(event);
            }
            if (event.type == SDL_QUIT) {
                return;
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
            return;
        }
        //else if (input.wasKeyPressed(SDL_SCANCODE_LEFT)) {
        //    this->_observer->moveX(-20);
        //}
        //else if (input.wasKeyPressed(SDL_SCANCODE_RIGHT)) {
        //    this->_observer->moveX(20);
        //}
        //else if (input.wasKeyPressed(SDL_SCANCODE_UP)) {
        //    this->_observer->moveY(-20);
        //}
        //else if (input.wasKeyPressed(SDL_SCANCODE_DOWN)) {
        //    this->_observer->moveY(20);
        //}
        //if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT) &&
        //    !input.isKeyHeld(SDL_SCANCODE_UP) && !input.isKeyHeld(SDL_SCANCODE_DOWN)) {
        //    //this->_cells.at(0).stopMoving();
        //}
        if (input.isMouseHeld()) {
            this->_observer->move(input.getMove());
        }
        if (input.mouseClicked()) {
            //TODO: this->_observer->activate(input.getClick());
        }
        if(input.scrolledUp){
            this->_observer->increase();
        }
        if (input.scrolledDown) {
            this->_observer->decrease();
        }

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        this->update(min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->draw(graphics);
    }
}

void Game::draw(Graphics& graphics) {
    graphics.clear();
    this->_observer->show();
    graphics.render();
}

void Game::update(float elapsedTime) {
    this->_map.update(elapsedTime);
}

int Game::min(int a, int b) {
    if (b > a) {
        return a;
    }
    return b;
}
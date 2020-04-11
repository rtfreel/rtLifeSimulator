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

    //TerrainGenerator tg = TerrainGenerator(graphics, 2048, 2048, 9, 1.85f);
    //this->_terrain = tg.getTerrain();
    this->_bg = GameObject(graphics, "source/sprites/background.png", 0, 0, 16, 80, 100, 100);
    this->_cells.push_back(Cell(graphics, 0, 0));

    //this->_back = Back(graphics, 0, 0);
    //for (int i = 0; i < 20; i++) {
    //    for (int j = 0; j < 10; j++) {
    //        this->_cells.push_back(Cell(graphics, 100 * i + 20, 100 * j + 20));
    //    }
    //}

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
        else if (input.wasKeyPressed(SDL_SCANCODE_LEFT)) {
            this->_cells.at(0).moveLeft();
        }
        else if (input.wasKeyPressed(SDL_SCANCODE_RIGHT)) {
            this->_cells.at(0).moveRight();
        }
        else if (input.wasKeyPressed(SDL_SCANCODE_UP)) {
            this->_cells.at(0).moveUp();
        }
        else if (input.wasKeyPressed(SDL_SCANCODE_DOWN)) {
            this->_cells.at(0).moveDown();
        }
        if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT) &&
            !input.isKeyHeld(SDL_SCANCODE_UP) && !input.isKeyHeld(SDL_SCANCODE_DOWN)) {
            this->_cells.at(0).stopMoving();
        }
        if (input.wasMousePressed(SDL_BUTTON_LEFT)) {
            //TODO: map moving
        }
        if (input.wasMouseReleased(SDL_BUTTON_LEFT)) {
            //TODO: map moving
        }
        if(input.scrolledUp){
            //this->_terrain->increase();
            this->_bg.increase();
            for (int i = 0; i < this->_cells.size(); i++) {
                this->_cells.at(i).increase();
            }
        }
        if (input.scrolledDown) {
            //this->_terrain->decrease();
            this->_bg.decrease();
            for (int i = 0; i < this->_cells.size(); i++) {
                this->_cells.at(i).decrease();
            }
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

    //this->_terrain->draw(graphics, 0, 0);
    this->_bg.draw(graphics, 0, 0);
    for (int i = 0; i < this->_cells.size(); i++) {
        this->_cells.at(i).draw(graphics);
    }

    graphics.render();
}

void Game::update(float elapsedTime) {
    //this->_terrain->update();
    this->_bg.update();
    for (int i = 0; i < this->_cells.size(); i++) {
        this->_cells.at(i).update(elapsedTime);
    }

}

int Game::min(int a, int b) {
    if (b > a) {
        return a;
    }
    return b;
}
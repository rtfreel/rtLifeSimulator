/* graphics.cpp
 * Holds all information dealing with graphics for the game
 */

#include "graphics.h"
#include <SDL.h>
#include <SDL_image.h>

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Life Simulator 1.0");
}

Graphics::~Graphics() {
    SDL_DestroyWindow(this->_window);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
    if (this->_spriteSheets.count(filePath) == 0) {
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect) {
    SDL_RenderCopy(this->_renderer, texture, sourceRect, destinationRect);
}

void Graphics::render() {
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return this->_renderer;
}
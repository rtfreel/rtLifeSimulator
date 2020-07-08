#include "minimap.h"
#include "globals.h"
#include "graphics.h"

Minimap::Minimap(){}

Minimap::Minimap(Graphics& graphics) :
    GameObject(graphics, "source/sprites/minimap.ppm", 0, 0, globals::MINIMAP_WIDTH, globals::MINIMAP_HEIGHT, globals::MINIMAP_X, globals::MINIMAP_Y) {
	this->_graphics = &graphics;
	this->_sourceRect.y = this->_sourceY;
	this->_sourceRect.x = this->_sourceX;
	this->_sourceRect.w = this->_sourceWidth;
	this->_sourceRect.h = this->_sourceHeight;
}

void Minimap::addCells(std::vector<Cell*> cells) {
	this->_cells = cells;
}

void Minimap::update() {}

void Minimap::draw(Graphics& graphics) {
	SDL_Rect destinationRectangle = { globals::MINIMAP_X, globals::MINIMAP_Y, globals::MINIMAP_WIDTH, globals::MINIMAP_HEIGHT };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
	for (int i = 0; i < this->_cells.size(); i++) {
		int x = globals::MINIMAP_X + (this->_cells.at(i)->getX() * globals::MINIMAP_WIDTH / globals::MAP_WIDTH);
		int y = globals::MINIMAP_Y + (this->_cells.at(i)->getY() * globals::MINIMAP_HEIGHT / globals::MAP_HEIGHT);
		int width = ((float)globals::MINIMAP_WIDTH / globals::MAP_WIDTH) * this->_cells.at(i)->getWidth();
		int height = ((float)globals::MINIMAP_HEIGHT / globals::MAP_HEIGHT) * this->_cells.at(i)->getHeight();
		SDL_SetRenderDrawColor(this->_graphics->getRenderer(), 255, 0, 0, 255);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				SDL_RenderDrawPoint(this->_graphics->getRenderer(), x + i, y + j);
			}
		}
		SDL_SetRenderDrawColor(this->_graphics->getRenderer(), 0, 0, 0, 0);
	}
}

#include "terrain.h"
#include "globals.h"
#include "graphics.h"

Terrain::Terrain() {}

Terrain::Terrain(Graphics& graphics, int width, int height) :
	GameObject(graphics, "source/sprites/terrain.ppm", 0, 0, width, height, 0, 0) {
	
}

void Terrain::setSource(int color) {
	this->_sourceRect.x = color + 1;
	this->_sourceRect.y = 0;
	this->_sourceRect.w = 1;
	this->_sourceRect.h = 1;
}
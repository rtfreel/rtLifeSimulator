#include "terrain.h"

Terrain::Terrain() {}

Terrain::Terrain(Graphics& graphics, int width, int height) :
	GameObject(graphics, "source/sprites/terrain.ppm", 0, 0, width, height, 0, 0) {

}
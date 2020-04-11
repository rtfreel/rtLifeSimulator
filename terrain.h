#ifndef TERRAIN_H
#define TERRAIN_H

#include "gameObject.h";
#include <string>

class Graphics;

class Terrain : public GameObject {
public:
	Terrain();
	Terrain(Graphics& graphics, int width, int height);

	int* _groundType;
};

#endif
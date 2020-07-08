#ifndef TERRAIN_H
#define TERRAIN_H

#include "gameObject.h";
#include <string>

class Graphics;

class Terrain : public GameObject {
public:
	Terrain();
	Terrain(Graphics& graphics, int width, int height);
	//Terrain(Graphics& graphics, int width, int height, float* noise);
	//void draw(Graphics& graphics, int x, int y, std::pair<int, int> topLeftOffset, std::pair<int, int>bottomRightOffset);

private:
	void setSource(int color);

	int _height, _width;
	float* _terrain;
};

#endif
#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include "terrain.h"

class Graphics;

class TerrainGenerator {
public:
	TerrainGenerator();
	TerrainGenerator(Graphics& graphics, int width, int height, int detalisation, float smoothness = 2.0f);

	Terrain* getTerrain();

private:
	void generateSeed();
	void generateNoise(int octaves, float bias);
	void print();

	int _w, _h;
	float* _seed;
	float* _noise;
	Terrain* _terrain;
};

#endif
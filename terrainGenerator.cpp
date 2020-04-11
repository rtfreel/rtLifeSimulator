#include "terrainGenerator.h"
#include <fstream>
#include <iostream>
#include <random>

TerrainGenerator::TerrainGenerator() {}

TerrainGenerator::TerrainGenerator(Graphics& graphics, int width, int height, int detalisation, float smoothness) : _w(width), _h(height) {
	this->_seed = new float[width * height];
	this->_noise = new float[width * height];
	generateSeed();
	generateNoise(detalisation, smoothness);
	print();
	this->_terrain = new Terrain(graphics, this->_w, this->_h);
}

void TerrainGenerator::generateSeed() {
	for (int i = 0; i < this->_h * this->_w; i++) {
		this->_seed[i] = (float)rand() / (float)RAND_MAX;
	}
}

void TerrainGenerator::generateNoise(int octaves, float bias) {

	//iterating over every point in the terrain
	for (int x = 0; x < this->_w; x++) {
		for (int y = 0; y < this->_h; y++) {

			float currentNoise = 0.0f;

			//importance of number we calculated for current octave
			float scale = 1.0f;

			//normalises noise in range of (0, 1)
			float rangeNormaliser = 0.0f;

			//octave - point in the seed array, we pay attention to
			for (int octave = 0; octave < octaves; octave++) {

				//pitch - distance between octaves
				int pitch = this->_w >> octave;

				int behindXOctave = (x / pitch) * pitch;
				int behindYOctave = (y / pitch) * pitch;

				int nextXOctave = (behindXOctave + pitch) % this->_w;		// (% width) makes us go to the first octave point if next is the last one
				int nextYOctave = (behindYOctave + pitch) % this->_w;		// width used again because we actually generate 1D horisontal noises

				//blend - distance to behind octave point
				float blendX = (float)(x - behindXOctave) / (float)pitch;
				float blendY = (float)(y - behindYOctave) / (float)pitch;

				//linear interpolation between li1 and li2
				float li1 = (1.0 - blendX) * _seed[behindYOctave * this->_w + behindXOctave] + blendX * _seed[behindYOctave * this->_w + nextXOctave];
				float li2 = (1.0 - blendX) * _seed[nextYOctave * this->_w + behindXOctave] + blendX * _seed[nextYOctave * this->_w + nextXOctave];
				currentNoise += (blendY * (li2 - li1) + li1) * scale;

				rangeNormaliser += scale;

				//decrease importance
				scale = scale / bias;
			}
			//set otput
			_noise[y * this->_w + x] = currentNoise / rangeNormaliser;
		}
	}
}

Terrain* TerrainGenerator::getTerrain() {
	return this->_terrain;
}

void TerrainGenerator::print() {
	std::ofstream img("source/sprites/terrain.ppm");
	img << "P3" << std::endl;
	img << this->_w << " " << this->_h << std::endl;
	img << "255" << std::endl;

	for (int x = 0; x < this->_w; x++) {
		for (int y = 0; y < this->_h; y++) {
			int pixel = (int)(this->_noise[y * this->_w + x] * 16.0f);
			int r = 0, g = 0, b = 0;
			switch (pixel) {
			case 0: r = 63; g = 72; b = 204; break;
			case 1: r = 31; g = 117; b = 218; break;
			case 2: r = 0; g = 162; b = 232; break;
			case 3: r = 77; g = 190; b = 231; break;

			case 4: r = 153; g = 217; b = 234; break;
			case 5: r = 196; g = 223; b = 205; break;
			case 6: r = 239; g = 228; b = 176; break;
			case 7: r = 247; g = 235; b = 88; break;

			case 8: r = 255; g = 242; b = 0; break;
			case 9:  r = 218; g = 236; b = 15; break;
			case 10: r = 181; g = 230; b = 29; break;
			case 11: r = 108; g = 204; b = 55; break;

			case 12: r = 34; g = 177; b = 76; break;
			case 13: r = 17; g = 153; b = 38; break;
			case 14: r = 0; g = 128; b = 0; break;
			case 15: r = 128; g = 64; b = 64; break;

			case 16: r = 255; g = 255; b = 255; break;
			}
			img << r << " " << g << " " << b << std::endl;
		}
	}
}
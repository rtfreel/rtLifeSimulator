#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>

namespace globals {
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 800;

	const int SCALE_LIMIT = 20;
	const double SCALE_MULTIPLIER = 1.1892071150027;

	const int MAP_WIDTH = 2048;
	const int MAP_HEIGHT = 2048;

	const int MINIMAP_WIDTH = 256;
	const int MINIMAP_HEIGHT = 256;
	const int MINIMAP_X = 1331;
	const int MINIMAP_Y = 13;

	const std::vector<std::string> CELL_ANIMATIONS = {
		"source/sprites/blue_cell.png",
		"source/sprites/brown_cell.png",
		"source/sprites/green_cell.png",
		"source/sprites/grey_cell.png",
		"source/sprites/red_cell.png",
		"source/sprites/purple_cell.png",
		"source/sprites/yellow_cell.png"
	};
}

struct Vector2 {
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}
	Vector2 zero() {
		return Vector2(0, 0);
	}
};

struct Vector2D {
	float x, y;
	Vector2D() : x(0), y(0) {}
	Vector2D(float x, float y) : x(x), y(y) {}
	void reset() {
		x = 0.0f;
		y = 0.0f;
	}
	void add(Vector2D vector) {
		x = x + vector.x;
		y = y + vector.y;
	}
};

#endif
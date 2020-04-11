#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>

namespace globals {
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 800;

	const float SCALE_MULTIPLIER = 1.58489f;

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

#endif
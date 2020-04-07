#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 800;

	const float SCALE_MULTIPLIER = 1.58489f;
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
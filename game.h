#ifndef GAME_H
#define GAME_H

#include "gameObject.h"
#include "cell.h"
#include "terrain.h"
#include <vector>

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics& graphics);
	void update(float elapsedTime);
	int min(int a, int b);

	GameObject _bg;
	//Terrain* _terrain;
	std::vector<Cell> _cells;
};

#endif
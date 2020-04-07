#ifndef GAME_H
#define GAME_H

#include "gameObject.h"
#include "animatedGameObject.h"

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
	AnimatedGameObject _cell;
};

#endif
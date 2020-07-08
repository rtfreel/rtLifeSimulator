#ifndef CELL_H
#define CELL_H

#include "animatedGameObject.h"
#include <string>

class Graphics;

class Cell : public AnimatedGameObject {
public:
	Cell();
	Cell(Graphics& graphics, float x, float y);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();
private:
	std::string getRandomColor();

	float _dx = 0, _dy = 0;
};

#endif
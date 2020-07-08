#include "cell.h"
#include "graphics.h"
#include "globals.h"

Cell::Cell(){}

Cell::Cell(Graphics& graphics, float x, float y) :
	AnimatedGameObject(graphics, getRandomColor(), 0, 0, 16, 16, x, y, 100) {
	this->setupAnimations();
	this->playAnimation("Breathing", rand() % 22);
}

void Cell::setupAnimations() {
	//TODO: more animations
	this->addAnimation(22, 0, 0, "Breathing", 16, 16, Vector2(0, 0));
}

void Cell::animationDone(std::string currentAnimation) {}

//TODO: rewrite all
void Cell::moveLeft() {
	this->_dx = -0.2f;
}

void Cell::moveRight() {
	this->_dx = 0.2f;
}

void Cell::moveUp() {
	this->_dy = -0.2f;
}

void Cell::moveDown() {
	this->_dy = 0.2f;
}

void Cell::stopMoving() {
	this->_dx = 0;
	this->_dy = 0;
}

void Cell::update(float elapsedTime) {
	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;

	int tmp1 = (int)((float)rand() / RAND_MAX * 2);
	int tmp2 = (int)((float)rand() / RAND_MAX * 2);
	switch (tmp1) {
	case 0: moveLeft();
		break;
	case 1:	moveRight();
		break;
	}
	switch (tmp2) {
	case 0: moveUp();
		break;
	case 1:	moveDown();
		break;
	}

	AnimatedGameObject::update(elapsedTime);
}

std::string Cell::getRandomColor(){
	return globals::CELL_ANIMATIONS[rand() % globals::CELL_ANIMATIONS.size()];
}
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
	this->_acc.x = -0.002f;
}

void Cell::moveRight() {
	this->_acc.x = 0.002f;
}

void Cell::moveUp() {
	this->_acc.y = -0.002f;
}

void Cell::moveDown() {
	this->_acc.y = 0.002f;
}

void Cell::stopMoving() {
	this->_vel.reset();
}

void Cell::update(float elapsedTime) {
	this->_vel.add(this->_acc);
	this->_acc.reset();

	this->_x += this->_vel.x * elapsedTime;
	this->_y += this->_vel.y * elapsedTime;

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
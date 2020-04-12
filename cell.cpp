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

	AnimatedGameObject::update(elapsedTime);
}

std::string Cell::getRandomColor(){
	return globals::CELL_ANIMATIONS[rand() % globals::CELL_ANIMATIONS.size()];
}
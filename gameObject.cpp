#include "gameObject.h"
#include "graphics.h"
#include "globals.h"
#include <cmath>

//TODO: add actual and visible x y positions

GameObject::GameObject() {}

GameObject::GameObject(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) :
	_x(posX), _y(posY) {		//_x(posX - (width/2)), _y(posY - (height / 2)) {
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h= height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
	}
}

GameObject::~GameObject() {}

void GameObject::draw(Graphics &graphics, int x, int y) {
	SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w * pow(globals::SCALE_MULTIPLIER, this->_sizePower), this->_sourceRect.h * pow(globals::SCALE_MULTIPLIER, this->_sizePower) };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void GameObject::update() {}

void GameObject::increase() {
	if (_sizePower < 10) {
		this->_sizePower++;
	}
	else {
		this->_sizePower = 10;
	}
}

void GameObject::decrease() {
	if (_sizePower > 0) {
		this->_sizePower--;
	}
	else {
		this->_sizePower = 0;
	}
}
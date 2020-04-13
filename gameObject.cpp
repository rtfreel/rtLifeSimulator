#include "gameObject.h"
#include "graphics.h"
#include "globals.h"
#include <cmath>

//TODO: add actual and visible x y positions

GameObject::GameObject() {}

GameObject::GameObject(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) :
	_x(posX), _y(posY), _sourceX(sourceX), _sourceY(sourceY), _sourceWidth(width), _sourceHeight(height) {
	//this->_sourceRect.x = sourceX;
	//this->_sourceRect.y = sourceY;
	//this->_sourceRect.w = width;
	//this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
	}
}

GameObject::~GameObject() {}

void GameObject::draw(Graphics &graphics, int x, int y, std::pair<int, int> topLeftOffset, std::pair<int, int> botRightOffset) {
	//top-left ofsetting
	if(topLeftOffset.first > 0)
		this->_sourceRect.x = _sourceX + topLeftOffset.first;
	if (topLeftOffset.second > 0) 
		this->_sourceRect.y = _sourceY + topLeftOffset.second;
	this->_sourceRect.w = _sourceWidth - abs(topLeftOffset.first);
	this->_sourceRect.h = _sourceHeight - abs(topLeftOffset.second);

	//bottom-right offsetting
	if (botRightOffset.first > 0)
		this->_sourceRect.w -= botRightOffset.first;
	if (botRightOffset.second > 0)
		this->_sourceRect.h -= botRightOffset.second;
	SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w * pow(globals::SCALE_MULTIPLIER, this->_scale), this->_sourceRect.h * pow(globals::SCALE_MULTIPLIER, this->_scale) };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void GameObject::update() {}

float GameObject::getX() {
	return this->_x;
}

float GameObject::getY() {
	return this->_y;
}

int GameObject::getWidth() {
	return this->_sourceWidth;
}

int GameObject::getHeight() {
	return this->_sourceHeight;
}

void GameObject::increase() {
	if (this->_scale < globals::SCALE_LIMIT) {
		this->_scale++;
	}
	else {
		this->_scale = globals::SCALE_LIMIT;
	}
}

void GameObject::decrease() {
	if (this->_scale > 0) {
		this->_scale--;
	}
	else {
		this->_scale = 0;
	}
}
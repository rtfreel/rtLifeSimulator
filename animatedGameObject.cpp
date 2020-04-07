#include "animatedGameObject.h"
#include "graphics.h"

AnimatedGameObject::AnimatedGameObject() {}

AnimatedGameObject::AnimatedGameObject(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate):
	GameObject(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
	_frameIndex(0),
	_timeToUpdate(timeToUpdate),
	_visible(true), 
	_currentAnimationOnce(false),
	_currentAnimation("") {}

void AnimatedGameObject::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++) {
		SDL_Rect newRect = { (i + x) * width, y, width, height };
		rectangles.push_back(newRect);
	}
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedGameObject::resetAnimations() {
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedGameObject::playAnimation(std::string animation, bool once) {
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation) {
		this->_currentAnimation = animation;
		//TODO: random if needed
		this->_frameIndex = 0;
	}
}

void AnimatedGameObject::setVisible(bool visible) {
	this->_visible = visible;
}

void AnimatedGameObject::stopAnimation() {
	this->_frameIndex = 0;
	this->animationDone(this->_currentAnimation);
}

void AnimatedGameObject::update(int elapsedTime) {
	GameObject::update();
	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_timeToUpdate) {
		this->_timeElapsed -= _timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1) {
			this->_frameIndex++;
		}
		else {
			if (this->_currentAnimationOnce) {
				this->setVisible(false);
			}
			this->_frameIndex = 0;
			this->animationDone(this->_currentAnimation);
		}
	}
}

void AnimatedGameObject::draw(Graphics& graphics, int x, int y) {
	if (this->_visible) {
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w = this->_sourceRect.w * pow(globals::SCALE_MULTIPLIER, 6);
		destinationRectangle.h = this->_sourceRect.h * pow(globals::SCALE_MULTIPLIER, 6);

		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
	}
}

void AnimatedGameObject::animationDone(std::string animation) {

};

void AnimatedGameObject::setupAnimations() {
	this->addAnimation(22, 0, 0, "Breathing", 16, 16, Vector2(0, 0));
}

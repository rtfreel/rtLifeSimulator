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

void AnimatedGameObject::playAnimation(std::string animation, int frame, bool once) {
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation) {
		this->_currentAnimation = animation;
		this->_frameIndex = frame;
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

void AnimatedGameObject::draw(Graphics& graphics, int x, int y, std::pair<int, int> topLeftOffset, std::pair<int, int> botRightOffset) {
	if (this->_visible) {
		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];

		//top-left ofsetting
		if (topLeftOffset.first > 0) {
			this->_sourceRect.x = _sourceX + topLeftOffset.first;
			sourceRect.x += topLeftOffset.first;
		}
		if (topLeftOffset.second > 0) {
			this->_sourceRect.y = _sourceY + topLeftOffset.second;
			sourceRect.y += topLeftOffset.second;
		}
		this->_sourceRect.w = _sourceWidth - abs(topLeftOffset.first);
		this->_sourceRect.h = _sourceHeight - abs(topLeftOffset.second);
		sourceRect.w -= abs(topLeftOffset.first);
		sourceRect.h -= abs(topLeftOffset.second);

		//bottom-right offsetting
		if (botRightOffset.first > 0) {
			this->_sourceRect.w -= botRightOffset.first;
			sourceRect.w -= botRightOffset.first;
		}
		if (botRightOffset.second > 0) {
			this->_sourceRect.h -= botRightOffset.second;
			sourceRect.h -= botRightOffset.second;
		}

		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w = this->_sourceRect.w * pow(globals::SCALE_MULTIPLIER, this->_scale);
		destinationRectangle.h = this->_sourceRect.h * pow(globals::SCALE_MULTIPLIER, this->_scale);

		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
	}
}

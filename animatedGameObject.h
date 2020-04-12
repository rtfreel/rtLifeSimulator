#ifndef ANIMATED_GAME_OBJECT_H
#define ANIMATED_GAME_OBJECT_H

#include "gameObject.h"
#include "globals.h"
#include <string>
#include <map>
#include <vector>

class Graphics;

class AnimatedGameObject : public GameObject{
public:
	AnimatedGameObject();
	AnimatedGameObject(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);

	void playAnimation(std::string animation, int frame = 0, bool once = false );
	void update(int elapsedTime);
	void draw(Graphics &graphics, int x, int y, std::pair<int, int> topLeftOffset, std::pair<int, int> bottomRightOffset);

protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);
	void resetAnimations();
	void stopAnimation();
	void setVisible(bool visible);

	virtual void animationDone(std::string currentAnimation) = 0;
	virtual void setupAnimations() = 0;

private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed = 0;
	bool _visible;
};

#endif
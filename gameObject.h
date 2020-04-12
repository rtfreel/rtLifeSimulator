#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <string>

class Graphics;

class GameObject {
public:
	GameObject();
	GameObject(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);
	
	virtual ~GameObject();
	virtual void update();
	void draw(Graphics& graphics, int x, int y, std::pair<int, int> topLeftOffset, std::pair<int, int>bottomRightOffset);

	float getX();
	float getY();
	int getWidth();
	int getHeight();

	void increase();
	void decrease();

protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	float _x, _y;
	int  _sourceX, _sourceY, _sourceWidth, _sourceHeight;
	int _scale = 0;

private:
};

#endif
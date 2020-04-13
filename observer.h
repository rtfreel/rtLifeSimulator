#ifndef OBSERVER_H
#define OBSERVER_H

#include "terrain.h"
#include "cell.h"

class Graphics;

class Observer {
public:
	Observer();
	Observer(Graphics& graphics, float x, float y, int width, int height);

	void addTerrain(Terrain* terrain);
	void addObject(GameObject* object);
	void addAnimatedObject(AnimatedGameObject* animatedObject);
	void addCell(Cell* cell);

	void increase();
	void decrease();
	void show();
	void update();

	float x, y;
	int w, h;

private:
	void clear();
	template <typename T>
	void drawObject(T* object);
	
	int _scale = 0;
	int _unscaledWidth, _unscaledHeight;
	float _unscaledX, _unscaledY;
	Graphics* _graphics;
	Terrain* _terrain;
	std::vector<GameObject*> _objects;
	std::vector<AnimatedGameObject*> _animatedObjects;
	std::vector<Cell*> _cells;
};

#endif
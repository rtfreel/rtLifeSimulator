#ifndef OBSERVER_H
#define OBSERVER_H

#include "terrain.h"
#include "cell.h"

class Graphics;

class Observer {
public:
	Observer(Graphics& graphics, float x, float y, int width, int height);

	void addTerrain(Terrain* terrain);
	void addObject(GameObject* object);
	void addAnimatedObject(AnimatedGameObject* animatedObject);
	void addCell(Cell* cell);

	void increase();
	void decrease();
	void show();

	float x, y;
	int w, h;

private:
	void clear();
	void drawObject();
	
	int _scale = 0;
	Graphics& _graphics;
	Terrain* _terrain;
	std::vector<GameObject*> _objects;
	std::vector<AnimatedGameObject*> _animatedObjects;
	std::vector<Cell*> _cells;
};

#endif
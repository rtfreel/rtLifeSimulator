#ifndef MAP_H
#define MAP_H

#include "cell.h"
#include "observer.h"
#include <vector>

//Controls everything on the playground

class Map {
public:
	Map();
	Map(Graphics& graphics, int width = 2048, int height = 2048);

	void update(float elapsedTime);
	Observer* getObserver();

private:

	void updateObserver();

	int _width, _height;
	Observer* _observer;
	Terrain* _terrain;
	std::vector<GameObject*> _objects;
	std::vector<AnimatedGameObject*> _animatedObjects;
	std::vector<Cell*> _cells;
};

#endif
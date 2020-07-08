#ifndef MAP_H
#define MAP_H

#include "cell.h"
#include "observer.h"
#include "globals.h"
#include <vector>

//Controls everything on the playground

class Map {
public:
	Map();
	Map(Graphics& graphics, int width = globals::MAP_WIDTH, int height = globals::MAP_HEIGHT);

	void update(float elapsedTime);
	Observer* getObserver();

private:

	void updateObserver();
	bool isVisible(GameObject *object);

	int _width, _height;
	Observer* _observer;
	Minimap* _minimap;
	Terrain* _terrain;
	std::vector<GameObject*> _objects;
	std::vector<AnimatedGameObject*> _animatedObjects;
	std::vector<Cell*> _cells;
};

#endif
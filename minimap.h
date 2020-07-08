#ifndef MINIMAP_H
#define MINIMAP_H

#include "cell.h"
#include <memory>

class Graphics;

class Minimap : public GameObject{
public:
	Minimap();
	Minimap(Graphics& graphics);

	void addCells(std::vector<Cell*> cells);

	void update();
	void draw(Graphics& graphics);

private:
	Graphics* _graphics;
	std::vector<Cell*> _cells;
};

#endif
#include "map.h"
#include "terrainGenerator.h"

Map::Map(){}

Map::Map(Graphics& graphics, int width, int height) : _width(width), _height(height){
	this->_observer = new Observer(graphics, (width - globals::SCREEN_WIDTH) / 2.0f, (height - globals::SCREEN_HEIGHT) / 2.0f, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
	for (int i = 0; i < 200; i++) {
		Cell* cell = new Cell(graphics, rand() % globals::MAP_WIDTH, rand() % globals::MAP_HEIGHT);
		cell->setXWraparound(0, width);
		cell->setYWraparound(0, height);
		this->_cells.push_back(cell);
	}

	//Generate new file (takes time)
	//TerrainGenerator generator = TerrainGenerator(graphics, width, height, 9, 1.95f);
	//this->_terrain = generator.getTerrain();
	//this->_minimap = generator.getMinimap();

	//Generate from existing file
	this->_terrain = new Terrain(graphics, width, height);
	this->_minimap = new Minimap(graphics);

	this->_minimap->addCells(this->_cells);
}

Observer* Map::getObserver() {
	return this->_observer;
}

void Map::update(float elapsedTime) {
	this->_terrain->update();
	this->_minimap->update();
	for (GameObject* object : this->_objects) { object->update(); }
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { animatedObject->update(elapsedTime); }
	for (Cell* cell : this->_cells) { cell->update(elapsedTime); }
	this->updateObserver();
}

void Map::updateObserver() {
	this->_observer->update();
	this->_observer->addTerrain(this->_terrain);
	this->_observer->addMinimap(this->_minimap);
	for (GameObject* object : this->_objects) { if (isVisible(object)) { this->_observer->addObject(object); }}
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { if (isVisible(animatedObject)) { this->_observer->addAnimatedObject(animatedObject); }}
	for (Cell* cell : this->_cells) { if (isVisible(cell)) { this->_observer->addCell(cell); }}
}

bool Map::isVisible(GameObject *object) {
	return true;
}
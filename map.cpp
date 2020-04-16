#include "map.h"
#include "terrainGenerator.h"

Map::Map(){}

Map::Map(Graphics& graphics, int width, int height) : _width(width), _height(height){
	this->_observer = new Observer(graphics, (width - globals::SCREEN_WIDTH) / 2.0f, (height - globals::SCREEN_HEIGHT) / 2.0f, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
	//TerrainGenerator generator = TerrainGenerator(graphics, width, height, 9, 1.95f);
	//this->_terrain = generator.getTerrain();
	this->_terrain = new Terrain(graphics, width, height);
	this->_cells.push_back(new Cell(graphics, 1024, 1024));
}

Observer* Map::getObserver() {
	return this->_observer;
}

void Map::update(float elapsedTime) {
	this->_terrain->update();
	for (GameObject* object : this->_objects) { object->update(); }
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { animatedObject->update(elapsedTime); }
	for (Cell* cell : this->_cells) { cell->update(elapsedTime); }
	this->updateObserver();
}

void Map::updateObserver() {
	this->_observer->update();
	this->_observer->addTerrain(this->_terrain);
	for (GameObject* object : this->_objects) { this->_observer->addObject(object); }
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { this->_observer->addAnimatedObject(animatedObject); }
	for (Cell* cell : this->_cells) { this->_observer->addCell(cell); }
}
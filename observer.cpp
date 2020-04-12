#include "observer.h"
#include "globals.h"

Observer::Observer(Graphics& graphics, float x, float y, int width, int height) : 
	_graphics(graphics), x(x), y(y), w(width), h(height) {

}

void Observer::addTerrain(Terrain* terrain) {
	this->_terrain = terrain;
}

void Observer::addObject(GameObject* object) {
	this->_objects.push_back(object);
}

void Observer::addAnimatedObject(AnimatedGameObject* animatedObject) {
	this->_objects.push_back(animatedObject);
}

void Observer::addCell(Cell* cell) {
	this->_cells.push_back(cell);
}

void Observer::increase() {
	this->_terrain->increase();
	for (GameObject* object : this->_objects) { object->increase(); }
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { animatedObject->increase(); }
	for (Cell* cell : this->_cells) { cell->increase(); }
}

void Observer::decrease() {
	this->_terrain->decrease();
	for (GameObject* object : this->_objects) { object->decrease(); }
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { animatedObject->decrease(); }
	for (Cell* cell : this->_cells) { cell->decrease(); }
}

void Observer::show() {
	int objX = 0, objY = 0;

	//difference between exteme points of object and observer
	std::pair<float, float> topLeftBlend (0.0f, 0.0f);

	//offsets of source image
	std::pair<int, int> topLeftOffset (0, 0);
	std::pair<int, int> botRightOffset (0, 0);

	topLeftBlend.first = this->_terrain->getX() - x;
	topLeftBlend.second = this->_terrain->getY() - y;
	if (topLeftBlend.first < 0)
		topLeftOffset.first = abs(topLeftBlend.first);
	else {
		objX = topLeftBlend.first * pow(globals::SCALE_MULTIPLIER, this->_scale);
	}
	if (topLeftBlend.second < 0)
		topLeftOffset.second = abs(topLeftBlend.second);
	else {
		objY = topLeftBlend.second * pow(globals::SCALE_MULTIPLIER, this->_scale);
	}
	//right point of the						object							  observer
	botRightOffset.first = (this->_terrain->getX() + this->_terrain->getWidth()) - (x + w);
	botRightOffset.second = (this->_terrain->getY() + this->_terrain->getHeight()) - (y + h);

	this->_terrain->draw(_graphics, objX, objY, topLeftOffset, botRightOffset);

	clear();
}

void Observer::drawObject() {

}

void Observer::clear() {
	this->_terrain = nullptr;
	this->_objects.clear();
	this->_animatedObjects.clear();
	this->_cells.clear();
}
#include "observer.h"
#include "globals.h"
#include <cmath>

Observer::Observer(){}

Observer::Observer(Graphics& graphics, float x, float y, int width, int height) : 
	_graphics(&graphics), x(x), y(y), _unscaledWidth(width), _unscaledHeight(height), _unscaledX(x), _unscaledY(y){
	this->w = width;
	this->h = height;
	this->x = x;
	this->y = y;
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

void Observer::addMinimap(Minimap* minimap) {
	this->_minimap = minimap;
}

void Observer::move(std::pair<int, int> move) {
	this->_unscaledX += move.first / pow(globals::SCALE_MULTIPLIER, this->_scale);
	this->_unscaledY += move.second / pow(globals::SCALE_MULTIPLIER, this->_scale);
}

void Observer::increase() {
	if (this->_scale < globals::SCALE_LIMIT) {
		this->_scale++;
	}
	else {
		this->_scale = globals::SCALE_LIMIT;
	}
	this->_terrain->increase();
	for (GameObject* object : this->_objects) { object->setScale(this->_scale); }
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { animatedObject->setScale(this->_scale); }
	for (Cell* cell : this->_cells) { cell->setScale(this->_scale); }
}

void Observer::decrease() {
	if (this->_scale > 0) {
		this->_scale--;
	}
	else {
		this->_scale = 0;
	}
	this->_terrain->decrease();
	for (GameObject* object : this->_objects) { object->setScale(this->_scale); }
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { animatedObject->setScale(this->_scale); }
	for (Cell* cell : this->_cells) { cell->setScale(this->_scale); }
}

void Observer::show() {
	this->drawObject<Terrain>(this->_terrain);
	for (GameObject* object : this->_objects) { this->drawObject<GameObject>(object); }
	for (AnimatedGameObject* animatedObject : this->_animatedObjects) { this->drawObject<AnimatedGameObject>(animatedObject); }
	for (Cell* cell : this->_cells) { this->drawObject<Cell>(cell); }
	
	this->_minimap->draw(*this->_graphics);
}

template <typename T>
void Observer::drawObject(T* object) {
	int objX = 0, objY = 0;

	//difference between exteme points of object and observer
	std::pair<float, float> topLeftBlend(0.0f, 0.0f);

	//offsets of source image
	std::pair<int, int> topLeftOffset(0, 0);
	std::pair<int, int> botRightOffset(0, 0);

	topLeftBlend.first = object->getX() - x;
	topLeftBlend.second = object->getY() - y;
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
	//right point of the				object					  observer
	botRightOffset.first = (object->getX() + object->getWidth()) - (x + w);
	botRightOffset.second = (object->getY() + object->getHeight()) - (y + h);

	object->draw(*this->_graphics, objX, objY, topLeftOffset, botRightOffset);
}

void Observer::update() {
	clear();
	this->w = std::ceil(this->_unscaledWidth / pow(globals::SCALE_MULTIPLIER, _scale));
	this->h = std::ceil(this->_unscaledHeight / pow(globals::SCALE_MULTIPLIER, _scale));
	this->x = this->_unscaledX + (this->_unscaledWidth - this->w) / 2;
	this->y = this->_unscaledY + (this->_unscaledHeight - this->h) / 2;
}

void Observer::clear() {
	this->_terrain = nullptr;
	this->_minimap = nullptr;
	this->_objects.clear();
	this->_animatedObjects.clear();
	this->_cells.clear();
}
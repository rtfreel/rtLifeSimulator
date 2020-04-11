#include "input.h"
#include <SDL.h>

void Input::beginNewFrame() {
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
	this->_pressedMouseButtons.clear();
	this->_releasedMouseButtons.clear();
	this->scrolledUp = false;
	this->scrolledDown = false;
}

void Input::keyUpEvent(const SDL_Event& event) {
	this->_releasedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = false;
}

void Input::keyDownEvent(const SDL_Event& event) {
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = true;
}

void Input::mouseUpEvent(const SDL_Event& event) {
	this->_releasedMouseButtons[event.button.button] = true;
	this->_heldMouseButtons[event.button.button] = false;
}

void Input::mouseDownEvent(const SDL_Event& event) {
	this->_pressedMouseButtons[event.button.button] = true;
	this->_heldMouseButtons[event.button.button] = true;
}

bool Input::isKeyHeld(SDL_Scancode key) {
	return this->_heldKeys[key];
}

bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->_pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key) {
	return this->_releasedKeys[key];
}

bool Input::isMouseHeld(Uint8 button) {
	return this->_heldMouseButtons[button];
}

bool Input::wasMousePressed(Uint8 button) {
	return this->_pressedMouseButtons[button];
}

bool Input::wasMouseReleased(Uint8 button) {
	return this->_releasedMouseButtons[button];
}
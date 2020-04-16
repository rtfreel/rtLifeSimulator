#include "input.h"
#include <SDL.h>

void Input::beginNewFrame() {
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
	this->scrolledUp = false;
	this->scrolledDown = false;
	this->_mousePressed = false;
	this->_mouseReleased = false;
	this->_mouseClicked = false;
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
	this->_mouseHeld = false;
	this->_mouseReleased = true;
	this->_mouseReleasedPos.first = event.button.x;
	this->_mouseReleasedPos.second = event.button.y;

	if (this->_mouseReleasedPos.first == this->_mousePressedPos.first &&
		this->_mouseReleasedPos.second == this->_mousePressedPos.second) {
		this->_mouseClicked = true;
		this->_mouseClick = this->_mouseReleasedPos;
	}
}

void Input::mouseDownEvent(const SDL_Event& event) {
	this->_mousePressed = true;
	this->_mouseHeld = true;
	this->_mousePressedPos.first = event.button.x;
	this->_mousePressedPos.second = event.button.y;
	this->_mouseLastPos = this->_mousePressedPos;
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

bool Input::isMouseHeld() {
	return this->_mouseHeld;
}

bool Input::wasMousePressed() {
	return this->_mousePressed;
}

bool Input::wasMouseReleased() {
	return this->_mouseReleased;
}

bool Input::mouseClicked() {
	return this->_mouseClicked;
}

std::pair<int, int> Input::getClick() {
	return this->_mouseClick;
}

std::pair<int, int> Input::getMove() {
	std::pair<int, int> move(0, 0);
	std::pair<int, int> state(0, 0);
	SDL_GetMouseState(&state.first, &state.second);
	move.first = this->_mouseLastPos.first - state.first;
	move.second = this->_mouseLastPos.second - state.second;
	this->_mouseLastPos = state;
	return move;
}
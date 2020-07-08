#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>

class Input {
public:
	void beginNewFrame();
	void keyUpEvent(const SDL_Event& event);
	void keyDownEvent(const SDL_Event& event);
	void mouseUpEvent(const SDL_Event& event);
	void mouseDownEvent(const SDL_Event& event);

	bool isKeyHeld(SDL_Scancode key);
	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isMouseHeld();
	bool wasMousePressed();
	bool wasMouseReleased();
	bool mouseClicked();

	std::pair<int, int> getClick();
	std::pair<int, int> getMove();

	bool scrolledUp, scrolledDown;

private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
	bool _mouseHeld, _mousePressed, _mouseReleased, _mouseClicked;
	std::pair<int, int> _mouseLastPos;
	std::pair<int, int> _mousePressedPos;
	std::pair<int, int> _mouseReleasedPos;
	std::pair<int, int> _mouseClick;
};

#endif
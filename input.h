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
	bool isMouseHeld(Uint8 button);
	bool wasMousePressed(Uint8 button);
	bool wasMouseReleased(Uint8 button);

	bool scrolledUp, scrolledDown;

private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
	std::map<Uint8, bool> _heldMouseButtons;
	std::map<Uint8, bool> _pressedMouseButtons;
	std::map<Uint8, bool> _releasedMouseButtons;

};

#endif
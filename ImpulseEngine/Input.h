#pragma once
#include <SDL.h>

#define KEYBOARD 0
#define MOUSE_BUTTON 1
#define GAMEPAD_BUTTON 2
#define UNDEFINED -1

class Input
{
public:
	Input();
	Input(SDL_Keycode key);
	~Input();
	
	void setMButtonInput(Uint8 button);
	void setGPadButtonInput(Uint8 button);
	void setKeyInput(SDL_Keycode key);

	
	SDL_Keycode getKey();
	Uint8 getButton();

	int getType();

private:
	SDL_Keycode key;
	Uint8 button;

	int type = UNDEFINED;
};

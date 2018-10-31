#include "Input.h"



Input::Input()
{
}

Input::Input(SDL_Keycode key)
:type(KEYBOARD), key(key)
{
}


Input::~Input()
{
}


void Input::setMButtonInput(Uint8 button)
{
	type = MOUSE_BUTTON;
	this->button = button;
}

void Input::setGPadButtonInput(Uint8 button)
{
	type = GAMEPAD_BUTTON;
	this->button = button;
}

void Input::setKeyInput(SDL_Keycode key)
{
	type = KEYBOARD;
	this->key = key;
}

 SDL_Keycode Input::getKey()
{
	return key;
}

 Uint8 Input::getButton()
{
	return button;
}

int Input::getType()
{
	return type;
}

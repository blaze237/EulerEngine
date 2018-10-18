#include "InputManager.h"
#include <iostream>

Vec2<int> InputManager::mousePos = Vec2<int>(0,0);

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::setRelativeMouseMode(bool b)
{
}

void InputManager::handleKeyDown(const SDL_Keycode &e)
{
	//std::cout << "key down" << e << std::endl;
}

void InputManager::handleKeyUp(const SDL_Keycode & e)
{
	//std::cout << "key up" << e << std::endl;
}

void InputManager::handleMouseKeyDown(const SDL_MouseButtonEvent & e)
{
	//std::cout << "mouse key down" << e.button << std::endl;

}

void InputManager::handleMouseKeyUp(const SDL_MouseButtonEvent & e)
{
	//std::cout << "mouse key up" << e.button << std::endl;
}

void InputManager::handleMouseMove(const SDL_MouseMotionEvent & e)
{
	if (SDL_GetRelativeMouseMode() == SDL_TRUE)
		mousePos.set(e.xrel, e.yrel);
	else
		mousePos.set(e.x, e.y);
}

void InputManager::handleMouseWheelEvent(const SDL_MouseWheelEvent & e)
{
//	if (e.y > 0) // scroll up
//	{
//		std::cout << "Scroll Up" << std::endl;
//	}
//	else if (e.y < 0) // scroll down
//	{
//		std::cout << "Scroll down" << std::endl;
//	}
//
//	if (e.x > 0) // scroll right
//	{
//		std::cout << "Scroll right" << std::endl;
//	}
//	else if (e.x < 0) // scroll left
//	{
//		std::cout << "Scroll left" << std::endl;
//	}
}

bool InputManager::isDown(SDL_Keycode key)
{
	return false;
}

bool InputManager::wasDown(SDL_Keycode key)
{
	return false;
}

bool InputManager::pressed(SDL_Keycode key)
{
	return false;
}

bool InputManager::held(SDL_Keycode key)
{
	return false;
}

bool InputManager::released(SDL_Keycode key)
{
	return false;
}

const Vec2<int>& InputManager::getMousePos()
{
	return mousePos;
}

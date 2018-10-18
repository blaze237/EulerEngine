#pragma once
#include <SDL.h>
#include <unordered_map>
#include "Vec2.h"

//Standard engine inputs that are mapped to specific keys by an external file
enum Inputs 
{
	FORWARD, BACKWARD, LEFT, RIGHT, ACTION, JUMP
};

class SceneManager;

class InputManager
{
	friend class SceneManager;

public:

	InputManager();
	~InputManager();

	

	static void setRelativeMouseMode(bool b);

	//ALSO WANT "INPUTS" VERSION OF EACH FUNCTION

	//Is the flag for this key true in the current tick
	static bool isDown(SDL_Keycode key);
	//Was the flag for this key true in the previous tick
	static bool wasDown(SDL_Keycode key);
	//Was the key pressed this tick
	static bool pressed(SDL_Keycode key);
	//Has the key been held down for two consecutive frames
	static bool held(SDL_Keycode key);
	//Was the key released this tick
	static bool released(SDL_Keycode key);

	//GET MOUSE POS AND SCROLLS AND DRAGS
	static const Vec2<int>& getMousePos();


private:

	static void handleKeyDown(const SDL_Keycode &e);
	static void handleKeyUp(const SDL_Keycode &e);
	static void handleMouseKeyDown(const SDL_MouseButtonEvent &e);
	static void handleMouseKeyUp(const SDL_MouseButtonEvent &e);
	static void handleMouseMove(const SDL_MouseMotionEvent &e);
	static void handleMouseWheelEvent(const SDL_MouseWheelEvent &e);

	//Hashtable of state of all inputs 
	std::unordered_map<int, bool> curInputStates;
	std::unordered_map<int, bool> prevInputStates;

	SDL_Keycode forward = SDLK_w;
	SDL_Keycode backward = SDLK_s;
	SDL_Keycode left = SDLK_a;
	SDL_Keycode right = SDLK_d;
	SDL_Keycode action = SDLK_e;
	SDL_Keycode jump = SDL_SCANCODE_SPACE;

	static Vec2<int> mousePos;
};


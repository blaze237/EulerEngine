#pragma once
#include <SDL.h>
#include <unordered_map>
#include "Vec2.h"
#include "Input.h"


//Standard engine inputs that are mapped to specific keys by an external file
enum CustomInputs 
{
	FORWARD, BACKWARD, LEFT, RIGHT, ACTION, JUMP, INVALID_INPUT
};

enum MWheelScrolls
{
	U, D, L, R, NONE
};

class SceneManager;

class InputManager
{
	friend class SceneManager;

private:
	//Private constructor to prevent intsantiation of InputManager outside of singleton pattern
	InputManager();
	~InputManager();

public:

	//Delete the copy cosntructor and assigment operator to enforce singleton
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;


	static InputManager &getInstance()
	{
		static InputManager    instance; 						  
		return instance;
	}

	void setRelativeMouseMode(bool b);

	//ALSO WANT keyboard, mouse and gamepad versions

	//Is the specified inputs state currently set to true
	bool isInputDown(CustomInputs input);
	//Was the specified inputs state set to true in the last frame
	bool wasInputDown(CustomInputs input);
	//Was the specified inputs state changed to true in this frame and 
	bool inputPressed(CustomInputs input);
	//Has the specified inputs state been set to true for two consectutive frames
	bool inputHeld(CustomInputs input);
	//Has the specified inputs state been changed to false in this frame
	bool inputReleased(CustomInputs input);


	//Is the specified keys state currently set to true
	bool isKeyDown(SDL_Keycode key);
	//Was the specified keys state set to true in the last frame
	bool wasKeyDown(SDL_Keycode key);
	//Was the specified keys state changed to true in this frame and 
	bool keyPressed(SDL_Keycode key);
	//Has the specified keys state been set to true for two consectutive frames
	bool keyHeld(SDL_Keycode key);
	//Has the specified keys state been changed to false in this frame
	bool keyReleased(SDL_Keycode key);

	//Is the specified keys state currently set to true
	bool isMButtonDown(Uint8 button);
	//Was the specified keys state set to true in the last frame
	bool wasMButtonDown(Uint8 button);
	//Was the specified keys state changed to true in this frame and 
	bool mButtonPressed(Uint8 button);
	//Has the specified keys state been set to true for two consectutive frames
	bool mButtonHeld(Uint8 button);
	//Has the specified keys state been changed to false in this frame
	bool mButtonReleased(SDL_Keycode button);



	MWheelScrolls getMWheelScroll();
	bool isMouseDragging();




	//GET MOUSE POS AND SCROLLS AND DRAGS
	const Vec2<int>& getMousePos();


	void update();



private:

	//Input event passthrough functions called by the main loop in SceneManager
	void handleKeyDown(const SDL_Keycode &key);
	void handleKeyUp(const SDL_Keycode &key);
	void handleMButtonDown(const SDL_MouseButtonEvent &e);
	void handleMButtonUp(const SDL_MouseButtonEvent &e);
	void handleMouseMove(const SDL_MouseMotionEvent &e);
	void handleMouseWheelEvent(const SDL_MouseWheelEvent &e);

	//Called internaly by the passthrough functions to update key/button/input state for the current frame
	void setCurKeyState(const SDL_Keycode &key, bool state);
	void setCurMButtonState(const Uint8 &key, bool state);

	//Translate key, mouse and gamepad button presses into associated input (if there exists one)
	CustomInputs translateToInput(const Uint8 &button);
	CustomInputs translateToInput(const SDL_Keycode &button);

	
	//Map of state of all inputs for current and previous frame
	std::unordered_map<CustomInputs, bool> curInputStates;
	std::unordered_map<CustomInputs, bool> prevInputStates;
	//Map of state of all keyboard keys for current and previous frame
	std::unordered_map<SDL_Keycode, bool> curKeyboardStates;
	std::unordered_map<SDL_Keycode, bool> prevKeyboardStates;
	//Map of state of all mouse buttons for current and previous frame
	std::unordered_map<Uint8, bool> curMButtonStates;
	std::unordered_map<Uint8, bool> prevMButtonStates;

	//Controller buttons

	//Controller joystick





	//PUT THESE IN A VECTOR
	 Input forward = SDLK_w;
	 Input backward = SDLK_s;
	 Input left = SDLK_a;
	 Input right = SDLK_d;
	 Input action = SDLK_e;
	 Input jump = SDLK_SPACE;

	 Vec2<int> mousePos = Vec2<int>(0, 0);

	 bool mouseDragged = false;
	 MWheelScrolls mWheelScrollDirection = NONE;

	 void(*onGamepadConnect)();
	 void(*onGamepadDisconnect)();

};


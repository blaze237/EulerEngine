#include "InputManager.h"
#include <iostream>


//MAKE INTO A SINGLETON
InputManager::InputManager()
{
	//Initialise the map for standard inputs
	curInputStates.emplace(FORWARD, false);
	curInputStates.emplace(BACKWARD, false);
	curInputStates.emplace(LEFT, false);
	curInputStates.emplace(RIGHT, false);
	curInputStates.emplace(JUMP, false);
	curInputStates.emplace(ACTION, false);

	prevInputStates.emplace(FORWARD, false);
	prevInputStates.emplace(BACKWARD, false);
	prevInputStates.emplace(LEFT, false);
	prevInputStates.emplace(RIGHT, false);
	prevInputStates.emplace(JUMP, false);
	prevInputStates.emplace(ACTION, false);
}


InputManager::~InputManager()
{
}

void InputManager::setRelativeMouseMode(bool b)
{
}


void InputManager::setCurKeyState(const SDL_Keycode & key, bool state)
{
	//First we have to check if this key has allready been registered in the current map
	auto it = curKeyboardStates.find(key);
	//If it has, simply update its state
	if (it != curKeyboardStates.end())
		it->second = state;
	//Otherwise add it to the map
	else
		curKeyboardStates.emplace(key, state);


	//Check if this key is one of the keys set as custom input
	CustomInputs input;
	if ((input = translateToInput(key)) == INVALID_INPUT)
		return;

	//The key pressed is set as a custom input, so we need to update the map for custom input states

	//First we have to check if this key has allready been registered in the current map
	auto it2 = curInputStates.find(input);
	//If it has, simply update its state
	if (it2 != curInputStates.end())
		it2->second = state;
	//Otherwise add it to the map
	else
		curInputStates.emplace(input, state);
	   
}

void InputManager::setCurMButtonState(const Uint8 & key, bool state)
{
	//First we have to check if this key has allready been registered in the current map
	auto it = curMButtonStates.find(key);
	//If it has, simply update its state
	if (it != curMButtonStates.end())
		it->second = state;
	//Otherwise add it to the map
	else
		curMButtonStates.emplace(key, state);

	//Check if this key is one of the keys set as custom input
	CustomInputs input;
	if ((input = translateToInput(key)) == INVALID_INPUT)
		return;

	//The button pressed is set as a custom input, so we need to update the map for custom input states

	//First we have to check if this key has allready been registered in the current map
	auto it2 = curInputStates.find(input);
	//If it has, simply update its state
	if (it2 != curInputStates.end())
		it2->second = state;
	//Otherwise add it to the map
	else
		curInputStates.emplace(input, state);
}


CustomInputs InputManager::translateToInput(const Uint8 &button)
{
	//Loop through inputs, return first one of button type (mouse or gamepad, just not keyboard) with matching button val, or INVALID_INPUT
	if (forward.getType() != KEYBOARD && forward.getButton() == button)
		return FORWARD;
	if (backward.getType() != KEYBOARD && backward.getButton() == button)
		return BACKWARD;
	if (left.getType() != KEYBOARD && left.getButton() == button)
		return LEFT;
	if (right.getType() != KEYBOARD && right.getButton() == button)
		return RIGHT;
	if (action.getType() != KEYBOARD && action.getButton() == button)
		return ACTION;
	if (jump.getType() != KEYBOARD && jump.getButton() == button)
		return JUMP;

	return INVALID_INPUT;
}


CustomInputs InputManager::translateToInput(const SDL_Keycode &key)
{
	//Loop through inputs, return first one of keyboard type with matching key val, or INVALID_INPUT
	if (forward.getType() == KEYBOARD && forward.getKey() == key)
		return FORWARD;
	if (backward.getType() == KEYBOARD && backward.getKey() == key)
		return BACKWARD;
	if (left.getType() == KEYBOARD && left.getKey() == key)
		return LEFT;
	if (right.getType() == KEYBOARD && right.getKey() == key)
		return RIGHT;
	if (action.getType() == KEYBOARD && action.getKey() == key)
		return ACTION;
	if (jump.getType() == KEYBOARD && jump.getKey() == key) 
		return JUMP;

	return INVALID_INPUT;
}

void InputManager::handleKeyDown(const SDL_Keycode &key)
{
	setCurKeyState(key, true);
}

void InputManager::handleKeyUp(const SDL_Keycode &key)
{
	setCurKeyState(key, false);
}

void InputManager::handleMButtonDown(const SDL_MouseButtonEvent & e)
{
	setCurMButtonState(e.button, true);
}

void InputManager::handleMButtonUp(const SDL_MouseButtonEvent & e)
{
	setCurMButtonState(e.button, false);
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
	//Scrolled up
	if (e.y > 0)
		mWheelScrollDirection = U;
	//Scrolled Down
	else if (e.y < 0) 
		mWheelScrollDirection = D;
	//Scrolled Right
	else if (e.x > 0) 
		mWheelScrollDirection = R;
	//Scrolled Left
	if (e.x < 0) 		
		mWheelScrollDirection = L;
}



bool InputManager::isInputDown(CustomInputs input)
{
	//If it doesnt exist, just return false. If it does exist, return the value
	auto it = curInputStates.find(input);
	return (it == curInputStates.end()) ? false : it->second;
}

bool InputManager::wasInputDown(CustomInputs input)
{
	//If it doesnt exist, just return false. If it does exist, return the value
	auto it = prevInputStates.find(input);
	return (it == prevInputStates.end()) ? false : it->second;
}

bool InputManager::inputPressed(CustomInputs input)
{
	return !wasKeyDown(input) && isKeyDown(input);
}

bool InputManager::inputHeld(CustomInputs input)
{
	return wasKeyDown(input) && isKeyDown(input);
}

bool InputManager::inputReleased(CustomInputs input)
{
	return wasKeyDown(input) && !isKeyDown(input);
}

bool InputManager::isKeyDown(SDL_Keycode key)
{
	//If it doesnt exist, just return false. If it does exist, return the value
	auto it = curKeyboardStates.find(key);
	return (it == curKeyboardStates.end()) ? false : it->second;
}

bool InputManager::wasKeyDown(SDL_Keycode key)
{
	//If it doesnt exist, just return false. If it does exist, return the value
	auto it = prevKeyboardStates.find(key);
	return (it == prevKeyboardStates.end()) ? false : it->second;
}

bool InputManager::keyPressed(SDL_Keycode key)
{
	return !wasKeyDown(key) && isKeyDown(key);
}

bool InputManager::keyHeld(SDL_Keycode key)
{
	return wasKeyDown(key) && isKeyDown(key);
}

bool InputManager::keyReleased(SDL_Keycode key)
{
	return wasKeyDown(key) && !isKeyDown(key);
}

bool InputManager::isMButtonDown(Uint8 button)
{
	//If it doesnt exist, just return false. If it does exist, return the value
	auto it = curMButtonStates.find(button);
	return (it == curMButtonStates.end()) ? false : it->second;
}

bool InputManager::wasMButtonDown(Uint8 button)
{
	//If it doesnt exist, just return false. If it does exist, return the value
	auto it = prevMButtonStates.find(button);
	return (it == prevMButtonStates.end()) ? false : it->second;
}

bool InputManager::mButtonPressed(Uint8 button)
{
	return !wasMButtonDown(button) && isKeyDown(button);
}

bool InputManager::mButtonHeld(Uint8 button)
{
	return wasMButtonDown(button) && isMButtonDown(button);
}

bool InputManager::mButtonReleased(SDL_Keycode button)
{
	return wasMButtonDown(button) && !isMButtonDown(button);
}

MWheelScrolls InputManager::getMWheelScroll()
{
	return MWheelScrolls();
}

bool InputManager::isMouseDragging()
{
	//TODO
	return false;
}

const Vec2<int>& InputManager::getMousePos()
{
	return mousePos;
}

void InputManager::update()
{
	//Put states from the frame that has just ended into previous states map ready for next frame
	prevInputStates = curInputStates;
	prevKeyboardStates = curKeyboardStates;


	//Reset mouse vars
	mouseDragged = false;
	mWheelScrollDirection = NONE;


}

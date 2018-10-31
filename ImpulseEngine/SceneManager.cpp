#include "SceneManager.h"
#include "InputManager.h"
#include <SDL_image.h>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <thread>
#include "MathTools.h"
#include "Vec2.h"
SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

bool SceneManager::init(int width, int height, Uint32 windowFlags, Uint32 rendererFlags)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL. Err code: " << SDL_GetError() << std::endl;
		return false;
	}

	//Set texture scaling
	switch (textureScaleMode)
	{
		case SceneManager::NEAREST_PIXEL:
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
				std::cout << "Failed to enable nearest pixel sampling!" << std::endl;
			break;
		case SceneManager::LINEAR:
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				std::cout << "Failed to enable linear filtering!" << std::endl;
			break;
		case SceneManager::ANISOTROPIC:
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				std::cout << "Failed to enable anisotropic filtering!" << std::endl;
			break;
	}

	//Make window
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
	if (window == NULL)
	{
		std::cout << "Failed to create window. Err code: " << SDL_GetError() << std::endl;
		return false;
	}

	//Make renderer 
	windowRenderer = SDL_CreateRenderer(window, -1, rendererFlags);
	if (windowRenderer == NULL)
	{
		std::cout << "Failed to create renderer. Err code: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(windowRenderer, bgColour.r, bgColour.g, bgColour.b, bgColour.a);

		//Initialize SDL_image
		int imgFlags = IMG_INIT_PNG || IMG_INIT_JPG || IMG_INIT_TIF;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			std::cout << "Failed to initialise SDL_image. Err code: " << IMG_GetError() << std::endl;
			return false;
		}
	}

	//If weve reached this point, then we can start up the engine!
	mainLoop();
}

void SceneManager::shutdown()
{
}

void SceneManager::mainLoop()
{
	//look into how vysnc effects loop speed?

	//Run the game indefinitley untill quit
	while (!quit)
	{
		//Get start time for this frame
		long fStart = SDL_GetTicks();
		//Determine what tick whe should be at by this time (technicaly fStart - gameStartTime, but this is is allways zero as using SDL_GetTicks() for time)
		long targetTick = ((int)(fStart * FIXED_UPDATE_RATE)) / 1000;

		//Keep prossessing phsyics/input ticks untill we reach the target tick
		while (currentTick < targetTick)
		{
			fixedUpdate(SDL_GetTicks());
			++currentTick;
		}

		//Now phsyics is up to date, we can render a frame and process a normal update logic tick
		update(SDL_GetTicks());
		render();

		//Update framecount, and if time update the fps value
		++frameCount;
		if (fStart >= frameIntervalEnd)
		{
			fps = frameCount;

			frameCount = 0;
			frameIntervalEnd = fStart + 1000;

			std::cout << "FPS: " << fps << std::endl;

		}

		

		//Max number of visualy different renderable frames is set by the tick rate, therefore we sleep untill the next tick to avoid waisting resources rendering identical intermediate frames
		long sleepTime = 1000 / FIXED_UPDATE_RATE + fStart - SDL_GetTicks();
		SDL_Delay(sleepTime < 0 ? 0 : sleepTime);
	}

	cleanup();
}

void SceneManager::fixedUpdate(long tCurrent)
{
	//First job is to check input
	pollEvents();


	//Next apply physics to awake objects in the scene
	//Non rigidbody + colider => static colider, allways the same bounds
	//Rididbody + collider => attempt to move, handle collisions that occur
	//kinematic rigidbody => it can move freely through anything, but things will collide with it and not go through it
	//Rigidbody + nocollidr => just gravity?





}

void SceneManager::update(long tCurrent)
{

	if (inputManager.keyHeld(SDLK_w))
		std::cout << "w!";


	//Tell the input manager to advance to polling for next frame. Must be last thing in update loop
	inputManager.update();
}

void SceneManager::pollEvents()
{
	//Handle event queue
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{

		switch (e.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			inputManager.handleKeyDown(e.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.handleKeyUp(e.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.handleMButtonDown(e.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.handleMButtonUp(e.button);
			break;
		case SDL_MOUSEMOTION:
			inputManager.handleMouseMove(e.motion);
			break;
		case SDL_MOUSEWHEEL:
			inputManager.handleMouseWheelEvent(e.wheel);
			break;
		case SDL_CONTROLLERAXISMOTION:

			break;
		case SDL_CONTROLLERBUTTONDOWN:

			break;
		case SDL_CONTROLLERBUTTONUP:

			break;
		case SDL_CONTROLLERDEVICEADDED:

			break;
		case SDL_CONTROLLERDEVICEREMOVED:

			break;
		default:
				break;
			//TODO controllers and touch?
		}
	}
}

void SceneManager::render()
{
	//Clear screen
	SDL_SetRenderDrawColor(windowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(windowRenderer);

	
	//Update screen
	SDL_RenderPresent(windowRenderer);
}

void SceneManager::cleanup()
{
	SDL_DestroyRenderer(windowRenderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

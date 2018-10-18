#pragma once

#include <SDL.h>
class SceneManager
{
public:
	enum TEXTURE_SCALE_MODE {NEAREST_PIXEL, LINEAR, ANISOTROPIC};

	

	SceneManager();
	~SceneManager();

	bool init(int width, int height, Uint32 windowFlags, Uint32 rendererFlags);
	void shutdown();



private:
	void mainLoop();
	void fixedUpdate(long tCurrent);
	void update(long tCurrent);
	void pollEvents();
	void render();
	void cleanup();

	TEXTURE_SCALE_MODE textureScaleMode = LINEAR;
	bool quit = false;

	SDL_Color bgColour = { 255, 255, 255, 255 };

	//Window to render to
	SDL_Window* window = NULL;
	//Renderer for the window
	SDL_Renderer* windowRenderer = NULL;

	//How many fixed update ticks per second. Fixed update used for physics and input
	int FIXED_UPDATE_RATE = 120;

	//What engine tick are we on
	long currentTick = 0;

	long frameIntervalEnd = 0; //End of the current frame count interval
	long frameCount;	//How many frames have been rendered so far since the last frame interval (1 second)
	int fps = 0;
};


#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Engine
{
private: // Properties
	// Global engine variables.
	bool g_bRunning = false; // Loop control flag.
	int g_iSpeed = 5; // Speed of box.
	const Uint8* g_iKeystates; // Keyboard state container.
	Uint32 g_start, g_end, g_delta, g_fps; // Fixed timestep variables.
	SDL_Window* g_pWindow; // This represents the SDL window.
	SDL_Renderer* g_pRenderer; // This represents the buffer to draw to.
	SDL_Texture* g_pTexture[3];
	bool up = true;

	// METHODS
	bool init(const char*, int, int, int, int, int);
	void wake();
	void sleep();
	void handleEvents();
	bool keyDown(SDL_Scancode);
	void update();
	void render();
	void clean();

public: // public methods
	Engine();
	~Engine();
	int run();
};


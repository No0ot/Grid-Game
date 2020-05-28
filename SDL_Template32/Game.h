#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "FSM.h"
// GAME MANAGERS
#include "TextureManager.h"


class Game
{
public:
	static Game* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	//void init() { m_bRunning = true; }

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	//public functions
	void render();
	void update();
	void handleEvents();
	void clean();
	void QuitGame() { m_bRunning = false; }
	bool running() { return m_bRunning; }
	FSM& GetFSM();

	SDL_Renderer* getRenderer();
	void setFrames(Uint32 frames);
	
	bool GetMouseState(int idx);
	void SetMouseState(int idx, bool b);
	SDL_Point& GetMousePos();

	private:
	Game();
	~Game();


	Uint32 m_frames;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	int m_currentFrame;
	bool m_bRunning;
	static Game* s_pInstance;
	FSM* m_pFSM;

	SDL_Point m_MousePos;
	bool m_MouseState[3] = { 0,0,0 };
};

typedef Game TheGame;


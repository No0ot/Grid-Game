#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include "FSM.h"

#include "Config.h"

class Engine
{
	// I am avoiding in-class initialization.
private: // Private properties.
	const Uint8* m_iKeystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Window* m_pWindow; // This represents the SDL window.
	SDL_Renderer* m_pRenderer; // This represents the buffer to draw to.

	TTF_Font* font;

	Mix_Music* m_pMusic;
	std::vector<Mix_Chunk*> m_vSounds;
	FSM* m_pFSM;

	SDL_Point m_MousePos;
	bool m_MouseState[3] = { 0,0,0 };

private: // Private methods.
public: // Public methods.
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool m_bRunning; // Loop control flag.
	bool KeyDown(SDL_Scancode c);
	SDL_Renderer* GetRenderer();
	SDL_Point& GetMousePos();
	TTF_Font* getFont();
	bool GetMouseState(int idx);
	void SetMouseState(int idx, bool b);
	Mix_Music* GetMusic();
	Mix_Chunk* GetSound(int i);
	FSM& GetFSM();
	void QuitGame();
	Engine();
	static Engine& Instance();
	~Engine();
};
//#pragma once
//#include <iostream>
//#include <vector>
//#include <SDL.h>
//#include <SDL_image.h>
//#include "FSM.h"
//// GAME MANAGERS
//#include "TextureManager.h"
//
//
//class Game
//{
//public:
//	static Game* Instance()
//	{
//		if (s_pInstance == nullptr)
//		{
//			s_pInstance = new Game();
//			return s_pInstance;
//		}
//		return s_pInstance;
//	}
//
//	//void init() { m_bRunning = true; }
//
//	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
//
//	//public functions
//	void render();
//	void update();
//	void handleEvents();
//	void clean();
//	void QuitGame() { m_bRunning = false; }
//	bool running() { return m_bRunning; }
//	FSM& GetFSM();
//
//	SDL_Renderer* getRenderer();
//	void setFrames(Uint32 frames);
//	
//	bool GetMouseState(int idx);
//	void SetMouseState(int idx, bool b);
//	SDL_Point& GetMousePos();
//
//	private:
//	Game();
//	~Game();
//
//
//	Uint32 m_frames;
//	SDL_Window* m_pWindow;
//	SDL_Renderer* m_pRenderer;
//	int m_currentFrame;
//	bool m_bRunning;
//	static Game* s_pInstance;
//	FSM* m_pFSM;
//
//	SDL_Point m_MousePos;
//	bool m_MouseState[3] = { 0,0,0 };
//};
//
//typedef Game TheGame;

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include "FSM.h"



class Engine
{
	// I am avoiding in-class initialization.
private: // Private properties.
	int timer;
	bool spaceOk;
	const Uint8* m_iKeystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Window* m_pWindow; // This represents the SDL window.
	SDL_Renderer* m_pRenderer; // This represents the buffer to draw to.

	SDL_Texture* m_pObsText;
	SDL_Texture* m_pBGText;
	SDL_Texture* m_pStartText;
	SDL_Texture* m_pLoseText;
	SDL_Point m_pivot;
	SDL_Texture* m_pSprText; // For the sprites.
	TTF_Font* font;

	int m_iESpawn, // The enemy spawn frame timer properties.
		m_iESpawnMax;


	Mix_Music* m_pMusic;
	std::vector<Mix_Chunk*> m_vSounds;
	FSM* m_pFSM;

	SDL_Point m_MousePos;
	bool m_MouseState[3] = { 0,0,0 };

private: // Private methods.
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
public: // Public methods.
	bool m_bRunning; // Loop control flag.
	bool KeyDown(SDL_Scancode c);
	SDL_Renderer* GetRenderer();
	SDL_Texture* GetScreenSpr();
	SDL_Texture* GetBGSpr();
	SDL_Texture* GetLoseSpr();
	SDL_Texture* GetSprite();
	SDL_Texture* GetObsSprite();
	SDL_Point& GetMousePos();
	TTF_Font* getFont();
	bool GetMouseState(int idx);
	void SetMouseState(int idx, bool b);
	bool getSpacebool();
	void setSpacebool(bool b);
	Mix_Music* GetMusic();
	Mix_Chunk* GetSound(int i);
	void setTime(int t);
	FSM& GetFSM();
	void QuitGame();
	Engine();
	static Engine& Instance();
	~Engine();
	int Run();
};
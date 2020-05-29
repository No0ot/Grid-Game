#include "Engine.h"
#include <iostream>
#include <ctime>

Engine::Engine()
{

}

Engine& Engine::Instance()
{
	static Engine TheGameEngine;
	return TheGameEngine;
}

Engine::~Engine() {}

bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	std::cout << "Initializing game." << std::endl;
	srand((unsigned)time(NULL));
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != nullptr) // Renderer init success.
			{
	
				TTF_Init();
				// insert fonts here
				if (Mix_Init(MIX_INIT_MP3) != 0) // Mixer init success.
				{
					Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048); // Good for most games.
					Mix_AllocateChannels(16);
					// insert music here
					// Load the chunks into the Mix_Chunk vector.
					m_vSounds.reserve(3); // Optional but good practice.
					//insert sounds here
					/* By the way, you should check to see if any of these loads are failing and
					   you can use Mix_GetError() to print out the error message. Wavs can be finicky.*/
				}
				else return false;
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / 60) * 1000); // Sets FPS in milliseconds and rounds.
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	m_pFSM = new FSM();
	m_pFSM->ChangeState(new GameState());
	Mix_PlayMusic(m_pMusic, -1); // Play. -1 = looping.
	Mix_VolumeMusic(16); // 0-MIX_MAX_VOLUME (128).
	m_bRunning = true; // Everything is okay, start the engine.
	std::cout << "Success!" << std::endl;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

void Engine::HandleEvents()
{
	GetFSM().HandleEvents();
}

// Keyboard utility function.
bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

SDL_Renderer* Engine::GetRenderer()
{
	return m_pRenderer;
}

SDL_Point& Engine::GetMousePos()
{
	return m_MousePos;
}

TTF_Font* Engine::getFont()
{
	return font;
}

bool Engine::GetMouseState(int i)
{
	return m_MouseState[i];
}

void Engine::SetMouseState(int i, bool b)
{
	m_MouseState[i] = b;
}

Mix_Music* Engine::GetMusic()
{
	return m_pMusic;
}

Mix_Chunk* Engine::GetSound(int i)
{
	return m_vSounds[i];
}

FSM& Engine::GetFSM()
{
	return *m_pFSM;
}

void Engine::Update()
{
	GetFSM().Update();

}

void Engine::Render()
{
	GetFSM().Render();

	//SDL_RenderPresent(m_pRenderer);
}

void Engine::Clean()
{
	std::cout << "Cleaning game." << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	for (int i = 0; i < (int)m_vSounds.size(); i++)
		Mix_FreeChunk(m_vSounds[i]);
	m_vSounds.clear();
	Mix_FreeMusic(m_pMusic);
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}




void Engine::QuitGame() { m_bRunning = false; }
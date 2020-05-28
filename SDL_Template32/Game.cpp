#include "Game.h"

//Game* Game::s_pInstance = nullptr;
//
//SDL_Renderer* Game::getRenderer()
//{
//	return m_pRenderer;
//}
//
//Game::Game()
//{
//}
//
//Game::~Game()
//{
//}
//
//bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
//{
//	int flags = 0;
//	if (fullscreen)
//	{
//		flags = SDL_WINDOW_FULLSCREEN;
//	}
//
//	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
//	{
//		std::cout << "SDL Init success" << std::endl;
//		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
//		if (m_pWindow != nullptr) // Window init success.
//		{
//			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
//			if (m_pRenderer != nullptr)
//			{
//				std::cout << "renderer creation success" << std::endl;
//				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
//			}
//			else
//			{
//				std::cout << "renderer init failure" << std::endl;
//				return false; // render int fail
//			}
//		}
//		else
//		{
//			std::cout << "window init failure" << std::endl;
//			return false; // window init fail
//		}
//	}
//	else
//	{
//		std::cout << "SDL init failure" << std::endl;
//		return false; //SDL could not intialize
//	}
//
//	std::cout << "init success" << std::endl;
//
//	m_bRunning = true; // everything initialized successfully - start the main loop
//	m_pFSM = new FSM();
//	m_pFSM->ChangeState(new TitleState());
//
//	return true;
//}
//	
//void Game::render()
//{
//	SDL_RenderClear(getRenderer()); // clear the renderer to the draw colour
//	
//	GetFSM().Render();
//
//	SDL_RenderPresent(getRenderer()); // draw to the screen
//
//
//}
//
//void Game::update()
//{
//	GetFSM().Update();
//	std::cout << "googog " << std::endl;
//}
//
//void Game::clean()
//{
//	std::cout << "Cleaning game!" << std::endl;
//
//	SDL_DestroyRenderer(m_pRenderer);
//	SDL_DestroyWindow(m_pWindow);
//	SDL_Quit();
//}
//
//void Game::handleEvents()
//{
//	GetFSM().HandleEvents();
//}
//
//FSM& Game::GetFSM()
//{
//	return *m_pFSM;
//}
//
//void Game::setFrames(const Uint32 frames)
//{
//	m_frames = frames;
//}
//
//bool Game::GetMouseState(int i)
//{
//	return m_MouseState[i];
//}
//
//void Game::SetMouseState(int i, bool b)
//{
//	m_MouseState[i] = b;
//}
//
//SDL_Point& Game::GetMousePos()
//{
//	return m_MousePos;
//}

#include "Game.h"
#include <iostream>
#include <ctime>
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
#define BGSCROLL 2 // Could these scroll/speed values be handled in the class? Yes. Consider it!

using namespace std;

Engine::Engine() :m_iESpawn(0), m_iESpawnMax(60), m_MousePos({ 0,0 })
{

	cout << "Engine class constructed!" << endl;
}

Engine& Engine::Instance()
{
	static Engine TheGameEngine;
	return TheGameEngine;
}

Engine::~Engine() {}

bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game." << endl;
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
				
				if (Mix_Init(MIX_INIT_MP3) != 0) // Mixer init success.
				{
					Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048); // Good for most games.
					Mix_AllocateChannels(16);
					
					// Load the chunks into the Mix_Chunk vector.
					m_vSounds.reserve(3); // Optional but good practice.
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
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	m_pFSM = new FSM();
	m_pFSM->ChangeState(new GameState());
	spaceOk = true;
	Mix_PlayMusic(m_pMusic, -1); // Play. -1 = looping.
	Mix_VolumeMusic(16); // 0-MIX_MAX_VOLUME (128).
	m_bRunning = true; // Everything is okay, start the engine.
	cout << "Success!" << endl;
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

SDL_Texture* Engine::GetScreenSpr()
{
	return m_pStartText;
}


SDL_Texture* Engine::GetBGSpr()
{
	return m_pBGText;
}

SDL_Texture* Engine::GetLoseSpr()
{
	return m_pLoseText;
}

SDL_Texture* Engine::GetSprite()
{
	return m_pSprText;
}

SDL_Texture* Engine::GetObsSprite()
{
	return m_pObsText;
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

bool Engine::getSpacebool()
{
	return spaceOk;
}

void Engine::setSpacebool(bool b)
{
	spaceOk = b;
}

Mix_Music* Engine::GetMusic()
{
	return m_pMusic;
}

Mix_Chunk* Engine::GetSound(int i)
{
	return m_vSounds[i];
}

void Engine::setTime(int t)
{
	timer = t;
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
	cout << "Cleaning game." << endl;

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


int Engine::Run()
{
	if (Init("GAME1017 Shooter Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning)
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_bRunning)
			Sleep();
	}
	Clean();
	return 0;
}

void Engine::QuitGame() { m_bRunning = false; }
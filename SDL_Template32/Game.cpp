#include "Game.h"

Game* Game::s_pInstance = nullptr;

SDL_Renderer* Game::getRenderer()
{
	return m_pRenderer;
}

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr)
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}
		}
		else
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;

	m_bRunning = true; // everything initialized successfully - start the main loop
	m_pFSM = new FSM();
	m_pFSM->ChangeState(new TitleState());

	return true;
}
	
void Game::render()
{
	SDL_RenderClear(getRenderer()); // clear the renderer to the draw colour
	
	GetFSM().Render();

	SDL_RenderPresent(getRenderer()); // draw to the screen


}

void Game::update()
{
	GetFSM().Update();
	std::cout << "googog " << std::endl;
}

void Game::clean()
{
	std::cout << "Cleaning game!" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::handleEvents()
{
	GetFSM().HandleEvents();
}

FSM& Game::GetFSM()
{
	return *m_pFSM;
}

void Game::setFrames(const Uint32 frames)
{
	m_frames = frames;
}

bool Game::GetMouseState(int i)
{
	return m_MouseState[i];
}

void Game::SetMouseState(int i, bool b)
{
	m_MouseState[i] = b;
}

SDL_Point& Game::GetMousePos()
{
	return m_MousePos;
}
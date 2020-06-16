#include "FSM.h"
#include "Engine.h"
#include <iostream>
#include <sstream>
#define WIDTH 1024
#define HEIGHT 768
using namespace std;

// Begin State.
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			Engine::Instance().QuitGame();
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Engine::Instance().QuitGame();
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button >= 1 && event.button.button <= 3)
				Engine::Instance().SetMouseState(event.button.button - 1, true);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button >= 1 && event.button.button <= 3)
				Engine::Instance().SetMouseState(event.button.button - 1, false);
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&Engine::Instance().GetMousePos().x, &Engine::Instance().GetMousePos().y);
			break;
		}
	}
}

void State::Resume(){}
// End State.


// Begin GameState.
GameState::GameState() : current_state(PLAYER_MOVE) {}

void GameState::BuildHexGrid()
{
	m_pHexGrid = std::vector<Hex*>();

	for (auto column = 0; column < 15; ++column)
	{
		for (auto row = 0; row < 10; ++row)
		{
			auto hex = new Hex();
			if( column % 2 == 1)
				hex->setPosition(glm::vec2(20 + (column * 48), (50 + (row * 64)) - 15));
			else
				hex->setPosition(glm::vec2(20 + (column * 48), (50 + (row * 64)) + 15));

			m_pHexGrid.push_back(hex);
		}
	}
	
}

void GameState::Enter()
{
	cout << "Entering Game..." << endl;
	BuildHexGrid();
	//m_MercVec = std::vector<Merc*>();
	//m_MercVec[0] = new Merc(ARCHER);
	
	m_Merc = new Merc(ARCHER);
	m_Merc->setHex(m_pHexGrid[16]);
}

void GameState::Update()
{
	switch (current_state)
	{
	case PLAYER_MOVE :
		for (int count = 0; count < (int)m_pHexGrid.size(); count++)
		{
			m_pHexGrid[count]->update();

		}
			m_Merc->update();

		break;
	case PLAYER_ABILITY:

		break;
	}
	//std::cout << " updating..." << std::endl;
}

void GameState::HandleEvents()
{
	State::HandleEvents();
}

void GameState::Render()
{
	//cout << "Rendering Game..." << endl;
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	//SDL_RenderClear(Engine::Instance().GetRenderer()); // Clear the screen with the draw color.
	// hex

	for (int count = 0; count < (int)m_pHexGrid.size(); count++)
		m_pHexGrid[count]->draw();
		
	m_Merc->draw();

	if (dynamic_cast<GameState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();
}

void GameState::Exit()
{
	cout << "Exiting Game..." << endl;
}

void GameState::Resume()
{
	cout << "Resuming Game..." << endl;
}

// End GameState.

// Begin TitleState.
TitleState::TitleState(){}

void TitleState::Enter()
{
	cout << "Entering Title..." << endl;
}

void TitleState::Update()
{
	
}

void TitleState::Render()
{
	cout << "Rendering Title..." << endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	if (dynamic_cast<TitleState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();
}

void TitleState::HandleEvents()
{
	State::HandleEvents();
}

void TitleState::Exit()
{
	cout << "Exiting Title..." << endl;
	
}
// End TitleState.

// Begin FSM.
FSM::FSM() {}
FSM::~FSM() {}

void FSM::Update()
{
	if (!m_vStates.empty())
		m_vStates.back()->Update(); // Invokes the Update of the current state.
}

void FSM::Render()
{
	if (!m_vStates.empty())
		m_vStates.back()->Render(); // Invokes the Render of the current state.
}
void FSM::ChangeState(State* pState)
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	//PushState(pState);
	pState->Enter(); // Invoke the Enter of the NEW current state.
	m_vStates.push_back(pState); // Push the address of the NEW current state into the vector.
}

void FSM::PushState(State* pState) 
{
	pState->Enter(); // Invoke the Enter of the NEW current state.
	m_vStates.push_back(pState); // Push the address of the NEW current state into the vector.
}

void FSM::PopState() // e.g. PauseState to GameState.
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->Resume();
}

void FSM::HandleEvents()
{
	if (!m_vStates.empty())
		m_vStates.back()->HandleEvents();
}

void FSM::Clean()
{
	while (!m_vStates.empty())
	{
		m_vStates.back()->Exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}

vector<State*>& FSM::GetStates() { return m_vStates; }
// End FSM.

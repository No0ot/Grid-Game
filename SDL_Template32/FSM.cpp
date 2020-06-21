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
			if (!mouseDown) {
				if (event.button.button >= 1 && event.button.button <= 3) {
					Engine::Instance().SetMouseState(event.button.button - 1, true);
					mouseDown = true;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button >= 1 && event.button.button <= 3) {
				Engine::Instance().SetMouseState(event.button.button - 1, false);
				mouseDown = false;
			}
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
GameState::GameState() : current_state(PLAYER_FACING) {}

void GameState::BuildHexGrid()
{
	m_pHexGrid = std::vector<Hex*>();

	for (auto row = 0; row < 11; row++)
	{
		for (auto column = 0; column < 15; column++)
		{
		
			if (column % 2 == 1)
			{
				auto newhex = new Hex(glm::vec2(20 + (column * 49), (50 + (row * 61)) - 15), glm::vec2(row, column));
				m_pHexGrid.push_back(newhex);
			}
			else
			{
				auto newhex = new Hex(glm::vec2(20 + (column * 49), (50 + (row * 61)) + 15), glm::vec2(row, column));
				m_pHexGrid.push_back(newhex);
			}
		}
	}
	
}

void GameState::MapGrid()
{
	for (auto hex : m_pHexGrid)
	{
		const auto x = hex->getGridPosition().x;
		const auto y = hex->getGridPosition().y;

		if (x != 0) { hex->setUp(m_pHexGrid[y + ((x - 1) * 15)]); }
		if (x != 11 - 1) { hex->setDown(m_pHexGrid[y + ((x + 1) * 15)]); }

		if ((int)y % 2 == 1)
		{
			if (y != 15 - 1 && x != 0) { hex->setUpRight(m_pHexGrid[(y + 1) + ((x - 1) * 15)]); }
			if (y != 15 - 1) { hex->setDownRight(m_pHexGrid[(y + 1) + (x * 15)]); }
			if (y != 0 && x != 0) { hex->setUpLeft(m_pHexGrid[(y - 1) + ((x - 1) * 15)]); }
			if (y != 0) { hex->setDownLeft(m_pHexGrid[(y - 1) + (x * 15)]); }
		}
		else
		{
			if (y != 15 - 1) { hex->setUpRight(m_pHexGrid[(y + 1) + (x * 15)]); }
			if (y != 15 - 1 && x != 11 - 1) { hex->setDownRight(m_pHexGrid[(y + 1) + ((x + 1) * 15)]); }
			if (y != 0 ) { hex->setUpLeft(m_pHexGrid[(y - 1) + (x * 15)]); }
			if (y != 0 && x != 11 - 1) { hex->setDownLeft(m_pHexGrid[(y - 1) + ((x + 1) * 15)]); }
		}
	}
}

void GameState::ResetHexs()
{
	m_pHexList.clear();
	m_pHexList2.clear();
	for (int count = 0; count < (int)m_pHexGrid.size(); count++)
	{
		m_pHexGrid[count]->setInteractiveState(Hex::INITIAL);
		m_pHexGrid[count]->setMouseState(Hex::STATE_OFF);
	}
	//std::cout << " HEXES RESET " << std::endl;
}

void GameState::Enter()
{
	cout << "Entering Game..." << endl;
	BuildHexGrid();
	MapGrid();
	mouseDown = false;
	counter = 0;
	m_Merc = new Merc(ARCHER, Unit::Owner::PLAYER_1);
	m_Merc->setHex(m_pHexGrid[68]);
	m_Merc->setState(Unit::State::ACTIVE);

	m_EnemyMerc = new Merc(ARCHER, Unit::Owner::AI);
	m_EnemyMerc->setHex(m_pHexGrid[21]);
}

void GameState::Update()
{
	switch (current_state)
	{
	case NONE:

		ResetHexs();
		counter++;
		if (counter == 120)
		{
			current_state = PLAYER_MOVE;
			counter = 0;
		}
		//std::cout << " NONE STATE " << std::endl;

		break;
	case PLAYER_MOVE :
		for (auto hex : m_pHexList2)
		{
			hex->setInteractiveState(Hex::RUN);
		}
		for (auto hex : m_pHexList)
		{
			hex->setInteractiveState(Hex::DASH);
		}

		for (auto hex : m_Merc->getHex()->getNeighbours())
		{
			if (hex != nullptr && hex->getOccupied() != true)
			{
				m_pHexList.push_back(hex);
				for (auto hex2 : hex->getNeighbours())
				{
					if (hex2 != nullptr && hex2->getOccupied() != true)
						m_pHexList.push_back(hex2);
				// This doesn't work as it ends up replacing 
					for (auto hex3 : hex2->getNeighbours())
					{
						if (hex3 != nullptr && hex3->getOccupied() != true)
							m_pHexList2.push_back(hex3);
						for (auto hex4 : hex3->getNeighbours())
						{
							if (hex4 != nullptr && hex4->getOccupied() != true)
								m_pHexList2.push_back(hex4);
						} 
					}
				}
			}
		}

		for (int count = 0; count < (int)m_pHexGrid.size(); count++)
		{
			m_pHexGrid[count]->update();

			if (m_pHexGrid[count]->getMouseState() == Hex::MouseState::STATE_SELECTED && m_pHexGrid[count]->getOccupied() != true && m_pHexGrid[count]->getInteractiveState() == Hex::DASH)
			{
				Hex* tempHex;
				tempHex = m_pHexGrid[count];
				m_Merc->getHex()->setOccupied(false);
				m_Merc->setHex(tempHex);
				std::cout << "P1:ARCHER MOVED TO HEX: " << m_Merc->getHex()->getGridPosition().x << " " << m_Merc->getHex()->getGridPosition().y << std::endl;
				ResetHexs();
				current_state = PLAYER_FACING;
			
			}
		}



			m_Merc->update();
			m_EnemyMerc->update();
			//std::cout << " MOVE STATE" << std::endl;
			

		break;
	case PLAYER_ABILITY:

		break;
	case PLAYER_ATTACK:

		break;
	case PLAYER_FACING:
		for (auto hex : m_Merc->getHex()->getNeighbours())
		{
			if (hex != nullptr && hex != m_Merc->getHex())
			{
				m_pHexList.push_back(hex);
			}
		}

		for (auto hex : m_pHexList)
		{
			hex->setInteractiveState(Hex::FACEING);

		for (int count = 0; count < (int)m_pHexGrid.size(); count++)
		{
			m_pHexGrid[count]->update();

			if (m_pHexGrid[count]->getMouseState() == Hex::MouseState::STATE_SELECTED && m_pHexGrid[count] != m_Merc->getHex() && m_pHexGrid[count]->getInteractiveState() == Hex::FACEING)
			{
				Hex* tempHex;
				tempHex = m_pHexGrid[count];
				m_Merc->setFacingHex(tempHex);
				m_pSelectedHex = nullptr;
				ResetHexs();
				current_state = NONE;
			}
		}
		m_Merc->update();
		m_EnemyMerc->update();

		}
		//std::cout << " FACEING STATE" << std::endl;

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
	m_EnemyMerc->draw();


	SDL_Rect rectangle = {800,20 ,220,728 };
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 240, 0, 0, 50);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rectangle);

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

#include "PlayState.h"
#include "Util.h"
#include "Engine.h"
#include <algorithm>
using namespace std;

// Begin GameState.
GameState::GameState() : current_state(NONE) {}

void GameState::BuildHexGrid()
{
	int map_radius = 6;
	for (int q = -map_radius; q <= map_radius; q++) {
		int r1 = max(-map_radius, -q - map_radius);
		int r2 = min(map_radius, -q + map_radius);
		for (int r = r1; r <= r2; r++) {
			m_pHexGrid.push_back(new Hex(q, r, -q - r));
		}
	}
}

Hex* GameState::returnHex(glm::vec3 search)
{
	Hex* temp = NULL;

	for (auto hex : m_pHexGrid)
	{
		if (hex->getCubeCoordinate() == search)
		{
			temp = hex;
		}
	}

	return temp;
}

void GameState::MapGrid()
{

	for (auto hex : m_pHexGrid)
	{

		for (auto neighbour : hex->directions)
		{
			float x = hex->getCubeCoordinate().x + neighbour.x;
			float y = hex->getCubeCoordinate().y + neighbour.y;
			float z = hex->getCubeCoordinate().z + neighbour.z;

			if (x < 7.0 && x > -7.0 && y < 7.0 && y > -7.0 && z < 7.0 && z > -7.0)
			{
				Hex* temp = returnHex(glm::vec3(x, y, z));
				hex->m_pNeighbours.push_back(temp);
			}
		}
	}

}

void GameState::ResetHexs()
{
	m_pHexList.clear();
	m_pThreatenedHexes.clear();
	for (int count = 0; count < (int)m_pHexGrid.size(); count++)
	{
		m_pHexGrid[count]->setInteractiveState(Hex::INITIAL);
		m_pHexGrid[count]->setMouseState(Hex::STATE_OFF);
	}
	//std::cout << " HEXES RESET " << std::endl;
}

int GameState::SpawnObjects(Unit* spawned_object)
{
	Hex* randomHex = nullptr;
	auto randomHexIndex = 0;
	do
	{
		randomHexIndex = int(Util::RandomRange(0, m_pHexGrid.size() - 1));
		randomHex = m_pHexGrid[randomHexIndex];
	} while (randomHex->getPathfindingState() != Hex::PathfindingState::UNVISITED); // search for empty tile


	if (spawned_object->getHex() != nullptr)
	{
		spawned_object->getHex()->setPathfindingState(Hex::PathfindingState::UNVISITED);
	}

	spawned_object->setPosition(randomHex->getPosition());
	spawned_object->setHex(randomHex);

	return randomHexIndex;
}

void GameState::AddHexestoList()
{

}

void GameState::Enter()
{
	//cout << "Entering Game..." << endl;
	BuildHexGrid();
	MapGrid();
	mouseDown = false;
	counter = 0;
	m_ActiveUnitProfile = new UnitProfile(glm::vec2(20, 600));
	m_HoverUnitProfile = new UnitProfile(glm::vec2(1000, 600));

	m_Player1MercVec = { new Merc(ARCHER, Unit::Owner::PLAYER_1, 1, "Curly"),
						 new Merc(BARBARIAN, Unit::Owner::PLAYER_1, 0, "Larry"),
						 new Merc(MAGE, Unit::Owner::PLAYER_1, 2, "Moe"),
						 new Merc(PRIEST, Unit::Owner::PLAYER_1, 3, "Kyle") };
	for (int count = 0; count < 4; count++)
	{
		SpawnObjects(m_Player1MercVec[count]);
		m_Player1MercVec[count]->getHex()->setOccupier(m_Player1MercVec[count]);
		m_Player1MercVec[count]->rollInitiative();
		m_turnOrder.push_back(m_Player1MercVec[count]);
	}

	m_Player2MercVec = { new Merc(ARCHER, Unit::Owner::PLAYER_2, 1, "Ed"),
						 new Merc(BARBARIAN, Unit::Owner::PLAYER_2, 0, "Edd"),
						 new Merc(MAGE, Unit::Owner::PLAYER_2, 2, "Eddy"),
						 new Merc(PRIEST, Unit::Owner::PLAYER_2, 3, "Edison") };
	for (int count = 0; count < 4; count++)
	{
		SpawnObjects(m_Player2MercVec[count]);
		m_Player2MercVec[count]->getHex()->setOccupier(m_Player2MercVec[count]);
		m_Player2MercVec[count]->rollInitiative();
		m_turnOrder.push_back(m_Player2MercVec[count]);
	}

	m_turnOrder.sort([](const Merc* lhs, const Merc* rhs) {return lhs->getInitiative() > rhs->getInitiative(); });
}

void GameState::Update()
{
	switch (current_state)
	{
	case NONE:

		ResetHexs();
		m_CurrentMerc = nullptr;
		m_CurrentMerc = m_turnOrder.front();
		m_CurrentMerc->setState(Unit::State::ACTIVE);
		m_ActiveUnitProfile->setUnitReference(m_CurrentMerc);
		m_CurrentMerc->getHex()->setPathfindingState(Hex::PathfindingState::GOAL);

		counter++;

		if (counter == 30)
		{
			std::cout << "----------------" << m_CurrentMerc->getName() << "'s Turn" << "----------------" << std::endl;
			current_state = PLAYER_MOVE;
			counter = 0;
		}
		//std::cout << " NONE STATE " << std::endl;
		for (auto merc : m_Player1MercVec)
		{
			merc->update();
		}
		m_CurrentMerc->update();
		for (auto merc : m_Player2MercVec)
		{
			merc->update();
		}
		break;
	case PLAYER_MOVE:

		for (auto hex : m_pHexGrid)
		{
			if (hex != nullptr && hex->getPathfindingState() != Hex::PathfindingState::IMPASSABLE && hex->getGlobalValue() <= m_CurrentMerc->getJob()->getMoveRange())
			{
				hex->setInteractiveState(Hex::RUN);
				if (hex != nullptr && hex->getPathfindingState() != Hex::PathfindingState::IMPASSABLE && hex->getGlobalValue() <= m_CurrentMerc->getJob()->getDashRange())
					hex->setInteractiveState(Hex::DASH);
			}
		}
		for (int count = 0; count < (int)m_pHexGrid.size(); count++)
		{
			m_pHexGrid[count]->update();

			if (m_pHexGrid[count]->getMouseState() == Hex::MouseState::STATE_SELECTED && m_pHexGrid[count]->getOccupied() != true && m_pHexGrid[count]->getInteractiveState() == Hex::DASH)
			{
				Hex* tempHex;
				tempHex = m_pHexGrid[count];
				m_CurrentMerc->getHex()->setOccupied(false);
				m_CurrentMerc->getHex()->setOccupier(nullptr);
				m_CurrentMerc->setHex(tempHex);
				tempHex->setOccupier(m_CurrentMerc);
				//std::cout << m_CurrentMerc->getName() <<" MOVED TO HEX: " << m_CurrentMerc->getHex()->getGridPosition().x << " " << m_CurrentMerc->getHex()->getGridPosition().y << std::endl;
				ResetHexs();
				current_state = PLAYER_ATTACK;
			}
			else if (m_pHexGrid[count]->getMouseState() == Hex::MouseState::STATE_SELECTED && m_pHexGrid[count]->getOccupied() != true && m_pHexGrid[count]->getInteractiveState() == Hex::RUN)
			{
				Hex* tempHex;
				tempHex = m_pHexGrid[count];
				m_CurrentMerc->getHex()->setOccupied(false);
				m_CurrentMerc->getHex()->setOccupier(nullptr);
				m_CurrentMerc->setHex(tempHex);
				tempHex->setOccupier(m_CurrentMerc);
				//std::cout << m_CurrentMerc->getName() << " MOVED TO HEX: " << m_CurrentMerc->getHex()->getGridPosition().x << " " << m_CurrentMerc->getHex()->getGridPosition().y << std::endl;
				ResetHexs();
				current_state = PLAYER_FACING;
			}
		}

		for (auto merc : m_Player1MercVec)
		{
			merc->update();
		}
		for (auto merc : m_Player2MercVec)
		{
			merc->update();
		}
		//std::cout << " MOVE STATE" << std::endl;


		break;
	case PLAYER_ABILITY:

		break;
	case PLAYER_ATTACK:
		// Get closest target in range with highest threat
		for (auto hex : m_pHexGrid)
		{
			if (hex->getOccupied() == true && hex->getGlobalValue() <= m_CurrentMerc->getJob()->getAttackRange() && hex != m_CurrentMerc->getHex() && hex->getOccupier()->getOwner() != m_CurrentMerc->getOwner())
			{
				m_pThreatenedHexes.push_back(hex);
			}
		}

		m_pThreatenedHexes.sort([](const Hex* lhs, const Hex* rhs) {return lhs->getGlobalValue() < rhs->getGlobalValue(); });
		if (!m_pThreatenedHexes.empty())
			m_pSelectedHex = m_pThreatenedHexes.front();

		if (m_pSelectedHex == nullptr)
		{
			ResetHexs();
			current_state = PLAYER_FACING;
		}

		for (auto merc : m_turnOrder)
		{
			if (merc->getHex() == m_pSelectedHex && merc->getOwner() != m_CurrentMerc->getOwner() && merc != m_CurrentMerc)
			{
				merc->setState(Unit::State::TARGET);
				m_CurrentMerc->attack(merc);
				ResetHexs();
				m_pSelectedHex = nullptr;
				current_state = PLAYER_FACING;
				break;
			}
			else
				current_state = PLAYER_FACING;
		}
		break;
	case PLAYER_FACING:
		for (auto hex : m_CurrentMerc->getHex()->getNeighbours())
		{
			if (hex != nullptr && hex != m_CurrentMerc->getHex())
			{
				m_pHexList.push_back(hex);
			}
		}

		for (auto hex : m_pHexList)
		{
			hex->setInteractiveState(Hex::FACEING);
		}
		for (int count = 0; count < (int)m_pHexGrid.size(); count++)
		{
			m_pHexGrid[count]->update();

			if (m_pHexGrid[count]->getMouseState() == Hex::MouseState::STATE_SELECTED && m_pHexGrid[count] != m_CurrentMerc->getHex() && m_pHexGrid[count]->getInteractiveState() == Hex::FACEING)
			{
				Hex* tempHex;
				tempHex = m_pHexGrid[count];
				m_CurrentMerc->setFacingHex(tempHex);
				// Move turn to next merc in list
				m_turnOrder.push_back(m_CurrentMerc);
				m_turnOrder.pop_front();
				m_CurrentMerc->setState(Unit::State::NO_STATE);
				ResetHexs();
				current_state = NONE;
			}
		}
		for (auto merc : m_Player1MercVec)
		{
			merc->update();
		}
		for (auto merc : m_Player2MercVec)
		{
			merc->update();
		}
		break;
	}
	//	std::cout << " FACEING STATE" << std::endl;

	//std::cout << " updating..." << std::endl;
	for (auto hex : m_pHexGrid)
	{

		hex->computeGlobalValue(m_CurrentMerc->getHex()->getCubeCoordinate());

		if (hex->getMouseState() == Hex::STATE_HOVER && hex->getOccupied())
		{
			m_HoverUnitProfile->setUnitReference(hex->getOccupier());
		}
		else if (hex->getMouseState() == Hex::STATE_HOVER && !hex->getOccupied())
		{
			m_HoverUnitProfile->setUnitReference(nullptr);
		}
	}
	m_ActiveUnitProfile->update();
	m_HoverUnitProfile->update();

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


	for (auto merc : m_Player2MercVec)
	{
		merc->draw();
	}
	for (auto merc : m_Player1MercVec)
	{
		merc->draw();
	}

	//SDL_Rect rectangle = {820,20 ,500,350 };
	//SDL_Rect rectangle2 = { 820,400 ,500,350 };
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 240, 0, 0, 50);
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rectangle);
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rectangle2);
	m_ActiveUnitProfile->draw();
	m_HoverUnitProfile->draw();

	if (dynamic_cast<GameState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();
}

void GameState::Exit()
{
	//cout << "Exiting Game..." << endl;
}

void GameState::Resume()
{
	//cout << "Resuming Game..." << endl;
}

// End GameState.
#include "PlayState.h"
#include "Util.h"
#include "Engine.h"
#include <algorithm>
#include "EventManager.h"
#include <unordered_map>
using namespace std;

// Begin GameState.
GameState::GameState() : current_state(START) {}

int GameState::SpawnObjects(Unit* spawned_object)
{
	Hex* randomHex = nullptr;
	auto randomHexIndex = 0;
	do
	{
		randomHexIndex = int(Util::RandomRange(0, m_pHexGrid.ReturnGrid().size() - 1));
		randomHex = m_pHexGrid.ReturnGrid()[randomHexIndex];
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

void GameState::drawGameBoard()
{
	for (int count = 0; count < (int)m_pHexGrid.ReturnGrid().size(); count++)
	{
		m_pHexGrid.ReturnGrid()[count]->setCamPosition(m_GameCamera->getPosition());
		m_pHexGrid.ReturnGrid()[count]->draw();
	}

	for (auto merc : m_Player2MercVec)
	{
		merc->setCamPosition(m_GameCamera->getPosition());
		merc->draw();
	}
	for (auto merc : m_Player1MercVec)
	{
		merc->setCamPosition(m_GameCamera->getPosition());
		merc->draw();
	}

}

void GameState::drawUI()
{
	m_ActiveUnitProfile->draw();
	m_HoverUnitProfile->draw();
	m_MoveButton->draw();
	m_AttackButton->draw();
	m_AbilityButton->draw();
	m_EndButton->draw();
}

void GameState::InitializeButtons()
{
	m_MoveButton = new Button("Img/move token.png", "MoveButton", glm::vec2(400, 650), true, BUTTON);
	m_MoveButton->addEventListener(CLICK, [&]()-> void
		{
			MoveClicked = !MoveClicked;
			current_state = MOVE;
			
		});
	m_MoveButton->addEventListener(MOUSE_OVER, [&]()-> void
		{
			if (!MoveClicked)
			{
				std::vector<Hex*> temp = m_pHexGrid.GetReachableHexs(m_CurrentMerc->getHex(), m_CurrentMerc->getJob()->getMoveRange());
				m_pHexGrid.ResetHexs();
				std::vector<Hex*> temp2 = m_pHexGrid.GetReachableHexs(m_CurrentMerc->getHex(), m_CurrentMerc->getJob()->getDashRange());

				for (auto hex : temp)
				{
					hex->setInteractiveState(Hex::RUN);
				}
				for (auto hex : temp2)
				{
					hex->setInteractiveState(Hex::DASH);
				}

			}
		});
	m_MoveButton->addEventListener(MOUSE_OUT, [&]()-> void
		{
			if (!MoveClicked)
			{
				m_pHexGrid.ResetHexs();
			}
		});

	m_AttackButton = new Button("Img/attack token.png", "AttackButton", glm::vec2(500, 650), true, BUTTON);
	m_AttackButton->addEventListener(CLICK, [&]()-> void
		{
			current_state = ATTACK;
		});
	m_AttackButton->addEventListener(MOUSE_OVER, [&]()-> void
		{
			for (auto hex : m_pHexGrid.ReturnGrid())
			{
				if (hex != nullptr && hex->getGlobalValue() <= m_CurrentMerc->getJob()->getAttackRange())
				{
					hex->setInteractiveState(Hex::THREAT);
				}
			}
		});
	m_AttackButton->addEventListener(MOUSE_OUT, [&]()-> void
		{
			m_pHexGrid.ResetHexs();
		});

	m_AbilityButton = new Button("Img/ability token.png", "AbilityButton", glm::vec2(600, 650), true, BUTTON);
	m_AbilityButton->m_state = INACTIVE;

	m_EndButton = new Button("Img/end token.png", "EndButton", glm::vec2(700, 650), true, BUTTON);
	m_EndButton->addEventListener(CLICK, [&]()-> void
		{
			current_state = FACING;
		});
}

void GameState::TurnStart()
{
	m_pHexGrid.ResetHexs();
	if (MoveClicked)
		MoveClicked = false;
	m_CurrentMerc = nullptr;
	m_CurrentMerc = m_turnOrder.front();
	m_CurrentMerc->setState(Unit::State::ACTIVE);
	m_ActiveUnitProfile->setUnitReference(m_CurrentMerc);
	m_CurrentMerc->getHex()->setPathfindingState(Hex::PathfindingState::GOAL);
	m_MoveButton->m_state = NONE;
	m_AttackButton->m_state = NONE;
	m_AbilityButton->m_state = INACTIVE;
	m_EndButton->m_state = NONE;
	m_GameCamera->setPosition(glm::vec2(m_CurrentMerc->getPosition().x - Config::SCREEN_WIDTH / 2, m_CurrentMerc->getPosition().y - Config::SCREEN_HEIGHT / 3));

	counter++;

	if (counter == 30)
	{
		std::cout << "----------------" << m_CurrentMerc->getName() << "'s Turn" << "----------------" << std::endl;
		current_state = IDLE;
		counter = 0;
	}

	for (auto hex : m_pHexGrid.ReturnGrid())
	{
		hex->computeGlobalValue(m_CurrentMerc->getHex()->getCubeCoordinate());
	}
	//std::cout << " NONE STATE " << std::endl;
}

void GameState::TurnIdle()
{
}

void GameState::TurnMove()
{
	//for (auto hex : m_pHexGrid.ReturnGrid())
	//{
	//	if (m_AttackButton->m_state != INACTIVE)
	//	{
	//		if (hex != nullptr && hex->getPathfindingState() != Hex::PathfindingState::IMPASSABLE && hex->getGlobalValue() <= m_CurrentMerc->getJob()->getMoveRange())
	//		{
	//			hex->setInteractiveState(Hex::RUN);
	//		}
	//	}
	//		if (hex != nullptr && hex->getPathfindingState() != Hex::PathfindingState::IMPASSABLE && hex->getGlobalValue() <= m_CurrentMerc->getJob()->getDashRange())
	//			hex->setInteractiveState(Hex::DASH);
	//}

	for (int count = 0; count < (int)m_pHexGrid.ReturnGrid().size(); count++)
	{

		if (m_pHexGrid.ReturnGrid()[count]->getMouseState() == Hex::MouseState::STATE_SELECTED && m_pHexGrid.ReturnGrid()[count]->getOccupied() != true && m_pHexGrid.ReturnGrid()[count]->getInteractiveState() == Hex::DASH)
		{
			Hex* tempHex;
			tempHex = m_pHexGrid.ReturnGrid()[count];
			m_CurrentMerc->getHex()->setOccupied(false);
			m_CurrentMerc->getHex()->setOccupier(nullptr);
			m_CurrentMerc->setHex(tempHex);
			tempHex->setOccupier(m_CurrentMerc);
			//std::cout << m_CurrentMerc->getName() <<" MOVED TO HEX: " << m_CurrentMerc->getHex()->getGridPosition().x << " " << m_CurrentMerc->getHex()->getGridPosition().y << std::endl;
			m_pHexGrid.ResetHexs();
			m_MoveButton->m_state = INACTIVE;
			current_state = IDLE;
		}
		else if (m_pHexGrid.ReturnGrid()[count]->getMouseState() == Hex::MouseState::STATE_SELECTED && m_pHexGrid.ReturnGrid()[count]->getOccupied() != true && m_pHexGrid.ReturnGrid()[count]->getInteractiveState() == Hex::RUN)
		{
			Hex* tempHex;
			tempHex = m_pHexGrid.ReturnGrid()[count];
			m_CurrentMerc->getHex()->setOccupied(false);
			m_CurrentMerc->getHex()->setOccupier(nullptr);
			m_CurrentMerc->setHex(tempHex);
			tempHex->setOccupier(m_CurrentMerc);
			//std::cout << m_CurrentMerc->getName() << " MOVED TO HEX: " << m_CurrentMerc->getHex()->getGridPosition().x << " " << m_CurrentMerc->getHex()->getGridPosition().y << std::endl;
			m_pHexGrid.ResetHexs();
			m_MoveButton->m_state = INACTIVE;
			m_AttackButton->m_state = INACTIVE;
			current_state = IDLE;
		}
	}

}

void GameState::TurnAttack()
{
	// Get closest target in range with highest threat
	for (auto hex : m_pHexGrid.ReturnGrid())
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
		m_pHexGrid.ResetHexs();
		m_AttackButton->m_state = INACTIVE;
		current_state = IDLE;
	}

	for (auto merc : m_turnOrder)
	{
		if (merc->getHex() == m_pSelectedHex && merc->getOwner() != m_CurrentMerc->getOwner() && merc != m_CurrentMerc)
		{
			merc->setState(Unit::State::TARGET);
			m_CurrentMerc->attack(merc);
			m_pHexGrid.ResetHexs();
			m_pSelectedHex = nullptr;
			m_AttackButton->m_state = INACTIVE;
			current_state = IDLE;
			break;
		}
		else {
			m_AttackButton->m_state = INACTIVE;
			current_state = IDLE;
		}
	}
}

void GameState::TurnFacing()
{
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

	for (int count = 0; count < (int)m_pHexList.size(); count++)
	{

		if (m_pHexList[count]->getMouseState() == Hex::MouseState::STATE_SELECTED && m_pHexList[count] != m_CurrentMerc->getHex() && m_pHexList[count]->getInteractiveState() == Hex::FACEING)
		{
			Hex* tempHex;
			tempHex = m_pHexList[count];
			m_CurrentMerc->setFacingHex(tempHex);
			// Move turn to next merc in list
			m_turnOrder.push_back(m_CurrentMerc);
			m_turnOrder.pop_front();
			m_CurrentMerc->setState(Unit::State::NO_STATE);
			m_pHexGrid.ResetHexs();
			current_state = START;
		}
	}
}

void GameState::TurnEnd()
{
}

void GameState::Enter()
{
	//cout << "Entering Game..." << endl;
	m_pHexGrid.BuildHexGrid();
	m_pHexGrid.MapGrid();
	mouseDown = false;
	counter = 0;
	m_ActiveUnitProfile = new UnitProfile(glm::vec2(20, 550));
	m_HoverUnitProfile = new UnitProfile(glm::vec2(900, 550));

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

	m_GameCamera = new Camera(glm::vec2(50, 50));
	InitializeButtons();

	m_turnOrder.sort([](const Merc* lhs, const Merc* rhs) {return lhs->getInitiative() > rhs->getInitiative(); });
}

void GameState::Update()
{
	switch (current_state)
	{
	case START:
		TurnStart();
		break;
	case IDLE:
		TurnIdle();
		break;
	case MOVE:
		TurnMove();
		break;
	case ABILITY:
		break;
	case ATTACK:
		TurnAttack();
		break;
	case FACING:
		TurnFacing();
		break;
	}
	//	std::cout << " FACEING STATE" << std::endl;

	//std::cout << " updating..." << std::endl;
	for (auto hex : m_pHexGrid.ReturnGrid())
	{
		hex->update();

		//hex->computeGlobalValue(m_CurrentMerc->getHex()->getCubeCoordinate());

		if (hex->getMouseState() == Hex::STATE_HOVER && hex->getOccupied())
		{
			m_HoverUnitProfile->setUnitReference(hex->getOccupier());
		}
		else if (hex->getMouseState() == Hex::STATE_HOVER && !hex->getOccupied())
		{
			m_HoverUnitProfile->setUnitReference(nullptr);
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

	m_ActiveUnitProfile->update();
	m_HoverUnitProfile->update();

	m_MoveButton->update();
	m_AttackButton->update();
	m_AbilityButton->update();
	m_EndButton->update();
}

void GameState::HandleEvents()
{
	//State::HandleEvents();
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_GameCamera->setPosition(glm::vec2(m_GameCamera->getPosition().x - 10, m_GameCamera->getPosition().y));
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_GameCamera->setPosition(glm::vec2(m_GameCamera->getPosition().x + 10, m_GameCamera->getPosition().y));
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_GameCamera->setPosition(glm::vec2(m_GameCamera->getPosition().x, m_GameCamera->getPosition().y - 10));
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_GameCamera->setPosition(glm::vec2(m_GameCamera->getPosition().x, m_GameCamera->getPosition().y + 10));
	}

	//if (m_MoveButton->m_state == CLICKED)
	//{
	//	current_state = MOVE;
	//}
	//if (m_EndButton->m_state == CLICKED)
	//{
	//	current_state = FACING;
	//}
	//if (m_AttackButton->m_state == CLICKED)
	//{
	//	current_state = ATTACK;
	//}
}

void GameState::Render()
{
	//cout << "Rendering Game..." << endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 25, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer()); // Clear the screen with the draw color.
	// hex



	drawGameBoard();
	drawUI();

	//SDL_Rect rectangle = {820,20 ,500,350 };
	//SDL_Rect rectangle2 = { 820,400 ,500,350 };
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 240, 0, 0, 50);
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rectangle);
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rectangle2);


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

std::vector<Hex*> GameState::ReachableHexs(Hex* start, int movement)
{
	std::vector<Hex*> visited;


	return visited;
}

// End GameState.
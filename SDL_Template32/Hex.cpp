#include "Hex.h"
#include "Engine.h"
#include "Util.h"
#include "Unit.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Hex::Hex(glm::vec2 worldPosition, glm::vec2 gridPosition) : mouseHover(false), m_MouseState(STATE_OFF), m_pGridPosition(gridPosition)
{
	TheTextureManager::Instance()->load("Img/Hex Tileset2.png", "hex", Engine::Instance().GetRenderer());
	TheTextureManager::Instance()->load("Img/selector.png", "selector", Engine::Instance().GetRenderer());

	setPosition(worldPosition);
	setWidth(40);
	setHeight(40);
	setType(GameObjectType::HEX);
	
	setOccupied(false);

	BuildHex();
	std::ostringstream tempLabel;
	tempLabel << std::fixed << std::setprecision(1) << m_globalGoalValue;
	auto labelstring = tempLabel.str();
	SDL_Color black{ 0, 0, 0, 255 };
	auto valueLabelPosition = glm::vec2(getPosition().x + 30 , getPosition().y + 40);
	m_pValueLabel = new Label(labelstring, "Consolas", 14, black, valueLabelPosition, true);

	m_pNeighbours = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
}

Hex::~Hex()
{

}

void Hex::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;
	SDL_Rect rectangle = { xComponent,yComponent,64,64 };
	
	TheTextureManager::Instance()->drawHex("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), 0,(int)m_HexType, (int)m_InteractiveState);
	if(m_MouseState != STATE_OFF)
	TheTextureManager::Instance()->drawSelector("selector", xComponent, yComponent, Engine::Instance().GetRenderer(), 0, (int)m_MouseState);
	m_pValueLabel->draw();
}

void Hex::update()
{
	bool mousecol = mouseCol();
	switch (m_MouseState)
	{
	case STATE_OFF:
		if (mousecol)
		{
			m_MouseState = STATE_HOVER;
		}
		//cout << " state off" << std::endl;
		break;
	case STATE_HOVER:
		if (!mousecol)
		{
			m_MouseState = STATE_OFF;
		}
		 if (mousecol && Engine::Instance().GetMouseState(0))
		{
			m_MouseState = STATE_SELECTED;
			
		}
			//std::cout << " state hover " << std::endl;
	
		break;
	case STATE_SELECTED:
		if (!Engine::Instance().GetMouseState(0))
		{
			if (mousecol)
			{
				m_MouseState = STATE_HOVER;
				// Execute new "callback".

			}
			else
				m_MouseState = STATE_OFF;
		}
		break;
	}

	std::ostringstream tempLabel;
	tempLabel << std::fixed << std::setprecision(1) << m_localGoalValue;
	const auto labelstring = tempLabel.str();
	m_pValueLabel->setText(labelstring);
}

void Hex::clean()
{

}

glm::vec2 Hex::getGridPosition()
{
	return m_pGridPosition;
}

Hex* Hex::getUp()
{
	return m_pNeighbours[UP];
}

Hex* Hex::getUpRight()
{
	return m_pNeighbours[UPRIGHT];
}

Hex* Hex::getDownRight()
{
	return m_pNeighbours[DOWNRIGHT];
}

Hex* Hex::getDown()
{
	return m_pNeighbours[DOWN];
}

Hex* Hex::getDownLeft()
{
	return m_pNeighbours[DOWNLEFT];
}

Hex* Hex::getUpleft()
{
	return m_pNeighbours[UPLEFT];
}

void Hex::setUp(Hex* hex)
{
	m_pNeighbours[UP] = hex;
}

void Hex::setUpRight(Hex* hex)
{
	m_pNeighbours[UPRIGHT] = hex;
}

void Hex::setDownRight(Hex* hex)
{
	m_pNeighbours[DOWNRIGHT] = hex;
}

void Hex::setDown(Hex* hex)
{
	m_pNeighbours[DOWN] = hex;
}

void Hex::setDownLeft(Hex* hex)
{
	m_pNeighbours[DOWNLEFT] = hex;
}

void Hex::setUpLeft(Hex* hex)
{
	m_pNeighbours[UPLEFT] = hex;
}


std::vector<Hex*> Hex::getNeighbours() const
{
	return m_pNeighbours;
}

Hex::MouseState Hex::getMouseState()
{
	return m_MouseState;
}

Hex::InteractiveState Hex::getInteractiveState()
{
	return m_InteractiveState;
}

Hex::PathfindingState Hex::getPathfindingState()
{
	return m_PathfindingState;
}

void Hex::setInteractiveState(InteractiveState newstate)
{
	m_InteractiveState = newstate;
}

void Hex::setPathfindingState(PathfindingState newstate)
{
	m_PathfindingState = newstate;
}

void Hex::setMouseState(MouseState newstate)
{
	m_MouseState = newstate;
}

bool Hex::getOccupied()
{
	return m_pOccupied;
}

void Hex::setOccupied(bool newbool)
{
	m_pOccupied = newbool;
}

void Hex::setOccupier(Merc* newunit)
{
	m_Occupier = newunit;
}

void Hex::setHexParent(Hex* new_hex)
{
	m_hexPathfindingParent = new_hex;
}

void Hex::setHexCost(int new_value)
{
	m_HexMoveCost = new_value;
}

void Hex::setLocalValue(float new_value)
{
	m_localGoalValue = new_value;
}

void Hex::setGlobalValue(float new_value)
{
	m_globalGoalValue = new_value;
}

bool Hex::mouseCol()
{
	int mx = Engine::Instance().GetMousePos().x;
	int my = Engine::Instance().GetMousePos().y;
	return (mx < (getPosition().x + getWidth()) && mx > getPosition().x &&
		my < (getPosition().y + getHeight()) && my > getPosition().y);
}

void Hex::setHover(bool h)
{
	mouseHover = h;
}

void Hex::BuildHex()
{
	
	m_HexType = PLAINS;

	int randnum = rand() % 5;
	if (randnum == 4)
		m_HexType = WALL;
	else if (randnum == 3)
		m_HexType = ROUGH;

	switch (m_HexType)
	{
	case PLAINS:
		setHexCost(1);
		m_InteractiveState = INITIAL;
		m_PathfindingState = UNVISITED;
		break;
	case WALL:
		setHexCost(1);
		m_InteractiveState = INITIAL;
		m_PathfindingState = IMPASSABLE;
		break;
	case ROUGH:
		setHexCost(1);
		m_InteractiveState = INITIAL;
		m_PathfindingState = UNVISITED;
		break;
	}
}

float Hex::computeGlobalValue(const glm::vec2 goal_location)
{
	m_goalLocation = goal_location;

	// declare heuristic;
	auto h = 0.0f;

	glm::vec3 cube_coord_a = (Util::offset_to_cube(getGridPosition()));
	glm::vec3 cube_coord_b = (Util::offset_to_cube(goal_location));

	h = (abs(cube_coord_a.x - cube_coord_b.x) + abs(cube_coord_a.y - cube_coord_b.y) + abs(cube_coord_a.z - cube_coord_b.z)) / 2;
	
		/*h = (abs(getGridPosition().x - goal_location.x) +
			 abs(getGridPosition().x + getGridPosition().y - goal_location.x - goal_location.y) +
			 abs(getGridPosition().y - goal_location.y)) /2;*/

		//return (abs(a.q - b.q)
		//	+ abs(a.q + a.r - b.q - b.r)
		//	+ abs(a.r - b.r)) / 2

	/*	function offset_distance(a, b) :
			var ac = offset_to_cube(a)
			var bc = offset_to_cube(b)
			return cube_distance(ac, bc)*/

	m_globalGoalValue = h;



	return m_globalGoalValue;
}

float Hex::computeLocalValue(Hex* active_hex)
{
	active_hex->setPathfindingState(GOAL);
	Hex* current_hex = this;
	m_openList.push_back(current_hex);
	std::vector<Hex*> adjacent = current_hex->getNeighbours();

	while (!m_openList.empty() && current_hex->getPathfindingState() != GOAL)
	{
		m_openList.sort([](const Hex* lhs, const Hex* rhs) {return lhs->getGlobalValue() < rhs->getGlobalValue(); });



		while (!m_openList.empty() && m_openList.front()->b_visited)
			m_openList.pop_front();


		if (m_openList.empty() /*|| current_tile->getTileState() == GOAL*/)
			break;

		current_hex = m_openList.front();
		current_hex->b_visited = true;


		std::vector<Hex*> adjacent = current_hex->getNeighbours();
		for (auto hex : adjacent)
		{

			if (hex != nullptr)
			{
				if (hex->getPathfindingState() == GOAL)
				{
					hex->setHexParent(current_hex);
					Hex* current = hex;
					while (current->getHexParent() != nullptr)
					{

						m_path.push_back(current);
						current = current->getHexParent();
						
						
					}
					current_hex = hex;
					m_openList.clear();
					break;
				}
				if (!hex->b_visited && hex->getPathfindingState() != IMPASSABLE)
				{
					m_openList.push_back(hex);
					
				}
				else
				{
					continue;
				}

				float tempLocal = current_hex->getLocalValue() + hex->getHexCost();
				if (tempLocal > hex->getLocalValue())
				{
					hex->setHexParent(current_hex);
					hex->setLocalValue(tempLocal);
				}


			}
		}
	}

	

	return m_localGoalValue;
}

float Hex::getGlobalValue() const
{
	return m_globalGoalValue;
}

float Hex::getLocalValue() const
{
	return m_localGoalValue;
}

Merc* Hex::getOccupier()
{
	return m_Occupier;
}

int Hex::getHexCost()
{
	return m_HexMoveCost;
}

Hex* Hex::getHexParent()
{
	return m_hexPathfindingParent;
}

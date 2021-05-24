#include "Hex.h"
#include "Engine.h"
#include "Util.h"
#include <iostream>
#include <sstream>
#include <iomanip>

glm::vec2 hex_to_pixel(Layout layout, glm::vec3 h) {
	const Orientation& M = layout.orientation;
	double x = (M.f0 * h.x + M.f1 * h.y) * layout.size.x;
	double y = (M.f2 * h.x + M.f3 * h.y) * layout.size.y;
	return glm::vec2(x + layout.origin.x, y + layout.origin.y);
}

Hex::Hex(int x, int y, int z) : m_hexLayout(Layout(layout_flat, glm::vec2(32.0, 34.0), glm::vec2(600.0,375.0))), m_cubeCoordinate(glm::vec3(x, y, z)), mouseHover(false), m_MouseState(STATE_OFF), m_PathfindingState(UNVISITED)
{
    TheTextureManager::Instance()->load("Img/Hex Tileset2.png", "hex", Engine::Instance().GetRenderer());
    TheTextureManager::Instance()->load("Img/selector.png", "selector", Engine::Instance().GetRenderer());

	BuildHex();
	setHeight(40);
	setWidth(40);
	
	setPosition(hex_to_pixel(m_hexLayout, getCubeCoordinate()));

	directions[0] = glm::vec3(1.0, -1.0, 0.0);	//UP RIGHT
	directions[1] = glm::vec3(1.0, 0.0, -1.0);	//DOWN RIGHT
	directions[2] = glm::vec3(0.0, 1.0, -1.0);	// UP
	directions[3] = glm::vec3(-1.0, 1.0, 0.0);	//UP LEFT
	directions[4] = glm::vec3(-1.0, 0.0, 1.0);	// DOWN LEFT
	directions[5] = glm::vec3(0.0, -1.0, 1.0);	//DOWN

	std::ostringstream tempLabel;
	tempLabel << std::fixed << std::setprecision(1) << m_globalGoalValue;
	auto labelstring = tempLabel.str();
	SDL_Color black{ 0, 0, 0, 255 };
	auto valueLabelPosition = glm::vec2(getPosition().x + 30, getPosition().y + 40);
	m_pValueLabel = new Label(labelstring, "Consolas", 14, black, valueLabelPosition, true);

	SetListenEvents();
}

Hex::~Hex()
{
}

void Hex::draw()
{
	const int xComponent = getPosition().x - getCamPosition().x;
	const int yComponent = getPosition().y - getCamPosition().y;

    TheTextureManager::Instance()->drawHex("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), 0, (int)m_HexType, (int)m_InteractiveState);
    if (m_MouseState != STATE_OFF)
        TheTextureManager::Instance()->drawSelector("selector", xComponent, yComponent, Engine::Instance().GetRenderer(), 0, (int)m_MouseState);

	m_pValueLabel->setCamPosition(getCamPosition());
	m_pValueLabel->draw();
}

void Hex::update()
{
	//check if mouse is over the Button
	onMouseOver();

	// check if mouse outside the Button
	onMouseOut();

	// check if left mouse is clicked
	onLeftMouseButtonClick();

	std::ostringstream tempLabel;
	tempLabel << std::fixed << std::setprecision(1) << m_globalGoalValue;
	const auto labelstring = tempLabel.str();
	m_pValueLabel->setText(labelstring);
}

void Hex::SetListenEvents()
{
	addEventListener(MOUSE_OVER, [&]()-> void
		{
			m_MouseState = STATE_HOVER;
		});
	addEventListener(MOUSE_OUT, [&]()-> void
		{
			m_MouseState = STATE_OFF;
		});
	addEventListener(CLICK, [&]()-> void
		{
			m_MouseState = STATE_SELECTED;
		});
}

bool Hex::mouseCol()
{

	int mx = EventManager::Instance().getMousePosition().x + getCamPosition().x;
	int my = EventManager::Instance().getMousePosition().y + getCamPosition().y;
	return (mx < (getPosition().x + getWidth()) && mx > getPosition().x &&
		my < (getPosition().y + getHeight()) && my > getPosition().y);
}

void Hex::clean()
{

}

glm::vec3 Hex::getCubeCoordinate()
{
    return m_cubeCoordinate;
}

Hex::MouseState Hex::getMouseState()
{
	return m_MouseState;
}

Hex::InteractiveState Hex::getInteractiveState()
{
	return m_InteractiveState;
}

bool Hex::getOccupied()
{
	return m_pOccupied;
}

Merc* Hex::getOccupier()
{
	return m_Occupier;
}

float Hex::getGlobalValue() const
{
	return m_globalGoalValue;
}

Hex* Hex::getParentHex()
{
	return m_pHexParent;
}

int Hex::getCost()
{
	return m_pHexCost;
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

void Hex::setOccupied(bool newbool)
{
	m_pOccupied = newbool;
}

void Hex::setOccupier(Merc* newunit)
{
	m_Occupier = newunit;
}

void Hex::setParentHex(Hex* newhex)
{
	m_pHexParent = newhex;
}

Hex::PathfindingState Hex::getPathfindingState()
{
	return m_PathfindingState;
}

std::vector<Hex*> Hex::getNeighbours() const
{
	return m_pNeighbours;
}

Hex Hex::Hex_add(Hex a, Hex b)
{
    return Hex(a.getCubeCoordinate().x + b.getCubeCoordinate().x,
                a.getCubeCoordinate().y + b.getCubeCoordinate().y,
                a.getCubeCoordinate().z + b.getCubeCoordinate().z);
}

Hex Hex::Hex_subtract(Hex a, Hex b)
{
    return Hex(a.getCubeCoordinate().x + b.getCubeCoordinate().x,
        a.getCubeCoordinate().y + b.getCubeCoordinate().y,
        a.getCubeCoordinate().z + b.getCubeCoordinate().z);
}

Hex Hex::Hex_multiply(Hex a, int k)
{
    return Hex(a.getCubeCoordinate().x * k,
                a.getCubeCoordinate().y * k,
                a.getCubeCoordinate().z * k);
}

bool operator == (Hex a, Hex b) {
    return a.getCubeCoordinate().x == b.getCubeCoordinate().x && a.getCubeCoordinate().y == b.getCubeCoordinate().y && a.getCubeCoordinate().z == b.getCubeCoordinate().z;
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
		m_InteractiveState = INITIAL;
		m_PathfindingState = UNVISITED;
		m_pHexCost = 1;
		break;
	case WALL:
		m_InteractiveState = INITIAL;
		m_PathfindingState = IMPASSABLE;
		m_pHexCost = 0;
		break;
	case ROUGH:
		m_InteractiveState = INITIAL;
		m_PathfindingState = UNVISITED;
		m_pHexCost = 2;
		break;
	}
}

float Hex::computeGlobalValue(const glm::vec3 goal_location)
{
	// declare heuristic;
	auto h = 0.0f;

	glm::vec3 cube_coord_a = getCubeCoordinate();
	glm::vec3 cube_coord_b = goal_location;

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
	float g = m_pHexCost - 1.0f;

	m_globalGoalValue = h + g;

	return m_globalGoalValue;
}

void Hex::aStarpathfinding(Hex* end)
{
	Hex* current_hex = this;

	m_pOpenList.push_back(current_hex);
	std::vector<Hex*> visited;

	while (!m_pOpenList.empty() && current_hex != end)
	{
		m_pOpenList.sort([](const Hex* lhs, const Hex* rhs) {return lhs->getGlobalValue() < rhs->getGlobalValue(); });

		for (auto hex : visited)
		{
			if (!m_pOpenList.empty() && m_pOpenList.front() == hex)
				m_pOpenList.pop_front();
		}

		if (m_pOpenList.empty())
			break;

		current_hex = m_pOpenList.front();
		visited.push_back(current_hex);

		std::vector<Hex*> adjacent = current_hex->getNeighbours();
		for (auto hex : adjacent)
		{
			if (hex != nullptr)
			{
				if (hex == end)
				{
					hex->setParentHex(current_hex);
					Hex* current = end;
					while (current->getParentHex() != nullptr)
					{
						m_pPath.push_back(current);
						current = current->getParentHex();
					}

					current_hex = hex;
					break;
				}
				for (auto visitedhex : visited)
				{
					if (hex != visitedhex && hex->getPathfindingState() != IMPASSABLE)
					{
						m_pOpenList.push_back(hex);
					}
					else
						continue;
				}

				float tempLocal = current_hex->m_localGoalValue + current_hex->m_pHexCost;

				if (tempLocal < hex->m_localGoalValue)
				{
					hex->setParentHex(current_hex);
					hex->m_localGoalValue = tempLocal;
					hex->m_globalGoalValue = hex->computeGlobalValue(end->getCubeCoordinate()) + hex->m_localGoalValue;
				}
			}
		}
	}
}

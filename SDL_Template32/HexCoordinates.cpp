#include "HexCoordinates.h"
#include "Engine.h"
#include "Util.h"

glm::vec2 hex_to_pixel(Layout layout, glm::vec3 h) {
	const Orientation& M = layout.orientation;
	double x = (M.f0 * h.x + M.f1 * h.y) * layout.size.x;
	double y = (M.f2 * h.x + M.f3 * h.y) * layout.size.y;
	return glm::vec2(x + layout.origin.x, y + layout.origin.y);
}

Hex::Hex(int x, int y, int z) : m_hexLayout(Layout(layout_flat, glm::vec2(32.0, 34.0), glm::vec2(400.0,375.0))), m_cubeCoordinate(glm::vec3(x, y, z)), mouseHover(false), m_MouseState(STATE_OFF), m_PathfindingState(UNVISITED)
{
    TheTextureManager::Instance()->load("Img/Hex Tileset2.png", "hex", Engine::Instance().GetRenderer());
    TheTextureManager::Instance()->load("Img/selector.png", "selector", Engine::Instance().GetRenderer());

	BuildHex();
	setHeight(40);
	setWidth(40);
	
	setPosition(hex_to_pixel(m_hexLayout, getCubeCoordinate()));

	directions[0] = glm::vec3(1.0, -1.0, 0.0);	//DOWN RIGHT
	directions[1] = glm::vec3(1.0, 0.0, -1.0);	//UP RIGHT
	directions[2] = glm::vec3(0.0, 1.0, -1.0);	// UP
	directions[3] = glm::vec3(-1.0, 1.0, 0.0);	//UP LEFT
	directions[4] = glm::vec3(-1.0, 0.0, 1.0);	// DOWN LEFT
	directions[5] = glm::vec3(0.0, -1.0, 1.0);	//DOWN
}

Hex::~Hex()
{
}

void Hex::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;
    SDL_Rect rectangle = { xComponent,yComponent,64,64 };

    TheTextureManager::Instance()->drawHex("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), 0, (int)m_HexType, (int)m_InteractiveState);
    if (m_MouseState != STATE_OFF)
        TheTextureManager::Instance()->drawSelector("selector", xComponent, yComponent, Engine::Instance().GetRenderer(), 0, (int)m_MouseState);
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
}

bool Hex::mouseCol()
{

	int mx = Engine::Instance().GetMousePos().x;
	int my = Engine::Instance().GetMousePos().y;
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
		break;
	case WALL:
		m_InteractiveState = INITIAL;
		m_PathfindingState = IMPASSABLE;
		break;
	case ROUGH:
		m_InteractiveState = INITIAL;
		m_PathfindingState = UNVISITED;
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
	float g = 1;

	m_globalGoalValue = h;



	return m_globalGoalValue;
}
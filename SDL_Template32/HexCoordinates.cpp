#include "HexCoordinates.h"
#include "Engine.h"
#include "Util.h"

struct Orientation {
	const double f0, f1, f2, f3;
	const double b0, b1, b2, b3;
	const double start_angle; // in multiples of 60°
	Orientation(double f0_, double f1_, double f2_, double f3_,
		double b0_, double b1_, double b2_, double b3_,
		double start_angle_)
		: f0(f0_), f1(f1_), f2(f2_), f3(f3_),
		b0(b0_), b1(b1_), b2(b2_), b3(b3_),
		start_angle(start_angle_) {}
};

const Orientation layout_flat
= Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
	2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
	0.0);

struct Layout {
	const Orientation orientation;
	const glm::vec2 size;
	const glm::vec2 origin;
	Layout(Orientation temporientation, glm::vec2 tempsize, glm::vec2 temporigin)
		: orientation(temporientation), size(tempsize), origin(temporigin) {}
};

HexCoordinates::HexCoordinates(int x, int y, int z) : m_cubeCoordinate(glm::vec3(x,y,z)), mouseHover(false), m_MouseState(STATE_OFF), m_PathfindingState(UNVISITED)
{
    TheTextureManager::Instance()->load("Img/Hex Tileset2.png", "hex", Engine::Instance().GetRenderer());
    TheTextureManager::Instance()->load("Img/selector.png", "selector", Engine::Instance().GetRenderer());

	BuildHex();

}

HexCoordinates::~HexCoordinates()
{
}

void HexCoordinates::draw()
{
    const int xComponent = getPosition().x;
    const int yComponent = getPosition().y;
    SDL_Rect rectangle = { xComponent,yComponent,64,64 };

    TheTextureManager::Instance()->drawHex("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), 0, (int)m_HexType, (int)m_InteractiveState);
    if (m_MouseState != STATE_OFF)
        TheTextureManager::Instance()->drawSelector("selector", xComponent, yComponent, Engine::Instance().GetRenderer(), 0, (int)m_MouseState);
}

void HexCoordinates::update()
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

bool HexCoordinates::mouseCol()
{
	int mx = Engine::Instance().GetMousePos().x;
	int my = Engine::Instance().GetMousePos().y;
	return (mx < (getPosition().x + getWidth()) && mx > getPosition().x &&
		my < (getPosition().y + getHeight()) && my > getPosition().y);
}

void HexCoordinates::clean()
{
}

glm::vec3 HexCoordinates::getCubeCoordinate()
{
    return m_cubeCoordinate;
}

HexCoordinates HexCoordinates::Hex_add(HexCoordinates a, HexCoordinates b)
{
    return HexCoordinates(a.getCubeCoordinate().x + b.getCubeCoordinate().x,
                a.getCubeCoordinate().y + b.getCubeCoordinate().y,
                a.getCubeCoordinate().z + b.getCubeCoordinate().z);
}

HexCoordinates HexCoordinates::Hex_subtract(HexCoordinates a, HexCoordinates b)
{
    return HexCoordinates(a.getCubeCoordinate().x + b.getCubeCoordinate().x,
        a.getCubeCoordinate().y + b.getCubeCoordinate().y,
        a.getCubeCoordinate().z + b.getCubeCoordinate().z);
}

HexCoordinates HexCoordinates::Hex_multiply(HexCoordinates a, int k)
{
    return HexCoordinates(a.getCubeCoordinate().x * k,
                a.getCubeCoordinate().y * k,
                a.getCubeCoordinate().z * k);
}

bool operator == (HexCoordinates a, HexCoordinates b) {
    return a.getCubeCoordinate().x == b.getCubeCoordinate().x && a.getCubeCoordinate().y == b.getCubeCoordinate().y && a.getCubeCoordinate().z == b.getCubeCoordinate().z;
}

void HexCoordinates::BuildHex()
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

glm::vec2 hex_to_pixel(Layout layout, HexCoordinates h) {
	const Orientation& M = layout.orientation;
	double x = (M.f0 * h.getCubeCoordinate().x + M.f1 * h.getCubeCoordinate().y) * layout.size.x;
	double y = (M.f2 * h.getCubeCoordinate().x + M.f3 * h.getCubeCoordinate().y) * layout.size.y;
	return glm::vec2(x + layout.origin.x, y + layout.origin.y);
}
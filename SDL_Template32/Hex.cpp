#include "Hex.h"
#include "Engine.h"
#include <iostream>

Hex::Hex(glm::vec2 worldPosition, glm::vec2 gridPosition) : mouseHover(false), m_MouseState(STATE_OFF), m_pGridPosition(gridPosition)
{
	TheTextureManager::Instance()->load("Img/Hex Tileset.png", "hex", Engine::Instance().GetRenderer());

	setPosition(worldPosition);
	setWidth(40);
	setHeight(40);
	setType(GameObjectType::HEX);
	m_InteractiveState = INITIAL;
	setOccupied(false);

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
	
	TheTextureManager::Instance()->drawHex("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), 0,(int)m_MouseState, (int)m_InteractiveState);
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
		//std::cout << " state off" << std::endl;
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

void Hex::setInteractiveState(InteractiveState newstate)
{
	m_InteractiveState = newstate;
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


#include "Hex.h"
#include "Engine.h"
#include <iostream>

Hex::Hex(glm::vec2 worldPosition, glm::vec2 gridPosition) : mouseHover(false), m_state(STATE_OFF), m_pGridPosition(gridPosition)
{
	TheTextureManager::Instance()->load("Img/Hex Tileset.png", "hex", Engine::Instance().GetRenderer());
	//TheTextureManager::Instance()->load("Img/selector.png", "hover", Engine::Instance().GetRenderer());

	setPosition(worldPosition);
	setWidth(40);
	setHeight(40);
	setType(GameObjectType::HEX);

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
	
	//switch (m_state)
	//{
	//case STATE_HOVER :
	//	//TheTextureManager::Instance()->draw("hover", xComponent, yComponent, Engine::Instance().GetRenderer(), false);
	//	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	//	SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &rectangle);
	//	break;
	//case STATE_OFF :
	//	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	//	//SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &rectangle);
	//	TheTextureManager::Instance()->draw("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), false);
	//	break;
	//case STATE_SELECTED :
	//	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	//	SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &rectangle);
	//}
	TheTextureManager::Instance()->drawHex("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), 0,(int)m_state);
}

void Hex::update()
{
	bool mousecol = mouseCol();
	switch (m_state)
	{
	case STATE_OFF:
		if (mousecol)
		{
			m_state = STATE_HOVER;
			

		}

		//std::cout << " state off" << std::endl;
		break;
	case STATE_HOVER:
		/*if (!mousecol)
		{
			m_state = STATE_OFF;
		}*/
		 if (mousecol && Engine::Instance().GetMouseState(0))
		{
			m_state = STATE_SELECTED;
			for (auto hex : m_pNeighbours)
			{
				if (hex != nullptr)
					hex->m_state = STATE_HOVER;
			}
		}
			//std::cout << " state hover " << std::endl;
	
		break;
	case STATE_SELECTED:
		if (!Engine::Instance().GetMouseState(0))
		{
			if (mousecol)
			{
				m_state = STATE_HOVER;
				// Execute new "callback".

			}
			else
				m_state = STATE_OFF;
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


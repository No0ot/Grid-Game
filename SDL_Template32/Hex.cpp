#include "Hex.h"
#include "Engine.h"
#include <iostream>

Hex::Hex() : mouseHover(false), m_state(STATE_OFF)
{
	TheTextureManager::Instance()->load("Img/hex.png", "hex", Engine::Instance().GetRenderer());
	TheTextureManager::Instance()->load("Img/selector.png", "hover", Engine::Instance().GetRenderer());

	setPosition(glm::vec2(20, 20));

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("hex");
	setWidth(size.x);
	setHeight(size.y);
	setType(GameObjectType::HEX);
}

Hex::~Hex()
{

}

void Hex::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;
	SDL_Rect rectangle = { xComponent,yComponent,64,64 };
	
	switch (m_state)
	{
	case STATE_HOVER :
		//TheTextureManager::Instance()->draw("hover", xComponent, yComponent, Engine::Instance().GetRenderer(), false);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &rectangle);
		break;
	case STATE_OFF :
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
		SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &rectangle);
		//TheTextureManager::Instance()->draw("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), false);
		break;
	}
	//TheTextureManager::Instance()->draw("hex", xComponent, yComponent,64,64, Engine::Instance().GetRenderer(),(int)m_state);
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
		if (!mousecol)
		{
			m_state = STATE_OFF;
		}
			//std::cout << " state hover " << std::endl;
		break;
	}


}

void Hex::clean()
{

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


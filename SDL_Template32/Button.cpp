#include "Button.h"
#include <utility>
#include "TextureManager.h"
#include "Engine.h"

Button::Button(const std::string image_path, std::string button_name, 
               const glm::vec2 position, const bool is_centered,const GameObjectType type ):
m_alpha(255), m_name(std::move(button_name)), m_isCentered(is_centered), m_active(true)
{
	TextureManager::Instance()->load(image_path,m_name, Engine::Instance().GetRenderer());

	const auto size = TextureManager::Instance()->getTextureSize(m_name);
	setWidth(85);
	setHeight(85);
	setPosition(position);
	setType(type);
	GameObject::setActive(true);
	m_state = NONE;
}

Button::~Button()
= default;

void Button::draw()
{
	// alias for x and y
	const auto x = getPosition().x;
	const auto y = getPosition().y;

	// draw the button
	if(getActive())
		TextureManager::Instance()->drawButton(m_name, x, y, Engine::Instance().GetRenderer(), m_state, false, SDL_FLIP_NONE);
}

void Button::update()
{
	//check if mouse is over the Button
	onMouseOver();

	// check if mouse outside the Button
	onMouseOut();

	// check if left mouse is clicked
	onLeftMouseButtonClick();
	if (m_mouseOver)
	{
		m_state = HOVER;
	}
	else
		m_state = NONE;

	if (m_mouseOver && EventManager::Instance().getMouseButton(0))
	{
		m_state = CLICKED;
	}
}

void Button::clean()
{
}

void Button::setAlpha(const Uint8 alpha)
{
	m_alpha = alpha;
}

void Button::setActive(const bool value)
{
	m_active = value;
}

#include "GameObject.h"

GameObject::GameObject()
{
	m_position = glm::vec2(0, 0);
	m_rotation = glm::vec2(0, 0);
	m_scale = glm::vec2(1.0f, 1.0f);
}

GameObject::~GameObject()
{}

// GETTER DEFINITONS
glm::vec2 GameObject::getPosition() { return m_position; }
glm::vec2 GameObject::getRotation() { return m_rotation; }
glm::vec2 GameObject::getScale() { return m_scale; }
int GameObject::getWidth() { return m_width; }
int GameObject::getHeight() { return m_height; }
GameObjectType GameObject::getType() { return m_type; }

//SETTER DEFINITIONS
void GameObject::setPosition(glm::vec2 newPosition)
{
	m_position = newPosition;
}

void GameObject::setWidth(int newWidth)
{
	m_width = newWidth;
}

void GameObject::setHeight(int newHeight)
{
	m_height = newHeight;
}

void GameObject::setType(GameObjectType newType)
{
	m_type = newType;
}
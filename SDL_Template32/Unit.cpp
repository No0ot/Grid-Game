#include "Unit.h"
#include "Hex.h"
#include "Engine.h"

Unit::Unit() : m_currentHex(nullptr), m_facingHex(nullptr)
{
	TheTextureManager::Instance()->load("Img/Death.png", "Death", Engine::Instance().GetRenderer());
}

Unit::~Unit()
{
}

Hex* Unit::getHex() const
{
	return m_currentHex;
}

void Unit::setHex(Hex* new_hex)
{
	if(m_currentHex != nullptr)
		m_currentHex->setPathfindingState(Hex::PathfindingState::UNVISITED);
	m_currentHex = new_hex;
	m_currentHex->setOccupied(true);
	m_currentHex->setPathfindingState(Hex::PathfindingState::IMPASSABLE);
	
}

Hex* Unit::getFacingHex() const
{
	return m_facingHex;
}

Hex* Unit::getAttackDirection() const
{
	return m_attackDirection;
}

void Unit::setAttackDirection(Hex* new_hex)
{
	m_attackDirection = new_hex;
}

void Unit::setFacingHex(Hex* new_hex)
{
	m_facingHex = new_hex;
}

Unit::State Unit::getState()
{
	return m_pState;
}

Unit::Owner Unit::getOwner()
{
	return m_pOwner;
}

void Unit::setOwner(Owner newowner)
{
	m_pOwner = newowner;
}

void Unit::setState(State newstate)
{
	m_pState = newstate;
}


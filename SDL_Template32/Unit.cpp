#include "Unit.h"

Unit::Unit() : m_currentHex(nullptr), m_facingHex(nullptr)
{
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
	m_currentHex = new_hex;
}

Hex* Unit::getFacingHex() const
{
	return m_facingHex;
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


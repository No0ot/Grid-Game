#include "Unit.h"

Unit::Unit() : m_currentHex(nullptr)
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

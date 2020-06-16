#include "Merc.h"
#include "Engine.h"

//Jobs
#include "Archer.h"

Merc::Merc(Jobenum job)
{
	switch (job)
	{
	case ARCHER:
		m_Job = new Archer();
		break;
	case KNIGHT:
		break;
	}

}

Merc::~Merc()
{
}

void Merc::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->drawMerc("archer", xComponent, yComponent, Engine::Instance().GetRenderer(), 300, 0);
}

void Merc::update()
{
	setPosition( glm::vec2(getHex()->getPosition().x + 10 ,getHex()->getPosition().y + 5 ));
}

void Merc::clean()
{
}

int Merc::getMaxHealth()
{
	return m_MaxHealth;
}

int Merc::getCurrentHealth()
{
	return m_CurrentHealth;
}

int Merc::getStrength()
{
	return m_Strength;
}

int Merc::getFinesse()
{
	return m_Finnese;
}

int Merc::getConcentration()
{
	return m_Concentration;
}

int Merc::getResolve()
{
	return m_Resolve;
}

void Merc::setMaxHealth(int new_maxhealth)
{
	m_MaxHealth = new_maxhealth;
}

void Merc::setCurrentHealth(int new_currenthealth)
{
	m_CurrentHealth = new_currenthealth;
}

void Merc::setStrength(int new_strength)
{
	m_Strength = new_strength;
}

void Merc::setFinesse(int new_finesse)
{
	m_Finnese = new_finesse;
}

void Merc::setConcentration(int new_concentration)
{
	m_Concentration = new_concentration;
}

void Merc::setResolve(int new_resolve)
{
	m_Resolve = new_resolve;
}

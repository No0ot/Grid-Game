#include "Merc.h"
#include "Engine.h"
#include <iostream>

Merc::Merc(Jobenum job , Owner owner, int race, std::string name)
{
	setState(NO_STATE);
	setOwner(owner);

	m_Job = new Job(job);
	m_Race = new Race(race);
	m_Name = name;

	setStrength(m_Job->getBaseStr() + m_Race->getRaceStr());
	setFinesse(m_Job->getBaseFin() + m_Race->getRaceFin());
	setConcentration(m_Job->getBaseCon() + m_Race->getRaceCon());
	setResolve(m_Job->getBaseRes() + m_Race->getRaceRes());
	setMaxHealth(50 + (getStrength() * 10));
	setCurrentHealth(getMaxHealth());
	
	switch (m_Job->getPrimaryStat())
	{
	case Job::STRENGTH:
		setMainStat(getStrength());
		break;
	case Job::FINESSE:
		setMainStat(getFinesse());
		break;
	case Job::CONCENTRATION:
		setMainStat(getConcentration());
		break;
	case Job::RESOLVE:
		setMainStat(getResolve());
		break;
	}
}

Merc::~Merc()
{
}

void Merc::draw()
{
	const int xComponent = getPosition().x - getCamPosition().x;
	const int yComponent = getPosition().y - getCamPosition().y;

	TheTextureManager::Instance()->drawMerc(getJob()->getTexturename(), xComponent, yComponent, Engine::Instance().GetRenderer(), getFacing(), (int)getState(),(int)getOwner());
}

void Merc::update()
{
	setPosition( glm::vec2(getHex()->getPosition().x + 10 ,getHex()->getPosition().y + 5 ));
	getHex()->setOccupied(true);
	updateFacing();
	
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

int Merc::getInitiative() const
{
	return m_Initiative;
}

Job* Merc::getJob()
{
	return m_Job;
}

std::string Merc::getName()
{
	return m_Name;
}

int Merc::getMainStat()
{
	return m_Mainstat;
}

Race* Merc::getRace()
{
	return m_Race;
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

void Merc::setMainStat(int new_stat)
{
	m_Mainstat = new_stat;
}

void Merc::updateFacing()
{
	int count = getHex()->getNeighbours().size();
	for (int i = 0; i < count ; i++)
	{
		if (getHex()->getNeighbours()[i] != nullptr)
		{
			Hex* checkHex = getHex()->getNeighbours()[i];
			if (getFacingHex() == checkHex)
				setFacing((60 * i) + 60);
		}
	}
	//if (getFacingHex() == getHex()->getNeighbours()[0])
	//	setFacing(120);
	//else if (getFacingHex() == getHex()->getNeighbours()[1])
	//	setFacing(60);
	//else if (getFacingHex() == getHex()->getNeighbours()[2])
	//	setFacing(0);
	//else if (getFacingHex() == getHex()->getNeighbours()[3])
	//	setFacing(300);
	//else if (getFacingHex() == getHex()->getNeighbours()[4])
	//	setFacing(240);
	//else if (getFacingHex() == getHex()->getNeighbours()[5])
	//	setFacing(180);
}

void Merc::rollInitiative()
{
	m_Initiative = rand() % 20 + 1 + m_Job->getInitMod();
	std::cout << m_Name << " Rolled " << m_Initiative << " Initiative" <<  std::endl;
}

void Merc::attack(Merc* targetUnit)
{
	int missChance = 40 + targetUnit->getFinesse();
	std::cout << this->getName() << " has a  " << 100 - missChance << "% chance to hit." << std::endl;
	int attackroll = rand() % 100 + getConcentration();
	std::cout << this->getName() << " rolled a " << attackroll << std::endl;

	if (attackroll > missChance)
	{
		int damage = rand() % m_Job->getMaxDamage() + m_Job->getMinDamage() + getMainStat();
		std::cout << this->getName() << " dealt " << damage << " damage to " << targetUnit->getName() << std::endl;
		targetUnit->setCurrentHealth(targetUnit->getCurrentHealth() - damage);
		std::cout << targetUnit->getName() << " has " << targetUnit->getCurrentHealth() << " health remaining." << std::endl;
	}
	else
	{
		std::cout << "--Attack Missed--" << std::endl;
	}
}


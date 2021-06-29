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
	m_Threat = m_Job->getBaseThreat();
	
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

	if(!m_isDead)
		TheTextureManager::Instance()->drawMerc(getJob()->getTexturename(), xComponent, yComponent, Engine::Instance().GetRenderer(), getFacing(), (int)getState(),(int)getOwner());
	else
		TheTextureManager::Instance()->drawMerc("Death", xComponent, yComponent, Engine::Instance().GetRenderer(), getFacing(), (int)getState(), (int)getOwner());
}

void Merc::update()
{
	setPosition( glm::vec2(getHex()->getPosition().x + 10 ,getHex()->getPosition().y + 5 ));
	//getHex()->setOccupied(true);
	updateFacing();
	
}

void Merc::clean()
{
}

float Merc::getMaxHealth()
{
	return m_MaxHealth;
}

float Merc::getCurrentHealth()
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

int Merc::getThreat() const
{
	return m_Threat;
}

void Merc::setMaxHealth(float new_maxhealth)
{
	m_MaxHealth = new_maxhealth;
}

void Merc::setCurrentHealth(float new_currenthealth)
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
	Hex* temphex = getFacingHex();

	if (temphex != nullptr)
	{
		for (int i = 0; i < 6 ; i++)
		{
			glm::vec3 temp = getHex()->getCubeCoordinate() + getHex()->directions[i];
			if (temphex->getCubeCoordinate() == temp)
			{
				setFacing((60 * i));

				switch (i)
				{
				case 0:
					m_sideFacingHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[1]);
					m_sideFacingHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[5]);
					m_sideBehindHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[2]);
					m_sideBehindHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[4]);
					m_BehindHex = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[3]);
					break;
				case 1:
					m_sideFacingHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[0]);
					m_sideFacingHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[2]);
					m_sideBehindHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[3]);
					m_sideBehindHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[5]);
					m_BehindHex = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[4]);
					break;
				case 2:
					m_sideFacingHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[1]);
					m_sideFacingHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[3]);
					m_sideBehindHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[4]);
					m_sideBehindHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[0]);
					m_BehindHex = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[5]);
					break;
				case 3:
					m_sideFacingHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[2]);
					m_sideFacingHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[4]);
					m_sideBehindHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[1]);
					m_sideBehindHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[5]);
					m_BehindHex = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[0]);
					break;
				case 4:
					m_sideFacingHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[3]);
					m_sideFacingHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[5]);
					m_sideBehindHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[2]);
					m_sideBehindHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[0]);
					m_BehindHex = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[1]);
					break;
				case 5:
					m_sideFacingHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[0]);
					m_sideFacingHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[4]);
					m_sideBehindHex1 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[3]);
					m_sideBehindHex2 = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[1]);
					m_BehindHex = ReturnNeighbour(getHex()->getCubeCoordinate() + getHex()->directions[2]);
					break;
				default:
					break;
				}
			}



		}
	}
}

void Merc::rollInitiative()
{
	m_Initiative = rand() % 20 + 1 + m_Job->getInitMod();
	std::cout << m_Name << " Rolled " << m_Initiative << " Initiative" <<  std::endl;
}

void Merc::DealDamage(Merc* targetUnit)
{
	int missChance = 40 + targetUnit->getFinesse();
	int attackroll = rand() % 100 + getConcentration();

	if (targetUnit->getAttackDirection() == targetUnit->getFacingHex())
	{
		std::cout << "Attack from front" << std::endl;
		missChance += 20;
	}
	else if (targetUnit->getAttackDirection() == targetUnit->m_sideFacingHex1)
	{
		std::cout << "Attack from front side 1" << std::endl;
		missChance += 10;
	}
	else if (targetUnit->getAttackDirection() == targetUnit->m_sideFacingHex2)
	{
		std::cout << "Attack from front side 2" << std::endl;
		missChance += 10;
	}
	else if (targetUnit->getAttackDirection() == targetUnit->m_sideBehindHex1)
	{
		std::cout << "Attack from behind side 1" << std::endl;
		missChance -= 15;
	}
	else if (targetUnit->getAttackDirection() == targetUnit->m_sideBehindHex2)
	{
		std::cout << "Attack from behind side 2" << std::endl;
		missChance -= 15;
	}
	else if (targetUnit->getAttackDirection() == targetUnit->m_BehindHex)
	{
		std::cout << "Attack from back" << std::endl;
		missChance -= 30;
	}

	std::cout << this->getName() << " has a  " << 100 - missChance << "% chance to hit." << std::endl;
	std::cout << this->getName() << " rolled a " << attackroll << std::endl;

	if (attackroll > missChance)
	{
		int damage = rand() % m_Job->getMaxDamage() + m_Job->getMinDamage() + getMainStat();
		targetUnit->TakeDamage(damage);
		std::cout << targetUnit->getName() << " has " << targetUnit->getCurrentHealth() << " health remaining." << std::endl;

		m_Threat += damage;
		std::cout << this->getName() << " Threat = " << this->getThreat() << std::endl;
	}
	else
	{
		std::cout << "--Attack Missed--" << std::endl;
	}
}

void Merc::TakeDamage(int damage)
{
	std::cout << this->getName() << " dealt " << damage << " damage to " << getName() << std::endl;
	setCurrentHealth(getCurrentHealth() - damage);

	if (getCurrentHealth() <= 0)
	{
		setCurrentHealth(0);
		m_isDead = true;
	}
}

Hex* Merc::ReturnNeighbour(glm::vec3 coordinate)
{
	for (auto hex : getHex()->getNeighbours())
	{
		if (hex->getCubeCoordinate() == coordinate)
			return hex;
		//break;
	}
}


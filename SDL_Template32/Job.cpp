#include "Job.h"
#include "Engine.h"
#include "TextureManager.h"

Job::Job(Jobenum job)
{
	switch (job)
	{
	case ARCHER:
		TheTextureManager::Instance()->load("Img/Archer.png", "archer", Engine::Instance().GetRenderer());
		setBaseStr(3);
		setBaseFin(10);
		setBaseCon(9);
		setBaseRes(4);
		setMinDamage(6);
		setMaxDamage(8);
		setInitMod(1);
		setMoveRange(4);
		setDashRange(1);
		setAttackRange(4);
		m_Texturename = "archer";
		break;
	case BARBARIAN:
		TheTextureManager::Instance()->load("Img/Barb.png", "barbarian", Engine::Instance().GetRenderer());
		setBaseStr(12);
		setBaseFin(9);
		setBaseCon(3);
		setBaseRes(6);
		setMinDamage(2);
		setMaxDamage(14);
		setInitMod(2);
		setMoveRange(6);
		setDashRange(2);
		setAttackRange(1);
		m_Texturename = "barbarian";
		break;
	case MAGE:
		TheTextureManager::Instance()->load("Img/Mage.png", "mage", Engine::Instance().GetRenderer());
		setBaseStr(2);
		setBaseFin(6);
		setBaseCon(14);
		setBaseRes(9);
		setMinDamage(14);
		setMaxDamage(2);
		setInitMod(0);
		setMoveRange(4);
		setDashRange(1);
		setAttackRange(3);
		m_Texturename = "mage";
		break;
	case PRIEST:
		TheTextureManager::Instance()->load("Img/Priest.png", "priest", Engine::Instance().GetRenderer());
		setBaseStr(4);
		setBaseFin(6);
		setBaseCon(8);
		setBaseRes(10);
		setMinDamage(2);
		setMaxDamage(14);
		setInitMod(0);
		setMoveRange(4);
		setDashRange(1);
		setAttackRange(3);
		m_Texturename = "priest";
		break;
	}
}

Job::~Job()
{
}

int Job::getBaseStr()
{
	return m_baseStr;
}

int Job::getBaseFin()
{
	return m_baseFin;
}

int Job::getBaseCon()
{
	return m_baseCon;
}

int Job::getBaseRes()
{
	return m_baseRes;
}

int Job::getMinDamage()
{
	return m_minDamage;
}

int Job::getMaxDamage()
{
	return m_maxDamage;
}

int Job::getInitMod()
{
	return m_initMod;
}

int Job::getMoveRange()
{
	return m_moveRange;
}

int Job::getDashRange()
{
	return m_dashRange;
}

int Job::getAttackRange()
{
	return m_attackRange;
}

std::string Job::getTexturename()
{
	return m_Texturename;
}

void Job::setBaseStr(int str)
{
	m_baseStr = str;
}

void Job::setBaseFin(int fin)
{
	m_baseFin = fin;
}

void Job::setBaseCon(int con)
{
	m_baseCon = con;
}

void Job::setBaseRes(int res)
{
	m_baseRes = res;
}

void Job::setInitMod(int intmod)
{
	m_initMod = intmod;
}

void Job::setMinDamage(int mindmg)
{
	m_minDamage = mindmg;
}

void Job::setMaxDamage(int maxdmg)
{
	m_maxDamage = maxdmg;
}

void Job::setMoveRange(int moverange)
{
	m_moveRange = moverange;
}

void Job::setDashRange(int dashrange)
{
	m_dashRange = dashrange;
}

void Job::setAttackRange(int attackrange)
{
	m_attackRange = attackrange;
}

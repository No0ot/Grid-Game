#include "Job.h"
#include "Engine.h"
#include "TextureManager.h"

Job::Job()
{
	switch (m_Jobenum)
	{
	case ARCHER:
		TheTextureManager::Instance()->load("Img/Archer.png", "archer", Engine::Instance().GetRenderer());
		setBaseStr(3);
		setBaseFin(10);
		setBaseCon(9);
		setBaseRes(4);
		break;
	case KNIGHT:
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

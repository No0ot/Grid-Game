#include "Race.h"


Race::Race(int raceIndex)
{
	switch (raceIndex)
	{
	case 0:

		m_Name = GOLEM;
		break;
	case 1:
		m_Name = ORILLA;
		break;
	case 2:
		m_Name = HUMAN;
		break;
	case 3:
		m_Name = XIIN;
	}
	SetStats();

}

void Race::SetStats()
{
	switch (m_Name)
	{
	case GOLEM:
		m_raceStr = 5;
		m_raceFin = 1;
		m_raceCon = 2;
		m_raceRes = 3;
		break;
	case ORILLA:
		m_raceStr = 3;
		m_raceFin = 5;
		m_raceCon = 2;
		m_raceRes = 1;
		break;
	case HUMAN:
		m_raceStr = 2;
		m_raceFin = 1;
		m_raceCon = 5;
		m_raceRes = 2;
		break;
	case XIIN:
		m_raceStr = 1;
		m_raceFin = 1;
		m_raceCon = 2;
		m_raceRes = 5;
		break;
	}
}

int Race::getRaceStr()
{
	return m_raceStr;
}

int Race::getRaceFin()
{
	return m_raceFin;
}

int Race::getRaceCon()
{
	return m_raceCon;
}

int Race::getRaceRes()
{
	return m_raceRes;
}

#pragma once
#include <string>

enum RaceEnum { GOLEM, ORILLA, HUMAN, GLORYBORN };

class Race
{
private:
	RaceEnum m_Name;
	enum PrimaryStat { STRENGTH, FINESSE, CONCENTRATION, RESOLVE };
	PrimaryStat m_PrimaryStat;
	std::string m_RaceName;
	int m_raceStr,
		m_raceFin,
		m_raceCon,
		m_raceRes;

public:

	Race(int raceIndex);
	~Race();

	void SetStats();

	int getRaceStr();
	int getRaceFin();
	int getRaceCon();
	int getRaceRes();
	std::string getRaceName();

	RaceEnum getEnum();
};


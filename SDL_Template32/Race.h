#pragma once
class Race
{
private:
	enum RaceEnum { GOLEM, ORILLA, HUMAN, XIIN };
	RaceEnum m_Name;
	enum PrimaryStat { STRENGTH, FINESSE, CONCENTRATION, RESOLVE };
	PrimaryStat m_PrimaryStat;

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

};


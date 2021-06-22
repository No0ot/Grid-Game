#pragma once
#include "JobEnum.h"
#include <string>
class Job
{
public:
	//enum Jobenum { ARCHER, KNIGHT };
	enum PrimaryStat { STRENGTH, FINESSE, CONCENTRATION, RESOLVE };
	Jobenum m_Jobenum;

	
	Job(Jobenum job);
	~Job();

	//Getters
	int getBaseStr();
	int getBaseFin();
	int getBaseCon();
	int getBaseRes();
	int getMinDamage();
	int getMaxDamage();
	int getInitMod();
	int getMoveRange();
	int getDashRange();
	int getAttackRange();
	int getMainStat();
	int getBaseThreat();
	std::string getTexturename();
	PrimaryStat getPrimaryStat();

	//Setters
	void setBaseStr(int str);
	void setBaseFin(int fin);
	void setBaseCon(int con);
	void setBaseRes(int res);
	void setMinDamage(int mindmg);
	void setMaxDamage(int maxdmg);
	void setInitMod(int intmod);
	void setMoveRange(int moverange);
	void setDashRange(int dashrange);
	void setAttackRange(int attackrange);
	void setMainStat(int mainstat);
	void setBaseThreat(int threat);

private:
	int m_baseStr,
		m_baseFin,
		m_baseCon,
		m_baseRes,
		m_minDamage,
		m_maxDamage,
		m_initMod,
		m_moveRange,
		m_dashRange,
		m_attackRange,
		m_mainStat,
		m_baseThreat;

	std::string m_Texturename;
	PrimaryStat m_PrimaryStat;
};


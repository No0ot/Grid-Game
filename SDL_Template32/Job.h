#pragma once
#include "JobEnum.h"
#include <string>
class Job
{
public:
	//enum Jobenum { ARCHER, KNIGHT };
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
	std::string getTexturename();
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
		m_attackRange;

	std::string m_Texturename;
	
};


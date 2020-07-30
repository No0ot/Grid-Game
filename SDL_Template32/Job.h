#pragma once
#include "JobEnum.h"
class Job
{
public:
	//enum Jobenum { ARCHER, KNIGHT };
	Jobenum m_Jobenum;
	
	Job();
	~Job();

	//Getters
	int getBaseStr();
	int getBaseFin();
	int getBaseCon();
	int getBaseRes();
	int getInitMod();
	//Setters
	void setBaseStr(int str);
	void setBaseFin(int fin);
	void setBaseCon(int con);
	void setBaseRes(int res);
	void setInitMod(int intmod);

private:
	int m_baseStr,
		m_baseFin,
		m_baseCon,
		m_baseRes,
		m_Range,
		m_minDamage,
		m_maxDamage,
		m_initMod;


	
};


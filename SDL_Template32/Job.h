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
	//Setters
	void setBaseStr(int str);
	void setBaseFin(int fin);
	void setBaseCon(int con);
	void setBaseRes(int res);

private:
	int m_baseStr,
		m_baseFin,
		m_baseCon,
		m_baseRes;


	
};


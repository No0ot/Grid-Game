#pragma once
#include "Unit.h"
#include "Job.h"
#include "JobEnum.h"
class Merc : public Unit
{
public:
	//friend class Job;
	Merc(Jobenum job);
	~Merc();

	//Inherited functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	//Getters
	int getMaxHealth();
	int getCurrentHealth();
	int getStrength();
	int getFinesse();
	int getConcentration();
	int getResolve();

	//Setters
	void setMaxHealth(int new_maxhealth);
	void setCurrentHealth(int new_currenthealth);
	void setStrength(int new_strength);
	void setFinesse(int new_finesse);
	void setConcentration(int new_concentration);
	void setResolve(int new_resolve);

private:
	// Needs a race and Job
	Job* m_Job;
	Jobenum m_JobTitle;

	enum PrimaryStat { STRENGTH, FINESSE, CONCENTRATION, RESOLVE};
	PrimaryStat m_PrimaryStat;
	// Data for stats
	int m_MaxHealth;
	int m_CurrentHealth;
	int m_Strength,
		m_Finnese,
		m_Concentration,
		m_Resolve;


};


#pragma once
#include "Unit.h"
#include "Job.h"
#include "JobEnum.h"
#include "Race.h"
#include <string>

class Merc : public Unit
{
public:
	//friend class Job;
	Merc(Jobenum job,Owner owner, int race, std::string name);
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
	int getInitiative() const;
	Job* getJob();
	std::string getName();

	//Setters
	void setMaxHealth(int new_maxhealth);
	void setCurrentHealth(int new_currenthealth);
	void setStrength(int new_strength);
	void setFinesse(int new_finesse);
	void setConcentration(int new_concentration);
	void setResolve(int new_resolve);

	//other functions
	void updateFacing();
	void rollInitiative();
	void attack(Merc* targetUnit);

private:
	// Needs a race and Job
	Job* m_Job;
	Jobenum m_JobTitle;
	Race* m_Race;


	enum PrimaryStat { STRENGTH, FINESSE, CONCENTRATION, RESOLVE};
	PrimaryStat m_PrimaryStat;
	// Data for stats
	std::string m_Name;
	int m_MaxHealth;
	int m_CurrentHealth;
	int m_Strength,
		m_Finnese,
		m_Concentration,
		m_Resolve,
		m_Initiative;


};


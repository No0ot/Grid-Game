#pragma once
#include "GameObject.h"
#include "Merc.h"
#include "TextureManager.h"
#include "Label.h"
#include <vector>

class UnitProfile : public GameObject
{
public:
	UnitProfile(glm::vec2 worldposition);
	~UnitProfile();

	//Inherited functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	//getters
	Merc* getUnitReference();
	//setters
	void setUnitReference(Merc* new_unit);
	//other methods
	void setLabels();

private:
	Merc* m_UnitReference;

	float m_HealthPerc;

	std::vector<Label*> m_Labels;

};


#include "UnitProfile.h"
#include "Engine.h"
#include <iostream>
#include <sstream>
#include <iomanip>

UnitProfile::UnitProfile(glm::vec2 worldposition)
{
	TheTextureManager::Instance()->load("Img/Unit Profile.png", "unitprofile", Engine::Instance().GetRenderer());

	setPosition(worldposition);

	std::ostringstream tempLabel;
	
	
		tempLabel << std::fixed << std::setprecision(1) << " ";
		auto labelstring = tempLabel.str();
		SDL_Color black{ 0, 0, 0, 255 };
		auto valueLabelPosition = glm::vec2(-20, -20);
			m_Labels = { new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",10, black, valueLabelPosition, true)};
	
}

UnitProfile::~UnitProfile()
{
}

void UnitProfile::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->drawUnitProfile("unitprofile", xComponent, yComponent, Engine::Instance().GetRenderer(), 0);

	for(auto labels : m_Labels)
		labels->draw();

	if (getUnitReference() != nullptr)
	{
		SDL_Rect rectangle = { xComponent, yComponent ,250,175 };
		SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
		if (getUnitReference()->getOwner() == Unit::PLAYER_1)
			SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 240, 100, 0, 50);
		else
			SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 100, 250, 50);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rectangle);
	}
}

void UnitProfile::update()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	if (m_UnitReference != nullptr)
	{
		std::ostringstream tempLabel[14];
		std::string labelstring[14];
		glm::vec2 labelposition[14];
		//HEALTH LABEL
		tempLabel[0] << std::fixed << std::setprecision(1) << m_UnitReference->getCurrentHealth() << " / " << m_UnitReference->getMaxHealth();
		labelposition[0] = glm::vec2(xComponent + 50, yComponent + 122);
		//DAMAGE LABEL
		tempLabel[1] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getMinDamage() + m_UnitReference->getMainStat() << "-" << m_UnitReference->getJob()->getMaxDamage() + m_UnitReference->getMainStat();
		labelposition[1] = glm::vec2(xComponent + 82 , yComponent + 150);
		//NAME LABEL
		tempLabel[2] << std::fixed << std::setprecision(1) << m_UnitReference->getName();
		labelposition[2] = glm::vec2(xComponent + 177, yComponent + 25);
		//JOB LABEL
		tempLabel[3] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getTexturename();
		labelposition[3] = glm::vec2(xComponent + 150, yComponent + 52);
		//RACE LABEL
		tempLabel[4] << std::fixed << std::setprecision(1) << m_UnitReference->getRace()->getRaceName();
		labelposition[4] = glm::vec2(xComponent + 210, yComponent + 52);
		//STR LABEL
		tempLabel[5] << std::fixed << std::setprecision(1) << m_UnitReference->getStrength();
		labelposition[5] = glm::vec2(xComponent + 160, yComponent + 87);
		//FIN LABEL
		tempLabel[6] << std::fixed << std::setprecision(1) << m_UnitReference->getFinesse();
		labelposition[6] = glm::vec2(xComponent + 160, yComponent + 107);
		//CON LABEL
		tempLabel[7] << std::fixed << std::setprecision(1) << m_UnitReference->getConcentration();
		labelposition[7] = glm::vec2(xComponent + 160, yComponent + 127);
		//RES LABEL
		tempLabel[8] << std::fixed << std::setprecision(1) << m_UnitReference->getResolve();
		labelposition[8] = glm::vec2(xComponent + 160, yComponent + 142);
		//INIT LABEL
		tempLabel[9] << std::fixed << std::setprecision(1) << m_UnitReference->getInitiative();
		labelposition[9] = glm::vec2(xComponent + 220, yComponent + 87);
		//DASH LABEL
		tempLabel[10] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getDashRange();
		labelposition[10] = glm::vec2(xComponent + 220, yComponent + 107);
		//RUN LABEL
		tempLabel[11] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getMoveRange();
		labelposition[11] = glm::vec2(xComponent + 220, yComponent + 127);
		//RANGE LABEL
		tempLabel[12] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getAttackRange();
		labelposition[12] = glm::vec2(xComponent + 225, yComponent + 142);

		for (int count = 0; count < m_Labels.size(); count++)
		{
			m_Labels[count]->setPosition(labelposition[count]);
			labelstring[count] = tempLabel[count].str();
			const SDL_Color green{ 0, 255, 100, 255 };
			m_Labels[count]->setText(labelstring[count]);
			m_Labels[count]->setColour(green);
		}
	}
}

void UnitProfile::clean()
{
}

Merc* UnitProfile::getUnitReference()
{
	return m_UnitReference;
}

void UnitProfile::setUnitReference(Merc* new_unit)
{
	m_UnitReference = new_unit;
}

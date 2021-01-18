#include "UnitProfile.h"
#include "Engine.h"
#include <iostream>
#include <sstream>
#include <iomanip>

UnitProfile::UnitProfile(glm::vec2 worldposition)
{
	TheTextureManager::Instance()->load("Img/Unit Profile.png", "unitprofile", Engine::Instance().GetRenderer());
	TheTextureManager::Instance()->load("Img/Golm.png", "golm", Engine::Instance().GetRenderer());
	TheTextureManager::Instance()->load("Img/Orilla.png", "orilla", Engine::Instance().GetRenderer());
	TheTextureManager::Instance()->load("Img/Human.png", "human", Engine::Instance().GetRenderer());
	TheTextureManager::Instance()->load("Img/Gloryborn.png", "gloryborn", Engine::Instance().GetRenderer());


	setPosition(worldposition);

	std::ostringstream tempLabel;
	
	
		tempLabel << std::fixed << std::setprecision(1) << " ";
		auto labelstring = tempLabel.str();
		SDL_Color black{ 0, 0, 0, 255 };
		auto valueLabelPosition = glm::vec2(-20, -20);
			m_Labels = { new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true),
						 new Label(labelstring, "Consolas",12, black, valueLabelPosition, true)};
	
}

UnitProfile::~UnitProfile()
{
}

void UnitProfile::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;


	if (getUnitReference() != nullptr)
	{
		TheTextureManager::Instance()->drawUnitProfile("unitprofile", xComponent, yComponent, Engine::Instance().GetRenderer(), 0);
		float healthbarwidth = 128.0f * m_HealthPerc;
		if (healthbarwidth < 0)
			healthbarwidth = 0;

		SDL_Rect health_rec = { xComponent + 18, yComponent + 156, healthbarwidth, 16 };
		SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_NONE);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 200, 0, 100);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &health_rec);

		for(auto labels : m_Labels)
			labels->draw();
		SDL_Rect rectangle = { xComponent, yComponent ,333,233 };
		SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
		if (getUnitReference()->getOwner() == Unit::PLAYER_1)
			SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 240, 100, 0, 50);
		else
			SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 100, 250, 50);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rectangle);

		switch (getUnitReference()->getRace()->getEnum())
		{
		case GOLEM:
			TheTextureManager::Instance()->draw("golm", xComponent + 22, yComponent + 21,182,182, Engine::Instance().GetRenderer());
			break;
		case ORILLA:
			TheTextureManager::Instance()->draw("orilla", xComponent + 22, yComponent + 21, 182, 182, Engine::Instance().GetRenderer());
			break;
		case HUMAN:
			TheTextureManager::Instance()->draw("human", xComponent + 22, yComponent + 21, 182, 182, Engine::Instance().GetRenderer());
			break;
		case GLORYBORN:
			TheTextureManager::Instance()->draw("gloryborn", xComponent + 22, yComponent + 21, 182, 182, Engine::Instance().GetRenderer());
			break;
		}
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
		tempLabel[0] << std::fixed << std::setprecision(1) << (int)m_UnitReference->getCurrentHealth() << " / " << (int)m_UnitReference->getMaxHealth();
		labelposition[0] = glm::vec2(xComponent + 90, yComponent + 165);
		//DAMAGE LABEL
		tempLabel[1] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getMinDamage() + m_UnitReference->getMainStat() << "-" << m_UnitReference->getJob()->getMaxDamage() + m_UnitReference->getMainStat();
		labelposition[1] = glm::vec2(xComponent + 110 , yComponent + 200);
		//NAME LABEL
		tempLabel[2] << std::fixed << std::setprecision(1) << m_UnitReference->getName();
		labelposition[2] = glm::vec2(xComponent + 240, yComponent + 35);
		//JOB LABEL
		tempLabel[3] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getTexturename();
		labelposition[3] = glm::vec2(xComponent + 200, yComponent + 70);
		//RACE LABEL
		tempLabel[4] << std::fixed << std::setprecision(1) << m_UnitReference->getRace()->getRaceName();
		labelposition[4] = glm::vec2(xComponent + 280, yComponent + 70);
		//STR LABEL
		tempLabel[5] << std::fixed << std::setprecision(1) << m_UnitReference->getStrength();
		labelposition[5] = glm::vec2(xComponent + 210, yComponent + 120);
		//FIN LABEL
		tempLabel[6] << std::fixed << std::setprecision(1) << m_UnitReference->getFinesse();
		labelposition[6] = glm::vec2(xComponent + 210, yComponent + 145);
		//CON LABEL
		tempLabel[7] << std::fixed << std::setprecision(1) << m_UnitReference->getConcentration();
		labelposition[7] = glm::vec2(xComponent + 210, yComponent + 170);
		//RES LABEL
		tempLabel[8] << std::fixed << std::setprecision(1) << m_UnitReference->getResolve();
		labelposition[8] = glm::vec2(xComponent + 210, yComponent + 195);
		//INIT LABEL
		tempLabel[9] << std::fixed << std::setprecision(1) << m_UnitReference->getInitiative();
		labelposition[9] = glm::vec2(xComponent + 290, yComponent + 120);
		//DASH LABEL
		tempLabel[10] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getDashRange();
		labelposition[10] = glm::vec2(xComponent + 290, yComponent + 145);
		//RUN LABEL
		tempLabel[11] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getMoveRange();
		labelposition[11] = glm::vec2(xComponent + 290, yComponent + 170);
		//RANGE LABEL
		tempLabel[12] << std::fixed << std::setprecision(1) << m_UnitReference->getJob()->getAttackRange();
		labelposition[12] = glm::vec2(xComponent + 295, yComponent + 195);

		for (int count = 0; count < m_Labels.size(); count++)
		{
			m_Labels[count]->setPosition(labelposition[count]);
			labelstring[count] = tempLabel[count].str();
			const SDL_Color green{ 0, 255, 100, 255 };
			m_Labels[count]->setText(labelstring[count]);
			m_Labels[count]->setColour(green);
		}

		m_HealthPerc = m_UnitReference->getCurrentHealth() / m_UnitReference->getMaxHealth();
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

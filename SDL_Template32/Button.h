#pragma once
#ifndef __BUTTON__
#define __BUTTON__

#include "GameObject.h"
#include <SDL.h>
#include "UIControl.h"

class Button : public UIControl
{
public:
	Button(const std::string& image_path,
		std::string button_name,
		glm::vec2 position, bool is_centered = true,
		GameObjectType type = BUTTON );
	
	~Button();

	// Life Cycle Events
	void draw() override;
	void update() override;
	void clean() override;

	// button setters
	void setAlpha(Uint8 alpha);
	void setActive(bool value);
	
private:
	Uint8 m_alpha;
	std::string m_name;
	bool m_isCentered;
	bool m_active;
};

#endif /* defined (__BUTTON__) */
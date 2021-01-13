#pragma once
#ifndef __UI_CONTROL__
#define __UI_CONTROL__

#include "GameObject.h"
#include <SDL.h>
#include "EventManager.h"
#include <unordered_map>
#include <functional>

class UIControl : public GameObject
{
public:
	UIControl();
	virtual ~UIControl();
	
	virtual void draw() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void clean() = 0;

	typedef std::function<void()> EventHandler;
	bool addEventListener(Event event, const EventHandler& handler);

	EventHandler getEventHandler(Event event);
	bool pointRectCheck(const glm::vec2, const glm::vec2, const float, const float);
	
protected:
	void onMouseOver();
	void onMouseOut();
	void onLeftMouseButtonClick();

private:
	bool m_eventExists(Event id);

	// mouse events
	bool m_mouseOver;
	bool m_mouseOverActive;
	bool m_mouseOutActive;
	
	bool m_leftMouseButtonClicked;

	// event structure
	std::unordered_map<Event, EventHandler> m_events;
};

#endif /* defined (__UI_CONTROL__) */


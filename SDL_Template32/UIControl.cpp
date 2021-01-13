#include "UIControl.h"


UIControl::UIControl():
	m_mouseOver(false), m_mouseOverActive(false), m_mouseOutActive(false), m_leftMouseButtonClicked(false)
{
}

UIControl::~UIControl()
= default;

bool UIControl::addEventListener(const Event event, const EventHandler& handler)
{
	if (m_eventExists(event))
	{
		return false;
	}

	m_events[event] = handler;
	return true;
}

UIControl::EventHandler UIControl::getEventHandler(Event event)
{
	return m_events[event];
}

bool UIControl::pointRectCheck(const glm::vec2 point, const glm::vec2 rect_start, const float rect_width, const float rect_height)
{
	const float topLeftX = rect_start.x - rect_width * 0.5;
	const float topLeftY = rect_start.y - rect_height * 0.5;
	const auto width = rect_width;
	const auto height = rect_height;

	if (point.x > topLeftX &&
		point.x < topLeftX + width &&
		point.y > topLeftY &&
		point.y < topLeftY + height)
	{
		return true;
	}
	return false;
}

void UIControl::onMouseOver()
{
	const auto mousePosition = EventManager::Instance().getMousePosition();

	
	if (pointRectCheck(mousePosition, getPosition(), getWidth(), getHeight()))
	{
		m_mouseOver = true;
	}
	else
	{
		m_mouseOver = false;
	}

	if ((m_events[MOUSE_OVER]) && (!m_mouseOverActive))
	{
		if (m_mouseOver)
		{
			m_events[MOUSE_OVER]();
			m_mouseOverActive = true;
		}
	}
	else if ((m_events[MOUSE_OVER]) && (!m_mouseOver))
	{
		m_mouseOverActive = false;
	}
}

void UIControl::onMouseOut()
{
	if ((m_events[MOUSE_OUT]) && (m_mouseOutActive) && (!m_mouseOver))
	{
		m_events[MOUSE_OUT]();
		m_mouseOutActive = false;
	}
	else if ((m_events[MOUSE_OUT]) && (m_mouseOver))
	{
		m_mouseOutActive = true;
	}
}

void UIControl::onLeftMouseButtonClick()
{
	if (EventManager::Instance().getMouseButton(LEFT))
	{
		if ((m_events[CLICK]) && (m_mouseOver) && !m_leftMouseButtonClicked)
		{
			m_leftMouseButtonClicked = true;
			m_events[CLICK](); // call click event
		}
	}
	else
	{
		m_leftMouseButtonClicked = false;
	}
}

bool UIControl::m_eventExists(Event id)
{
	return m_events.find(id) != m_events.end();
}

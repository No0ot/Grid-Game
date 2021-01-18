#pragma once

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <string>

enum GameObjectType {
	HEX,
	JOB,
	CHARACTER,
	BUTTON,
	NUM_OF_TYPES
};

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	//GETTERS
	glm::vec2 getPosition();
	glm::vec2 getCamPosition();
	glm::vec2 getRotation();
	glm::vec2 getScale();
	int getWidth();
	int getHeight();
	GameObjectType getType();
	int getFacing();
	bool getActive();

	//SETTERS
	void setPosition(glm::vec2 newpos);
	void setCamPosition(glm::vec2 newpos);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setType(GameObjectType newType);
	void setFacing(int newfacing);
	void setActive(bool newactive);

private:
	// VARIABLES
	int m_facing;
	bool m_active;

	//TRANSFORM
	glm::vec2 m_worldPosition;
	glm::vec2 m_cameraPosition;
	glm::vec2 m_rotation;
	glm::vec2 m_scale;

	//SIZE
	int m_width;
	int m_height;

	// ANIMATION
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	std::string m_textureID;

	GameObjectType  m_type;
};


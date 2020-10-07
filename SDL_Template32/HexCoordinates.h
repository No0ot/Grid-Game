#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "Label.h"

class HexCoordinates : public GameObject
{
public:
	glm::vec3 m_cubeCoordinate;

	HexCoordinates(int x, int y, int z);
	~HexCoordinates();

	// Draw the object
	void draw() override;

	// Update the object
	void update() override;

	// remove anything that needs to be deleted
	void clean() override;

	enum MouseState { STATE_OFF, STATE_HOVER, STATE_SELECTED };
	enum InteractiveState { INITIAL, DASH, RUN, FACEING };
	enum PathfindingState { NO_PATH, OPEN, CLOSED, START, GOAL, PATH, UNVISITED, IMPASSABLE };
	enum HexType { PLAINS, WALL, ROUGH, RAISED };

	MouseState m_MouseState;
	InteractiveState m_InteractiveState;
	PathfindingState m_PathfindingState;
	HexType m_HexType;

	glm::vec3 getCubeCoordinate();

	HexCoordinates Hex_add(HexCoordinates a, HexCoordinates b);
	HexCoordinates Hex_subtract(HexCoordinates a, HexCoordinates b);
	HexCoordinates Hex_multiply(HexCoordinates a, int k);

	bool mouseCol();
	void BuildHex();

private:

	bool mouseHover;
};


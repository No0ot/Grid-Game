#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "Label.h"
#include <vector>

class Merc;
class Hex : public GameObject
{
public:
	Hex(glm::vec2 worldPosition, glm::vec2 gridPosition);
	~Hex();
	// Draw the object
	void draw() override;

	// Update the object
	void update() override;

	// remove anything that needs to be deleted
	void clean() override;


	glm::vec2 getGridPosition();

	//Neighbour getters
	Hex* getUp();
	Hex* getUpRight();
	Hex* getDownRight();
	Hex* getDown();
	Hex* getDownLeft();
	Hex* getUpleft();

	//Neighbour Setters
	void setUp(Hex* hex);
	void setUpRight(Hex* hex);
	void setDownRight(Hex* hex);
	void setDown(Hex* hex);
	void setDownLeft(Hex* hex);
	void setUpLeft(Hex* hex);

	enum TileNeighbours {UP, UPRIGHT, DOWNRIGHT, DOWN, DOWNLEFT, UPLEFT};
	enum MouseState { STATE_OFF, STATE_HOVER, STATE_SELECTED };
	enum InteractiveState {INITIAL, DASH, RUN, FACEING };
	enum PathfindingState {NO_PATH, OPEN, CLOSED, START, GOAL, PATH, UNVISITED,IMPASSABLE};
	enum HexType {PLAINS, WALL, ROUGH, RAISED};

	MouseState m_MouseState;
	InteractiveState m_InteractiveState;
	PathfindingState m_PathfindingState;
	HexType m_HexType;

	// Other Getters
	std::vector<Hex*> getNeighbours() const;
	MouseState getMouseState();
	InteractiveState getInteractiveState();
	PathfindingState getPathfindingState();
	bool getOccupied();
	float getGlobalValue() const;
	float getLocalValue() const;
	Merc* getOccupier();
	int getHexCost();
	Hex* getHexParent();

	// Other Setters
	void setInteractiveState(InteractiveState newstate);
	void setPathfindingState(PathfindingState newstate);
	void setMouseState(MouseState newstate);
	void setOccupied(bool newbool);
	void setOccupier(Merc* newunit);
	void setHexParent(Hex* new_hex);
	void setHexCost(int new_value);
	void setLocalValue(float new_value);
	void setGlobalValue(float new_value);

	// Other Methods
	void BuildHex();
	float computeGlobalValue(const glm::vec2 goal_location);
	bool AstarPathfinding(Hex* active_hex);
	void buildPath();

private:
	//labels
	Label* m_pValueLabel;

	glm::vec2 m_goalLocation;
	float m_globalGoalValue = 0.0f;
	float m_localGoalValue = 0.0f;
	float m_MovementCost = 0.0f;
	std::list<Hex*> m_openList;
	std::vector<Hex*> m_path;
	bool b_visited;
	Hex* m_hexPathfindingParent = nullptr;
	int m_HexMoveCost;
	bool mouseCol();
	void setHover(bool h);
	bool m_pOccupied;
	bool mouseHover;
	glm::vec3 m_cubeCoordinate;
	glm::vec2 m_pGridPosition;
	std::vector<Hex*> m_pNeighbours;
	Merc* m_Occupier;
};


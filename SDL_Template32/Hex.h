#pragma once
#include "UIControl.h"
#include "TextureManager.h"
#include "Label.h"
#include "EventManager.h"

class Merc;

struct Orientation {
	const double f0, f1, f2, f3;
	const double b0, b1, b2, b3;
	const double start_angle; // in multiples of 60°
	Orientation(double f0_, double f1_, double f2_, double f3_,
		double b0_, double b1_, double b2_, double b3_,
		double start_angle_)
		: f0(f0_), f1(f1_), f2(f2_), f3(f3_),
		b0(b0_), b1(b1_), b2(b2_), b3(b3_),
		start_angle(start_angle_) {}
};

const Orientation layout_flat
= Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
	2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
	0.0);

struct Layout {
	const Orientation orientation;
	const glm::vec2 size;
	const glm::vec2 origin;
	Layout(Orientation temporientation, glm::vec2 tempsize, glm::vec2 temporigin)
		: orientation(temporientation), size(tempsize), origin(temporigin) {}
};

class Hex : public UIControl
{
public:
	glm::vec3 m_cubeCoordinate;
	Layout m_hexLayout;

	Hex(int x, int y, int z);
	~Hex();

	// Draw the object
	void draw() override;

	// Update the object
	void update() override;

	// remove anything that needs to be deleted
	void clean() override;

	enum MouseState { STATE_OFF, STATE_HOVER, STATE_SELECTED };
	enum InteractiveState { INITIAL, DASH, RUN, FACEING, THREAT };
	enum PathfindingState { NO_PATH, OPEN, CLOSED, START, GOAL, PATH, UNVISITED, IMPASSABLE };
	enum HexType { PLAINS, WALL, ROUGH, RAISED };

	MouseState m_MouseState;
	InteractiveState m_InteractiveState;
	PathfindingState m_PathfindingState;
	HexType m_HexType;
	std::vector<Hex*> m_pNeighbours;
	std::vector<Hex*> m_pPath;

	//Getters
	glm::vec3 getCubeCoordinate();
	std::vector<Hex*> getNeighbours() const;
	MouseState getMouseState();
	InteractiveState getInteractiveState();
	PathfindingState getPathfindingState();
	bool getOccupied();
	Merc* getOccupier();
	float getGlobalValue() const;
	Hex* getParentHex();
	int getCost();

	//Setters
	void setInteractiveState(InteractiveState newstate);
	void setPathfindingState(PathfindingState newstate);
	void setMouseState(MouseState newstate);
	void setOccupied(bool newbool);
	void setOccupier(Merc* newunit);
	void setParentHex(Hex* newhex);

	//Maths
	Hex Hex_add(Hex a, Hex b);
	Hex Hex_subtract(Hex a, Hex b);
	Hex Hex_multiply(Hex a, int k);

	void SetListenEvents();
	bool mouseCol();
	void BuildHex();
	float computeGlobalValue(const glm::vec3 goal_location);
	void aStarpathfinding(Hex* end);

	glm::vec3 directions[6];
private:
	Label* m_pValueLabel;

	std::list<Hex*> m_pOpenList;
	std::vector<Hex*> m_pClosedList;
	Hex* m_pHexParent;

	int m_pHexCost;
	bool m_pOccupied;
	Merc* m_Occupier;
	bool mouseHover;
	float m_globalGoalValue;
	float m_localGoalValue = 0;
};


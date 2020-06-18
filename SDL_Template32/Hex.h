#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include <vector>
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

	MouseState m_MouseState;
	InteractiveState m_InteractiveState;

	std::vector<Hex*> getNeighbours() const;
	MouseState getMouseState();
	InteractiveState getInteractiveState();
	void setInteractiveState(InteractiveState newstate);
	void setMouseState(MouseState newstate);
private:

	bool mouseCol();
	void setHover(bool h);

	bool mouseHover;
	glm::vec2 m_pGridPosition;
	std::vector<Hex*> m_pNeighbours;
};


#pragma once
#include "GameObject.h"
#include "TextureManager.h"

class Hex : public GameObject
{
public:
	Hex();
	~Hex();
	// Draw the object
	void draw() override;

	// Update the object
	void update() override;

	// remove anything that needs to be deleted
	void clean() override;
	void buildGrid(int i, int j);
	enum state { STATE_OFF,STATE_HOVER, STATE_SELECTED } m_state;
private:
	state getState();
	bool getOccupied();
	bool getActive();
	void setActive(bool b);
	void setOccupied(bool b);
	bool mouseCol();
	void setHover(bool h);

	bool mouseHover;
	
};


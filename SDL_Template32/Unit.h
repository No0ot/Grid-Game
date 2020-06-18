#pragma once
#include "GameObject.h"
#include "Hex.h"

class Unit : public GameObject
{
public:
	enum State {NO_STATE, ACTIVE, TARGET};
	enum Owner { AI, PLAYER_1, PLAYER_2 };
	Unit();
	~Unit();
	// Draw the object
	virtual void draw() override = 0;

	// Update the object
	virtual void update() override = 0;

	// remove anything that needs to be deleted
	virtual void clean() override = 0;

	Hex* getHex() const;
	void setHex(Hex* new_hex);
	Hex* getFacingHex() const;
	void setFacingHex(Hex* new_hex);

	State getState();
	Owner getOwner();
	void setOwner(Owner newowner);
	void setState(State newstate);
private:
	Owner m_pOwner;
	State m_pState;

	Hex* m_currentHex;
	Hex* m_facingHex;

};


#pragma once
#include "GameObject.h"
//#include "Hex.h"
class Hex;
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
	Hex* getFacingHex() const;
	Hex* getAttackDirection() const;
	State getState();
	Owner getOwner();

	void setAttackDirection(Hex* new_hex);
	void setFacingHex(Hex* new_hex);
	void setHex(Hex* new_hex);
	void setOwner(Owner newowner);
	void setState(State newstate);

	bool m_isDead = false;
	Hex* m_sideFacingHex1;
	Hex* m_sideFacingHex2;
	Hex* m_sideBehindHex1;
	Hex* m_sideBehindHex2;
	Hex* m_BehindHex;
private:
	Owner m_pOwner;
	State m_pState;

	Hex* m_currentHex;
	Hex* m_facingHex;

	Hex* m_attackDirection;

};


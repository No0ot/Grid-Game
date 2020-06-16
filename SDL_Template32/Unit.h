#pragma once
#include "GameObject.h"
#include "Hex.h"
class Unit : public GameObject
{
public:
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
private:
	Hex* m_currentHex;
	enum Owner { AI, PLAYER_1, PLAYER_2 };
	Owner m_pOwner;
};


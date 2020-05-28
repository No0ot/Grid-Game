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
private:
	bool getOccupied();
	bool getActive();
	void setActive(bool b);
	void setOccupied(bool b);
	
};


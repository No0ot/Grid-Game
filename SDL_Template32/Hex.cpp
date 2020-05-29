#include "Hex.h"
#include "Engine.h"

Hex::Hex()
{
	TheTextureManager::Instance()->load("Img/hex.png", "hex", Engine::Instance().GetRenderer());

	setPosition(glm::vec2(20, 20));

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("hex");
	setWidth(size.x);
	setHeight(size.y);
	setType(GameObjectType::HEX);
}

Hex::~Hex()
{

}
void Hex::buildGrid(int i, int j)
{

	if (j == 1 || j == 3 || j == 5 || j == 7 || j == 9 || j == 11 || j == 13 || j == 15)
		setPosition(glm::vec2(20 + (j * 95), (50 + (i * 64)) - 15));

	else if (j == 0 || j == 2 || j == 4 || j == 6 || j == 8 || j == 10 || j == 12 || j == 14)
		setPosition(glm::vec2(20 + (j * 95), (50 + (i * 64)) + 15));

}
void Hex::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("hex", xComponent, yComponent, Engine::Instance().GetRenderer(), false);
}

void Hex::update()
{

}

void Hex::clean()
{

}


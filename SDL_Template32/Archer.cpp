#include "Archer.h"
#include "TextureManager.h"
#include "Engine.h"

Archer::Archer()
{
	TheTextureManager::Instance()->load("Img/Archer.png", "archer", Engine::Instance().GetRenderer());

	setBaseStr(3);
	setBaseFin(10);
	setBaseCon(9);
	setBaseRes(4);

}

Archer::~Archer()
{
}

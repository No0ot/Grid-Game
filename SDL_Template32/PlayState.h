#pragma once

#include "State.h"
#include "Camera.h"

//Game Objects
//#include "Hex.h"
#include "HexCoordinates.h"
#include "Merc.h"
#include "UnitProfile.h"

class GameState : public State
{
private:
	std::vector<Hex*> m_pHexGrid;
	std::vector<Hex*> m_pHexList;
	std::list<Hex*> m_pThreatenedHexes;
	enum TurnState { NONE, PLAYER_MOVE, PLAYER_ABILITY, PLAYER_ATTACK, PLAYER_FACING, ENEMY_TURN };
	std::vector<Merc*> m_Player1MercVec;
	std::vector<Merc*> m_Player2MercVec;
	Merc* m_CurrentMerc;
	Merc* m_Player1Merc;
	Merc* m_Player2Merc;
	std::list<Merc*> m_turnOrder;
	UnitProfile* m_ActiveUnitProfile;
	UnitProfile* m_HoverUnitProfile;
	Camera* m_GameCamera;

	Hex* m_pSelectedHex;
	int counter;
public:
	TurnState current_state;
	GameState();
	void BuildHexGrid();
	Hex* returnHex(glm::vec3 search);
	void MapGrid();
	void ResetHexs();
	int SpawnObjects(Unit* spawned_object);
	void AddHexestoList();
	void drawGameBoard();
	void drawUI();

	//Inherited functions
	void Enter();
	void Update();
	void HandleEvents();
	void Render();
	void Exit();
	void Resume();
};
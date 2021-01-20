#pragma once

#include "State.h"
#include "Camera.h"

//Game Objects
//#include "Hex.h"
#include "Button.h"
#include "Hex.h"
#include "Merc.h"
#include "UnitProfile.h"
enum TurnState 
{
	START,
	IDLE,
	MOVE,
	ABILITY, 
	ATTACK,
	FACING, 
	END
};

class GameState : public State
{
private:
	std::vector<Hex*> m_pHexGrid;
	std::vector<Hex*> m_pHexList;
	std::list<Hex*> m_pThreatenedHexes;
	std::vector<Merc*> m_Player1MercVec;
	std::vector<Merc*> m_Player2MercVec;
	Merc* m_CurrentMerc;
	Merc* m_Player1Merc;
	Merc* m_Player2Merc;
	std::list<Merc*> m_turnOrder;
	UnitProfile* m_ActiveUnitProfile;
	UnitProfile* m_HoverUnitProfile;
	Button* m_MoveButton;
	Button* m_AttackButton;
	Button* m_AbilityButton;
	Button* m_EndButton;
	Camera* m_GameCamera;

	Hex* m_pSelectedHex;
	int counter;
	int m_mapRadius = 4;
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
	void InitializeButtons();

	//TURN FUNCTIONS
	void TurnStart();
	void TurnIdle();
	void TurnMove();
	void TurnAttack();
	void TurnFacing();
	void TurnEnd();


	//Inherited functions
	void Enter();
	void Update();
	void HandleEvents();
	void Render();
	void Exit();
	void Resume();
};
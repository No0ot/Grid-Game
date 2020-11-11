#pragma once
#include <vector>
#include <list>
//Game Objects
//#include "Hex.h"
#include "HexCoordinates.h"
#include "Merc.h"
#include "UnitProfile.h"

class State // Abstract base class.
{
protected:
	State() {}
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void HandleEvents() = 0;
	virtual void Exit() = 0;
	virtual void Resume();

	bool mouseDown;
};

class GameState : public State
{
private:
	std::vector<Hex*> m_pHexGrid;
	std::vector<Hex*> m_pHexList;
	std::list<Hex*> m_pThreatenedHexes;
	enum TurnState { NONE,PLAYER_MOVE, PLAYER_ABILITY, PLAYER_ATTACK, PLAYER_FACING, ENEMY_TURN};
	std::vector<Merc*> m_Player1MercVec;
	std::vector<Merc*> m_Player2MercVec;
	Merc* m_CurrentMerc;
	Merc* m_Player1Merc;
	Merc* m_Player2Merc;
	std::list<Merc*> m_turnOrder;
	UnitProfile* m_ActiveUnitProfile;
	UnitProfile* m_HoverUnitProfile;

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
	//Inherited functions
	void Enter();
	void Update();
	void HandleEvents();
	void Render();
	void Exit();
	void Resume();
};

class TitleState : public State
{
private:

public:
	TitleState();
	void Enter();
	void Update();
	void Render();
	void HandleEvents();
	void Exit();
};

class FSM
{
private:
	std::vector<State*> m_vStates;
public: 
	FSM();
	~FSM();
	void Update();
	void Render();
	void ChangeState(State* pState); // Normal state change.
	void PushState(State* pState); // GameState to PauseState.
	void PopState(); // PauseState to GameState.
	void Clean();
	void HandleEvents();
	std::vector<State*>& GetStates();
};


#pragma once
#include <vector>
//Game Objects
#include "Hex.h"
#include "Merc.h"

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
	enum TurnState { NONE,PLAYER_MOVE, PLAYER_ABILITY, PLAYER_ATTACK, PLAYER_FACING, ENEMY_TURN};
	std::vector<Merc*> m_MercVec;
	Merc* m_Merc;

	Hex* m_pSelectedHex;
	int counter;
public:
	TurnState current_state;
	GameState();
	void BuildHexGrid();
	void MapGrid();
	void ResetHexs();
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


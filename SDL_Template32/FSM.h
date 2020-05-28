#pragma once
#include <vector>
//Game Objects
#include "Hex.h"

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
};

class GameState : public State
{
private:
	Hex* m_pHex;
public:
	GameState();
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


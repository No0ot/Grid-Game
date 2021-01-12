#pragma once
#include <vector>
#include <list>

//STATES
#include "PlayState.h"

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


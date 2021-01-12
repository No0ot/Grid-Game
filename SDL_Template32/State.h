#pragma once

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


#pragma once

#include <fsm/State.h>

namespace fsm
{

class FiniteStateMachine
{
public:
	FiniteStateMachine();

	virtual State* getCurrentState() const {return currentState; }

	virtual void run();

	virtual void setState(State& newState);

private:
	State* currentState;
};

} // end namespace fsm
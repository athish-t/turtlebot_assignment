#pragma once

namespace fsm
{

class FiniteStateMachine;

class State
{
public:
	virtual void run(FiniteStateMachine* fsm) = 0;

	virtual ~State() {}

};

} // end namespace fsm

#include "fsm/FiniteStateMachine.h"

namespace fsm
{

FiniteStateMachine::FiniteStateMachine() {}

void FiniteStateMachine::setState(State& newState)
{
	currentState = &newState;
	currentState->run(this);
}

void FiniteStateMachine::run()
{
	currentState->run(this);
}

} // end namespace fsm
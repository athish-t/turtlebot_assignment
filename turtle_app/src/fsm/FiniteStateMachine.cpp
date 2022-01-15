#include "fsm/FiniteStateMachine.h"

namespace fsm
{

FiniteStateMachine::FiniteStateMachine() {}

void FiniteStateMachine::setState(State& newState)
{
	if (currentState != nullptr) {
		currentState->terminate(this);
	}
	currentState = &newState;
	currentState->init(this);
}

void FiniteStateMachine::run()
{
	currentState->run(this);
}

} // end namespace fsm
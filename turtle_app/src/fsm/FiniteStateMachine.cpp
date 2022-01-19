#include "fsm/FiniteStateMachine.h"

namespace fsm
{

FiniteStateMachine::FiniteStateMachine() : isRunning(false) {}

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
	while (isRunning) {
		currentState->evaluateTransitions(this);
		currentState->run(this);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void FiniteStateMachine::start()
{
	isRunning = true;
	mainThread.reset(new std::thread(&FiniteStateMachine::run, this));
}

void FiniteStateMachine::stop()
{
	isRunning = false;
	mainThread->join();
}


} // end namespace fsm
#pragma once

#include <vector>
#include <ros/ros.h>

namespace fsm
{

// Forward declare FSM to resolve circular dependency
class FiniteStateMachine;

/*
* Abstract Class defining each state in the FSM
*/
class State
{
public:

	/*
	* Called once when this state is reached
	*/
	virtual void init(FiniteStateMachine* fsm) {};

	/*
	* Called once when this state is exited
	*/
	virtual void terminate(FiniteStateMachine* fsm) {};

	/*
	* Run the state's behaviour.
	* This should be short lived since it is invoked continuously until a transition happens.
	*/
	virtual void run(FiniteStateMachine* fsm) = 0;

	/*
	* Evaluate and transition to a new state.
	*/
	virtual void evaluateTransitions(FiniteStateMachine* fsm) = 0;

	/*
	* Do not destroy since children will be implemented as singletons
	*/
	virtual ~State() {}
};

} // end namespace fsm

#pragma once

#include <vector>
#include <ros/ros.h>

namespace fsm
{

class FiniteStateMachine;

class State
{
public:
	virtual void init(FiniteStateMachine* fsm) {};
	virtual void terminate(FiniteStateMachine* fsm) {};
	virtual void run(FiniteStateMachine* fsm) = 0;

	virtual ~State() {}

};

} // end namespace fsm

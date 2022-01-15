#include "Terminate.h"
#include "fsm/FiniteStateMachine.h"

namespace fsm
{

State& Terminate::getInstance()
{
	static Terminate singleton;
	return singleton;
}

void Terminate::init(FiniteStateMachine* fsm)
{
	ROS_INFO_STREAM_NAMED(__func__, "In Terminate state");
}

void Terminate::run(FiniteStateMachine* fsm)
{
	return;
}

} // end namespace fsm
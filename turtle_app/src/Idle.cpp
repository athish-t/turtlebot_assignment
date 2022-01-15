#include "Idle.h"
#include "Initialize.h"
#include "Terminate.h"
#include "fsm/FiniteStateMachine.h"

namespace fsm
{

State& Idle::getInstance()
{
	static Idle singleton;
	return singleton;
}

void Idle::init(FiniteStateMachine* fsm)
{
	ROS_INFO_STREAM_NAMED(__func__, "In Idle state");
}

void Idle::run(FiniteStateMachine* fsm)
{
	ROS_INFO_STREAM_NAMED(__func__, "**************************************");
	ROS_INFO_STREAM_NAMED(__func__, "Press 'c' to restart");
	ROS_INFO_STREAM_NAMED(__func__, "Press 'q' to terminate");
	ROS_INFO_STREAM_NAMED(__func__, "**************************************");

	// Transition
	// Wait for user unput
	char c;
	std::cin >> c;
	switch(c) {
		case 'c':
			fsm->setState(Initialize::getInstance());
			break;
		case 'q':
			fsm->setState(Terminate::getInstance());
			break;
		default:
			ROS_INFO_STREAM_NAMED(__func__, "Invalid input.");
	};

}

} // end namespace fsm
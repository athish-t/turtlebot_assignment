#include "fsm/FiniteStateMachine.h"
#include "states/Idle.h"
#include "states/Initialize.h"
#include "states/Terminate.h"

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
	userInput = std::nullopt;
}

void Idle::run(FiniteStateMachine* fsm)
{
	ROS_INFO_STREAM_NAMED(__func__, "**************************************");
	ROS_INFO_STREAM_NAMED(__func__, "Press 'c' to restart");
	ROS_INFO_STREAM_NAMED(__func__, "Press 'q' to terminate");
	ROS_INFO_STREAM_NAMED(__func__, "**************************************");

	// Wait for user unput
	char c;
	std::cin >> c;
	userInput = c;
}

void Idle::evaluateTransitions(FiniteStateMachine* fsm)
{
	if (!userInput.has_value()) {
		return;
	}

	switch(userInput.value()) {
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
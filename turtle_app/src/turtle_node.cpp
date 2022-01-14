#include <ros/ros.h>
#include "fsm/FiniteStateMachine.h"
#include "Initialize.h"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "turtle_app");

	fsm::FiniteStateMachine turtleFsm;
	turtleFsm.setState(fsm::Initialize::getInstance());

	return 0;
}
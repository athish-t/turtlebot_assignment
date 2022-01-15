#include <ros/ros.h>
#include "fsm/FiniteStateMachine.h"
#include "Initialize.h"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "turtle_app");
	ros::NodeHandle nh;

	ROS_INFO_STREAM_NAMED(__func__, "Starting turtle FSM node");

	fsm::FiniteStateMachine turtleFsm;
	turtleFsm.setState(fsm::Initialize::getInstance());

	// Tick
	while (ros::ok()) {
		turtleFsm.run();
	}

	return 0;
}
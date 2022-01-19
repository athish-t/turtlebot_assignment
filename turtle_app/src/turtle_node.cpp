#include <ros/ros.h>
#include "fsm/FiniteStateMachine.h"
#include "states/Initialize.h"
#include "world_model.h"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "turtle_app");
	ros::NodeHandle nh;
	ros::AsyncSpinner spinner(1);

	ROS_INFO_STREAM_NAMED(__func__, "Starting turtle FSM node");

	// Initialize world information
	WorldModel::instance().init();

	// Initialize FSM and set intial state
	fsm::FiniteStateMachine turtleFsm;
	turtleFsm.setState(fsm::Initialize::getInstance());

	// Start
	spinner.start();
	turtleFsm.start();

	ros::waitForShutdown();
	turtleFsm.stop();

	return 0;
}
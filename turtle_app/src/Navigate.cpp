#include "Navigate.h"
#include "CameraCapture.h"
#include "fsm/FiniteStateMachine.h"

#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>

namespace fsm
{

State& Navigate::getInstance()
{
	static Navigate singleton;
	return singleton;
}

void Navigate::run(FiniteStateMachine* fsm)
{
	std::cout << "In Navigate state" << std::endl;

	auto& goals = std::any_cast<Goals&>(fsm->getUserData().at("goals"));
	if (goals.size() == 0) {
		std::cout << "No remaining goals" << std::endl;
		return;
	}

	const auto& goal = goals.front();
	std::cout << "Next goal: " << goal[0] << " " << goal[1] << " " << goal[2] << std::endl;

	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> navActionClient("move_base", true);
	navActionClient.waitForServer();
	move_base_msgs::MoveBaseGoal navGoal;
	navGoal.target_pose.header.frame_id = "map";
	navGoal.target_pose.pose.position.x = goal[0];
	navGoal.target_pose.pose.position.y = goal[1];
	navGoal.target_pose.pose.orientation.w = 1.0; // TODO: set quaternion
	navActionClient.sendGoal(navGoal);
	bool finished_before_timeout = navActionClient.waitForResult();

	goals.pop();

	// Transition
	if (goals.size() != 0) {
		fsm->setState(CameraCapture::getInstance());
	}
}

} // end namespace fsm
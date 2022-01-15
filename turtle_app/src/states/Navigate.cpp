#include "fsm/FiniteStateMachine.h"
#include "states/Navigate.h"
#include "states/Idle.h"
#include "states/CameraCapture.h"

namespace fsm
{

State& Navigate::getInstance()
{
	static Navigate singleton;
	return singleton;
}

void Navigate::init(FiniteStateMachine* fsm)
{
	ROS_INFO_STREAM_NAMED(__func__, "In Navigate state");
}

void Navigate::run(FiniteStateMachine* fsm)
{
	auto& goals = std::any_cast<Goals&>(fsm->getUserData().at("goals"));

	// Go to Idle state if all goals are processed
	if (goals.size() == 0) {
		ROS_INFO_STREAM_NAMED(__func__, "No remaining goals");

		// Transition
		fsm->setState(Idle::getInstance());
		return;
	}

	// Get next goal from queue
	const auto& goal = goals.front();
	ROS_INFO_STREAM_NAMED(__func__, "Next goal: " << goal.coordinates[0] << " " << goal.coordinates[1] << " " << goal.coordinates[2]);

	// Send action goal and wait for result
	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> navActionClient("move_base", true);
	navActionClient.waitForServer();
	move_base_msgs::MoveBaseGoal navGoal;
	navGoal.target_pose.header.frame_id = "map";
	navGoal.target_pose.pose.position.x = goal.coordinates[0];
	navGoal.target_pose.pose.position.y = goal.coordinates[1];
	tf2::Quaternion quat;
	quat.setRPY(0, 0, goal.coordinates[2]);
	quat.normalize();
	navGoal.target_pose.pose.orientation = tf2::toMsg(quat);
	navActionClient.sendGoal(navGoal);
	bool finished_before_timeout = navActionClient.waitForResult();

	// Save checkpoint info
	fsm->getUserData()["last_checkpoint_id"] = static_cast<int>(goal.id);
	goals.pop();

	// Transition
	fsm->setState(CameraCapture::getInstance());
}

} // end namespace fsm
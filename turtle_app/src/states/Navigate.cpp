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
	goals = std::addressof(std::any_cast<Goals&>(fsm->getUserData().at("goals")));
	navActionClient.reset(new ActionClient("move_base", true));
	navActionClient->waitForServer();
	goalSent = false;
}

void Navigate::run(FiniteStateMachine* fsm)
{
	if (!goalSent && goals->size() != 0) {
		// Get next goal from queue
		const auto& goal = goals->front();
		ROS_INFO_STREAM_NAMED(__func__, "Next goal: " << goal.coordinates[0] << " " << goal.coordinates[1] << " " << goal.coordinates[2]);

		// Send action goal
		move_base_msgs::MoveBaseGoal navGoal;
		navGoal.target_pose.header.frame_id = "map";
		navGoal.target_pose.pose.position.x = goal.coordinates[0];
		navGoal.target_pose.pose.position.y = goal.coordinates[1];
		tf2::Quaternion quat;
		quat.setRPY(0, 0, goal.coordinates[2]);
		quat.normalize();
		navGoal.target_pose.pose.orientation = tf2::toMsg(quat);
		navActionClient->sendGoal(navGoal);

		goalSent = true;
	}

	auto state = navActionClient->getState();
	if (!state.isDone()) {
		return;
	}
}

void Navigate::terminate(FiniteStateMachine* fsm)
{
	navActionClient->cancelAllGoals();

	// Save checkpoint info
	fsm->getUserData()["last_checkpoint_id"] = static_cast<int>(goals->front().id);
	goals->pop();
}

void Navigate::evaluateTransitions(FiniteStateMachine* fsm)
{
	// Transition to idle if interrupted
	if (WorldModel::instance().isInterrupted()) {
		ROS_WARN_STREAM_NAMED(__func__, "User interrupt requested. Idling now.");
		fsm->setState(Idle::getInstance());
		return;
	}

	auto state = navActionClient->getState();
	if (state == ActionState::SUCCEEDED){
		ROS_INFO_STREAM_NAMED(__func__, "Navigate action goal succeeded");
		fsm->setState(CameraCapture::getInstance());
	}
	else if (
		state == ActionState::RECALLED ||
		state == ActionState::REJECTED ||
		state == ActionState::PREEMPTED ||
		state == ActionState::ABORTED
	) {
		ROS_ERROR_STREAM_NAMED(__func__, "Navigate action goal failed");
		fsm->setState(Idle::getInstance());
	}
	else if (goals->size() == 0) {
		ROS_INFO_STREAM_NAMED(__func__, "No remaining goals");
		fsm->setState(Idle::getInstance()); // Go to Idle state if all goals are processed
	}
}

} // end namespace fsm
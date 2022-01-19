#include "fsm/State.h"
#include "Types.h"
#include "world_model.h"

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/simple_client_goal_state.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

namespace fsm
{

class Navigate : public State
{
	using ActionClient = actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>;
	using ActionState = actionlib::SimpleClientGoalState::StateEnum;

public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm) override;
	virtual void terminate(FiniteStateMachine* fsm) override;
	virtual void evaluateTransitions(FiniteStateMachine* fsm) override;

	/*
	* Get singleton instance of state
	*/
	static State& getInstance();

private:
	/*
	* Disallow default construction to get state instance as singleton
	*/
	Navigate() {}
	Navigate(const Navigate& other);
	Navigate& operator=(const Navigate& other);

	Goals* goals;
	std::unique_ptr<ActionClient> navActionClient;
	bool goalSent;
};

} // end namespace fsm
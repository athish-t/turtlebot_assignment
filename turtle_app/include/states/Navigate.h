#include "fsm/State.h"
#include "Types.h"

#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

namespace fsm
{

class Navigate : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm) override;

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
};

} // end namespace fsm
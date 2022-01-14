#include "Initialize.h"
#include "Navigate.h"
#include "fsm/FiniteStateMachine.h"

namespace fsm
{

State& Initialize::getInstance()
{
	static Initialize singleton;
	return singleton;
}

void Initialize::parseGoals(XmlRpc::XmlRpcValue& xmlGoals, Goals& goals)
{
	ROS_ASSERT(xmlGoals.getType() == XmlRpc::XmlRpcValue::TypeArray);

	for (int i = 0; i < xmlGoals.size(); i++)
	{
		ROS_ASSERT(xmlGoals[i].getType() == XmlRpc::XmlRpcValue::TypeArray);
		ROS_ASSERT(xmlGoals[i].size() == 3);
		ROS_ASSERT(xmlGoals[i][0].getType() == XmlRpc::XmlRpcValue::TypeDouble);
		ROS_ASSERT(xmlGoals[i][1].getType() == XmlRpc::XmlRpcValue::TypeDouble);
		ROS_ASSERT(xmlGoals[i][2].getType() == XmlRpc::XmlRpcValue::TypeDouble);

		goals.push({
			static_cast<double>(xmlGoals[i][0]),
			static_cast<double>(xmlGoals[i][1]),
			static_cast<double>(xmlGoals[i][2])
		});
	}
}

void Initialize::run(FiniteStateMachine* fsm)
{
	std::cout << "In Initialize state" << std::endl;

	ros::NodeHandle nh("~");

	XmlRpc::XmlRpcValue xmlGoals;
	Goals goals;
	nh.getParam("turtle_goals", xmlGoals);
	parseGoals(xmlGoals, goals);

	fsm->getUserData().emplace(std::make_pair("goals", goals));

	fsm->setState(Navigate::getInstance());
}

} // end namespace fsm
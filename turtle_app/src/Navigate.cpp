#include "Navigate.h"
#include "CameraCapture.h"
#include "fsm/FiniteStateMachine.h"

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
	auto& goals = std::any_cast<std::vector<std::vector<double>>&>(fsm->getUserData().at("goals"));

	std::cout << "goals: " << std::endl;
	for (auto& goal : goals){
		std::cout << goal[0] << " " << goal[1] << " " << goal[2] ;
		std::cout << std::endl;
	}

	fsm->setState(CameraCapture::getInstance());
}

} // end namespace fsm
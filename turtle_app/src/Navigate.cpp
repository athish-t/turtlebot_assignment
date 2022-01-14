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

	auto& goals = std::any_cast<Goals&>(fsm->getUserData().at("goals"));
	if (goals.size() == 0) {
		std::cout << "No remaining goals" << std::endl;
	}
	else {
		const auto& goal = goals.front();
		std::cout << "Next goal: " << goal[0] << " " << goal[1] << " " << goal[2] << std::endl;
		goals.pop();
	}

	if (goals.size() != 0) {
		fsm->setState(CameraCapture::getInstance());
	}
}

} // end namespace fsm
#include <iostream>
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
	fsm->setState(CameraCapture::getInstance());
}

} // end namespace fsm
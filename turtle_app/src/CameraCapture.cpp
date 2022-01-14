#include <iostream>
#include "fsm/FiniteStateMachine.h"
#include "CameraCapture.h"
#include "Navigate.h"

namespace fsm
{

State& CameraCapture::getInstance()
{
	static CameraCapture singleton;
	return singleton;
}

void CameraCapture::run(FiniteStateMachine* fsm)
{
	std::cout << "In CameraCapture state" << std::endl;
	// fsm->setState(Navigate::getInstance());
}

} // end namespace fsm
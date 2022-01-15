#include "Navigate.h"
#include "CameraCapture.h"
#include "fsm/FiniteStateMachine.h"

namespace fsm
{

State& CameraCapture::getInstance()
{
	static CameraCapture singleton;
	return singleton;
}

void CameraCapture::run(FiniteStateMachine* fsm)
{
	ROS_INFO_STREAM_NAMED(__func__, "In CameraCapture state");
	fsm->setState(Navigate::getInstance());
}

} // end namespace fsm
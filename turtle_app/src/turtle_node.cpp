#include "fsm/FiniteStateMachine.h"
#include "Navigate.h"

int main(int argc, char** argv)
{
	fsm::FiniteStateMachine turtleFsm;
	turtleFsm.setState(fsm::Navigate::getInstance());

	return 0;
}
#include "fsm/State.h"

namespace fsm
{

class CameraCapture : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;

	static State& getInstance();

private:
	CameraCapture() {}
	CameraCapture(const CameraCapture& other);
	CameraCapture& operator=(const CameraCapture& other);
};

} // end namespace fsm
#include "fsm/State.h"
#include "Types.h"

namespace fsm
{

class Idle : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm);

	static State& getInstance();

private:
	Idle() {}
	Idle(const Idle& other);
	Idle& operator=(const Idle& other);
};

} // end namespace fsm
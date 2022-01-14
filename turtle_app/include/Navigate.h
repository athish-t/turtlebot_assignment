#include "fsm/State.h"

namespace fsm
{

class Navigate : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;

	static State& getInstance();

private:
	Navigate() {}
	Navigate(const Navigate& other);
	Navigate& operator=(const Navigate& other);
};

} // end namespace fsm
#include "fsm/State.h"
#include "Types.h"

namespace fsm
{

class Idle : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm) override;

	/*
	* Get singleton instance of state
	*/
	static State& getInstance();

private:

	/*
	* Disallow default construction to get state instance as singleton
	*/
	Idle() {}
	Idle(const Idle& other);
	Idle& operator=(const Idle& other);
};

} // end namespace fsm
#include "fsm/State.h"
#include "Types.h"

namespace fsm
{

class Terminate : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm) override;
	virtual void evaluateTransitions(FiniteStateMachine* fsm) override;

	/*
	* Get singleton instance of state
	*/
	static State& getInstance();

private:
	/*
	* Disallow default construction to get state instance as singleton
	*/
	Terminate() {}
	Terminate(const Terminate& other);
	Terminate& operator=(const Terminate& other);
};

} // end namespace fsm
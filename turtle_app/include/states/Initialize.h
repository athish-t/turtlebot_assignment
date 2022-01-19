#include "fsm/State.h"
#include "Types.h"

namespace fsm
{

class Initialize : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm) override;
	virtual void evaluateTransitions(FiniteStateMachine* fsm) override;

	/*
	* Get singleton instance of state
	*/
	static State& getInstance();

protected:
	/*
	* Parse goal data from xmlrpc data obtained from param server
	*/
	void parseGoals(XmlRpc::XmlRpcValue& xmlGoals, Goals& goals);

private:
	/*
	* Disallow default construction to get state instance as singleton
	*/
	Initialize() {}
	Initialize(const Initialize& other);
	Initialize& operator=(const Initialize& other);

	bool initialized;
};

} // end namespace fsm
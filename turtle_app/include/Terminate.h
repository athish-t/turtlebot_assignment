#include "fsm/State.h"
#include "Types.h"

namespace fsm
{

class Terminate : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm);

	static State& getInstance();

protected:
	void parseGoals(XmlRpc::XmlRpcValue& xmlGoals, Goals& goals);

private:
	Terminate() {}
	Terminate(const Terminate& other);
	Terminate& operator=(const Terminate& other);
};

} // end namespace fsm
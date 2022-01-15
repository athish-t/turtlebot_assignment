#include "fsm/State.h"
#include "Types.h"

namespace fsm
{

class Initialize : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm);

	static State& getInstance();

protected:
	void parseGoals(XmlRpc::XmlRpcValue& xmlGoals, Goals& goals);

private:
	Initialize() {}
	Initialize(const Initialize& other);
	Initialize& operator=(const Initialize& other);
};

} // end namespace fsm
#include "fsm/State.h"

namespace fsm
{

class Initialize : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;

	static State& getInstance();

protected:
	void parseGoals(XmlRpc::XmlRpcValue& xmlGoals, std::vector<std::vector<double>>& goals);

private:
	Initialize() {}
	Initialize(const Initialize& other);
	Initialize& operator=(const Initialize& other);
};

} // end namespace fsm
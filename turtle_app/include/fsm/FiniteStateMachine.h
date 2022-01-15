#pragma once

#include <unordered_map>
#include <any>

#include "fsm/State.h"

namespace fsm
{

class FiniteStateMachine
{
	using UserData = std::unordered_map<std::string, std::any>;

public:
	FiniteStateMachine();

	State* getCurrentState() const {return currentState; }

	void run();

	void setState(State& newState);

	UserData& getUserData() {return userData; }

private:
	State* currentState = nullptr;

	UserData userData;
};

} // end namespace fsm
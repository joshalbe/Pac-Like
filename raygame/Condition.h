#pragma once
#include "Agent.h"

class Condition
{
	///<Summary>
	/// Conditions allow us to test the success of decisions and transitions.
	/// As a pure virtual class, classes inherit from
	/// Condition and implement the function to decide the result.
	///<Summary>

public:
	Condition() {}
	virtual ~Condition() {}

	virtual bool test(Agent* agent) const = 0;
};
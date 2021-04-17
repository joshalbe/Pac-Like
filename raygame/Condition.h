#pragma once
#include "Agent.h"

class Condition
{
public:
	Condition() {}
	virtual ~Condition() {}

	virtual bool test(Agent* agent) const = 0;
};
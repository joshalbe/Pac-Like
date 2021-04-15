#pragma once
#include "Agent.h"

class Decision
{
public:
	virtual void makeDecision(Agent* agent, float deltaTime) = 0;
};


#pragma once
#include "Decision.h"
class BehaviorDecision : public Decision
{
public:
	BehaviorDecision(Behavior* behavior) : m_behavior(behavior) {}
	~BehaviorDecision() {}

	virtual void makeDecision(Agent* agent, float deltaTime);

private:
	Behavior* m_behavior = nullptr;

};


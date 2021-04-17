#include "BehaviorDecision.h"
#include "Behavior.h"

void BehaviorDecision::makeDecision(Agent* agent, float deltaTime) 
{
	//Return if the behavior is empty
	if (m_behavior == nullptr)
		return;

	m_behavior->update(agent, deltaTime);
}
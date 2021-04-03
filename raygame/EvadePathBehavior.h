#pragma once
#include "SteeringBehavior.h"

class Agent;

class EvadePathBehavior : public SteeringBehavior
{
public:
	EvadePathBehavior(Character* target, float forceScale = 5);

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
};